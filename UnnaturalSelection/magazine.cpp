//The implemintation of Magazine
//By Michael Wiegand
// 11/4/2013

#include "magazine.h"

/**************************
INITALIZERS
**************************/
Magazine::Magazine(int size, int maxAmmo, int totalAmmo, int damage, int muzzelVelocity, int recoil, MagType magType, Projectile* projectile): size(size), maxAmmo(maxAmmo), totalAmmo(totalAmmo), damage(damage), muzzelVelocity(muzzelVelocity), recoil(recoil), magType(magType), projectile(projectile)
{
	projArray = new Projectile*[size];
	for(int i(0); i < size; i++)
	{
		projArray[i] = new Projectile(*projectile);
	}
	projArrayIndex = 0;
	loadAmmo();
}

Magazine::~Magazine()
{
	delete []projArray;
}
/*********************************************
ALL FUNCTIONS
**********************************************/
void Magazine::fire(D3DXVECTOR2 initialPos, float angle)
{
	projArray[projArrayIndex]->fire(initialPos, angle);
	projArrayIndex++;
	projArrayIndex %= size;
}
//Calls update for all porjectiles that are active
void Magazine::updateMagsProjectiles(float frameTime)
{
	for(int i(0); i < size; i++)
	{
		if(projArray[i]->getActive())
		{
			projArray[i]->update(frameTime);
		}
	}
	if(projectile->getActive())
	{
		projectile->update(frameTime);
	}
}
void Magazine::loadAmmo()
{
	totalAmmo += ammoCount;
	ammoCount = min(totalAmmo, size);
	totalAmmo -= ammoCount;
}
//Calls display for all active projectiles
void Magazine::displayMagsProjectiles()
{
	for(int i(0); i < size; i++)
	{
		if(projArray[i]->getVisible())
		{
			projArray[i]->draw();
		}
	}
}
//Sets all Projectiles to the new stats
void Magazine::setProjectileStats(int damage, int minRange, int maxRange, int muzzelVelocity)
{
	damage += this->damage;
	//minRange += this->minRange;
	//maxRange += this->maxRange;
	muzzelVelocity += this->muzzelVelocity;
	for(int i(0); i < size; i++)
	{
		projArray[i]->setStats(damage, minRange, maxRange, muzzelVelocity);
	}
}
//Returns the next projectile, used to put in chamber and sets the index to the next
Projectile* Magazine::getNextProjectile()
{
	//Needs to see if there is a next round avaible, if none return 0;
	Projectile* nextRound = projArray[projArrayIndex];
	projArrayIndex++;
	projArrayIndex %= size;
	return nextRound;
}