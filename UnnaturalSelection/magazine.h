//Base class for all Magazines that are used and the interface
//By Michael Wiegand
// 11/4/2013

#ifndef MAGAZINE_H
#define MAGAZINE_H
#define WIN32_LEAN_AND_MEAN
#include "projectile.h"

//Contains the constatnts or defaults for Magazine
namespace magazineNS
{
	const int MAG_SIZE = 30;
	const int MUZZEL_VELOCITY = 0;
	const int RECOIL = 30;
	const int DAMAGE = 10;
	const int MAX_AMMO = 300;

}

//Enumberated types needed
//enum MagType{5mm, 7mm, 7.62mm, 8mm, 9mm, 10mm, 11.43mm, 12.7mm};
enum MagType{ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, ELEVEN, TWELVE};


class Magazine
{
public:
	/*********************************************
	ALL VARIBLES
	**********************************************/
	//How many rounds are in the clip currently
	int ammoCount;
	//Max number of round the clip can hold
	int size;
	//Total Ammo Max
	int maxAmmo;
	//Total ammo;
	int totalAmmo;
	//Damage it adds
	int damage;
	//Muzzel Velocity it adds
	int muzzelVelocity;
	//Recoil when fired
	int recoil;
	//What type of mag it is
	MagType magType;
	//What projectile it makes
	Projectile* projectile;
	//All the projectiles that the mag made
	Projectile** projArray;
	//Keeps track of the index of the last active
	int projArrayIndex;
	//Projectile
	//Mag Mods
	//MagMods* magMods[];

	/*********************************************
	ALL FUNCTIONS
	**********************************************/
	//Calls update for all porjectiles that are active
	virtual void updateMagsProjectiles(float frameTime);
	//Puts ammo in the clip
	virtual void loadAmmo();
	//Calls display for all active projectiles
	virtual void displayMagsProjectiles();
	//Sets all Projectiles to the new stats
	virtual void setProjectileStats(int damage, int minRange, int maxRange, int muzzelVelocity);
	//Returns the next projectile, used to put in chamber and sets the index to the next
	virtual Projectile* getNextProjectile();

	/**************************
	INITALIZERS
	**************************/
	Magazine(int size, int maxAmmo, int totalAmmo, int damage, int muzzelVelocity, int recoil, MagType magType, Projectile* projectile);
	~Magazine();

};



#endif