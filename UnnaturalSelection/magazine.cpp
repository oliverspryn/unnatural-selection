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
		projArray[i] = new Projectile();
	}
	projArrayIndex = 0;
	loadAmmo();
}
Magazine::Magazine()
{
	using namespace magazineNS;
	Magazine(MAG_SIZE, MAX_AMMO, MAX_AMMO, DAMAGE, MUZZEL_VELOCITY, RECOIL, ONE, 0);
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
	projArray[projArrayIndex]->fire(initialPos, angle);

}
//Calls update for all porjectiles that are active
void Magazine::updateMagsProjtiles(float frameTime)
{
	for(int i(0); i <= projArrayIndex; i++)
	{
		projArray[i]->update(frameTime);
	}
}
void Magazine::loadAmmo()
{
	totalAmmo += ammoCount;
	ammoCount = min(totalAmmo, size);
	totalAmmo -= ammoCount;
}