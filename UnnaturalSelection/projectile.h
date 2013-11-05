//This is the base structure for all projectiles and the interface
//by Michael Wiegand
// 11/4/2013
#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "entity.h"

//Constants for Projectile class
namespace projectileNS
{



}


class Projectile: public Entity
{
public:
	/*********************************************
	ALL VARIBLES
	**********************************************/
	//The damage of the perjectile
	int damage;
	int minRange;
	int maxRange;
	//Current distance traveled
	float distance;
	//Angle Traveling
	float angle;
	//Any Mods that change the projectile
	//ProjectileMod* projectileMods[];

	/*********************************************
	ALL FUNCTIONS
	**********************************************/
	void act();

	/**************************
	INITALIZERS
	**************************/
	Projectile(int damage, int minRange, int maxRange, int muzzelVelocity, int angle, VECTOR2 position);
};


#endif