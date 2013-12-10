#ifndef AI_H
#define AI_H

#include "Character.h"
#include "game.h"
#include "graphics.h"


class AI : public Character {
public : 
	AI(Game* game, Graphics* graphics, int charSize = 0, Character** chars = 0, int terrainSize = 0, TerrainElement** terrains = 0);
	virtual void update(float frameTime)
	{
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
			if(input->isKeyDown('R') && reloadStep == 0)
			{
				reloadStep = 1;
				reloadTimer = frameTime;
			}
			if(reloadStep != 0)
			{
				reloadTimer += frameTime;
				if(reloadTimer > static_cast<Gun*>(currentWeapon)->reloadTime)
				{
					static_cast<Gun*>(currentWeapon)->loadMag();
					reloadStep = 0;
				}
				else if(reloadTimer > static_cast<Gun*>(currentWeapon)->reloadTime/3)
				{
					static_cast<Gun*>(currentWeapon)->removeMag();
					currentMag->loadAmmo();
				}
			}
			currentWeapon->act(frameTime, 0, false, false, false, false);
		}
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

};

#endif