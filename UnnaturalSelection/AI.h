#ifndef AI_H
#define AI_H

#include "Character.h"
#include "HealthBar.h"
#include "game.h"
#include "graphics.h"

class AI : public Character {
public : 
	AI(Game* game, Graphics* graphics, float hp = 300);

	virtual void draw() {
		Character::draw();

		//hb->draw();
	}

	virtual void initialize() {
		Character::initialize();

		hb->initialize();
	}

	virtual void update(float frameTime)
	{
		if(invertColorCount > 0)
		{
			if(invertColorCount == 1)
			{
				this->body->color = D3DCOLOR_ARGB(510,255,255,255) - this->body->color;
			}
			invertColorCount--;

		}
	//Health bar stuff
		int x = body->getCenterX()-hb->getWidth()/2;
		int y = body->getCenterY();
		hb->setCenterX(x);
		hb->setY(y-100);
		hb->setPercent(healthPoints / characterNS::HEALTH_POINTS);
		hb->update(frameTime);

		bool goRight(false), goLeft(false), callJump(false);
		D3DXVECTOR2 distance = characters[0]->getCenter()-this->getCenter();
		float minDist = (distance.x*distance.x + distance.y*distance.y);
		int closest = 0;
		
		if(target != 0 && canSee(target))
		{

		}else{
			for(int i(0); i < characterSize; i++)
			{
				if(characters[i] != this)
				{
					distance = characters[i]->getCenter()-this->getCenter();
					float dist = (distance.x*distance.x + distance.y*distance.y);
					if(canSee(characters[i]))
					{
						target = characters[i];
					}
					if(dist < minDist)
					{
						minDist = dist;
						closest = i;
					}
				}
			}
			if(!canSee(target))
			{
				target = characters[closest];
			}
		}
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
		//TARGET FOUND AT THIS POINT

		//Start Movement Code
		if(target->standingOn == standingOn)
		{
			callJump = true;
		}

		//END movement Code
		if(target != 0)
		{
			int goDir = moveDirection(target);
			if(goDir > 0)
			{
				goRight = true;
			}else if(goDir < 0){
				goLeft = true;
			}
		}

		firing = !firing;
//		Character::update(frameTime, false, false, false, false, false);
		Character::update(frameTime, goRight, goLeft, callJump || standingOn == 0, shouldShoot(target) && firing, false);
	
	}
	void giveInfo(int charSize, Character** chars, int terrainSize, TerrainElement** terrains)
	{
		characterSize = charSize;
		characters = chars;
		this->terrainSize = terrainSize;
		terrain = terrains;
	}
	
	bool canSee(Character* enemy)
	{
		if(enemy==0)return false;
		D3DXVECTOR2 delta = enemy->getCenter() - getCenter();
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

	bool shouldShoot(Character* enemy)
	{
		
		D3DXVECTOR2 delta = enemy->getCenter() - getCenter();
		float distSquared = delta.x*delta.x + delta.y*delta.y;
		if(shootDistance*shootDistance < distSquared || minShootDistance*minShootDistance > distSquared)
		{
			return false;
		}
		return canSee(enemy);
	}
	//true is right
	int moveDirection(Character* enemy)
	{
		D3DXVECTOR2 distance = enemy->getCenter()-getCenter();
		if((minShootDistance+2*sightDistance)/3 < abs(distance.x))
		{
			return (distance.x < 0? -1: 1);
		}else if(abs(distance.x) < (minShootDistance+2*sightDistance)/3){
			return (distance.x < 0? 1: -1);
		}
		//return rand()%2;
		return 0;
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
	//Lines of sight
	int sightDistance;
	int shootDistance;
	int minShootDistance;
	HealthBar* hb;


};

#endif