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
	for(int i(0); i < size; i++)
	{
		delete projArray[i];
	}
}
/*********************************************
ALL FUNCTIONS
**********************************************/
void Magazine::fire(D3DXVECTOR2 initialPos, float angle)
{
	projArray[0]->fire(initialPos, angle);
	projectile->fire(initialPos, 100);
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