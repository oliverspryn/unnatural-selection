#ifndef AI_H
#define AI_H

#include "Character.h"
#include "game.h"
#include "graphics.h"


class AI : public Character {
public : 
	AI(Game* game, Graphics* graphics);
	virtual void update(float frameTime)
	{
		D3DXVECTOR2 distance = characters[0]->getCenter()-this->getCenter();
		float minDist = (distance.x*distance.x + distance.y*distance.y);
		int closest = 0;
		for(int i(0); i < characterSize; i++)
		{
			if(characters[i] != this)
			{
				distance = characters[i]->getCenter()-this->getCenter();
				float dist = (distance.x*distance.x + distance.y*distance.y);
				if(dist < minDist)
				{
					minDist = dist;
					closest = i;
				}
			}
		}
		target = characters[closest];
		if(target == 0 && characterSize > 1)
		{
			target = characters[rand()%characterSize];
			while(target == this)
			{
				target = characters[rand()%characterSize];
			}
		}
		if(target != 0)
		{
				aimAngle = atan2(target->getCenterY()-this->getCenterY(), target->getCenterX()-this->getCenterX());
		}

		if (standingOn == 0 || !standingOn->getActive()) {
			D3DXVECTOR2 v (
				body->getVelocity().x, 
				body->getVelocity().y + frameTime * characterNS::GRAVITY_Y
			);

			setVelocity(v);
		} else {
			int xpos = body->getX();

			if (body->getCenterX() + 12 < standingOn->corners[0].x || body->getCenterX() - 12 > standingOn->corners[3].x) {
				standingOn = 0;
			}
		}

	////Move left or right
	//	if (input->isKeyDown(characterNS::WALK_LEFT) ^ input->isKeyDown(characterNS::WALK_RIGHT)) {
	//		faceDir = input->isKeyDown(characterNS::WALK_RIGHT) ? 1 : -1;

	//		body->walking = true;
	//	} else {
	//		faceDir = 0;
	//		body->walking = false;
	//	}

	//Crouch, disabled, sad face :(
		//body->crouch = input->isKeyDown(characterNS::CROUCH);
		//head->crouch = input->isKeyDown(characterNS::CROUCH);

		if (standingOn != 0) {
			body->jumping = false;
			
		} else {
			walk(frameTime/3);
			body->jumping = true;
		}

	//Ready? Aim... <insert "fire" statement here, when ready>
	
		//aimAngle = atan2(
		//	body->getY() - static_cast<float>(input->getMouseY()),
		//	body->getX() - static_cast<float>(input->getMouseX())
		//);

	//Determine orientation of the player, based on the mouse direction
		if (aimAngle > PI2) { // Quadrant 1
			faceDir = 1;
		}

		if (aimAngle < PI2 && aimAngle > 0.0) { // Quadrant 2
			faceDir = -1;
		}

		if (aimAngle > -PI2 && aimAngle <= 0.0) { // Quadrant 3
			faceDir = -1;
		}

		if (aimAngle < -PI2 && aimAngle <= 0.0) { // Quadrant 4
			faceDir = 1;
		}

	//Set the direction of the player
		body->faceDir = faceDir;
		head->faceDir = faceDir;

		body->update(frameTime);
		//cursor->update(frameTime);
		head->update(frameTime);

		updateCorners();

		if(currentWeapon != 0)
		{
			if(target == 0)
			{
				if(this->faceDir > 0)
				{
					aimAngle = PI;
				}else{
					aimAngle = 0;
				}
			}
			currentWeapon->setAngle(aimAngle);
			currentWeapon->setX(getCenterX() + weaponPos.x * std::cos(aimAngle) + weaponPos.y * std::sin(aimAngle) - currentWeapon->getWidth()/2);
			currentWeapon->setY(getCenterY() + weaponPos.y * std::cos(aimAngle) + weaponPos.x * std::sin(aimAngle) -currentWeapon->getHeight()/2);

			currentWeapon->update(frameTime);
			if(reloadStep == 0 && (input->isKeyDown('R') || reinterpret_cast<Gun*>(currentWeapon)->mag->ammoCount == 0))
			{
				reloadStep = 1;
				reloadTimer = frameTime;
			}
			if(reloadStep != 0)
			{
				reloadTimer += frameTime;
				if(reloadTimer > static_cast<Gun*>(currentWeapon)->reloadTime)
				{
					if(static_cast<Gun*>(currentWeapon)->isMagInGun)
					{
						currentMag->loadAmmo();
					}
					static_cast<Gun*>(currentWeapon)->loadMag();
					reloadStep = 0;
				}
				else if(reloadTimer > static_cast<Gun*>(currentWeapon)->reloadTime/100)
				{
					static_cast<Gun*>(currentWeapon)->removeMag();
					currentMag->loadAmmo();
				}
			}
			firing = !firing;
			currentWeapon->act(frameTime, firing && shouldShoot(target), false, false, false, false);
		}
	}
	void giveInfo(int charSize, Character** chars, int terrainSize, TerrainElement** terrains)
	{
		characterSize = charSize;
		characters = chars;
		this->terrainSize = terrainSize;
		terrain = terrains;
	}
	
	bool shouldShoot(Character* enemy)
	{
		int sightDistance = 500;
		D3DXVECTOR2 delta = enemy->getCenter() - getCenter();
		if(sightDistance*sightDistance < delta.x*delta.x + delta.y*delta.y)
		{
			return false;
		}
		myLines::Ray rayOfSight(getCenter(), delta, sightDistance);
		for(int i(0); i < terrainSize; i++)
		{
			float ft = 1;
			if(terrain[i]->collidesWithRay(&rayOfSight, ft))
			{
				return false;
			}
		}
		return true;
	}

	//number of other characharers
	int characterSize;
	//The characters that exist
	Character** characters;
	//Number of terrain elements
	int terrainSize;
	//All terrain elements
	TerrainElement** terrain;
	//The Current target
	Character* target;
	//If gun was shot last round
	bool firing;

};

#endif