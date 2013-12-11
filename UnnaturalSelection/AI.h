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
		//TARGET FOUND AT THIS POINT

		//Start Movement Code
		bool callJump = false;
		if(target->standingOn == standingOn)
		{
			callJump = true;
		}

		//END movement Code


		firing = !firing;
		Character::update(frameTime, false, false, callJump || standingOn == 0, shouldShoot(target) && firing, false);
	
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
		int minShootDistance = 50;
		D3DXVECTOR2 delta = enemy->getCenter() - getCenter();
		float distSquared = delta.x*delta.x + delta.y*delta.y;
		if(sightDistance*sightDistance < distSquared || minShootDistance*minShootDistance > distSquared)
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