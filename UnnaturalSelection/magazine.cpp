//The implemintation of Magazine
//By Michael Wiegand
// 11/4/2013

#include "magazine.h"

/**************************
INITALIZERS
**************************/
Magazine::Magazine(int size, int maxAmmo, int totalAmmo, int damage, int muzzelVelocity, int recoil, MagType magType, Projectile* projectile): size(size), maxAmmo(maxAmmo), totalAmmo(totalAmmo), damage(damage), muzzelVelocity(muzzelVelocity), recoil(recoil), magType(magType), projectile(projectile)
{
	loadAmmo();
}
Magazine::Magazine()
{
	using namespace magazineNS;
	Magazine(MAG_SIZE, MAX_AMMO, MAX_AMMO, DAMAGE, MUZZEL_VELOCITY, RECOIL, ONE, 0);
}


/*********************************************
ALL FUNCTIONS
**********************************************/
void Magazine::loadAmmo()
{
	totalAmmo += ammoCount;
	ammoCount = min(totalAmmo, size);
	totalAmmo -= ammoCount;
}