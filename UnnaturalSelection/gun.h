//This is the base class for all guns and the interface
//By Michael Wiegand
// 11/4/2013
#ifndef GUN_H
#define GUN_H
#define WIN32_LEAN_AND_MEAN
#include "weapon.h"
#include "magazine.h"

//The constant values for Guns also defaults
namespace gunNS
{
	//Deafult Gun Immage
	const char GUN_PICTURE[] =   "pictures\\AssultRifle(128x32).png"; 
	/**************************
	WEAPON BASE STATS
	**************************/
	//Damage
	const int MIN_DAMGE = 0;
	const int MAX_DAMAGE = 1000;
	const int BASE_DAMAGE = 10;
	//Fire Rate
	//Rounds per minute
	const int MIN_RPM = 1;
	const int MAX_RPM = 6000;
	const int BASE_RPM = 60;
	//Muzzel Velocity
	//World units per second
	const int MIN_MUZZEL_VELOCITY = 10;
	const int MAX_MUZZEL_VELOCITY = 10000;
	const int BASE_MUZZEL_VELOCITY = 2000;
	//Min Range
	//World Units
	const int MIN_MIN_RANGE = 1;
	const int MAX_MIN_RANGE = 10000;
	const int BASE_MIN_RANGE = 500;
	//Max Range
	//World Units
	const int MIN_MAX_RANGE = 1;
	const int MAX_MAX_RANGE = 10000;
	const int BASE_MAX_RANGE = 500;
	//Recoil Reduction
	const int MIN_RECOIL_REDUCTION = -180;
	const int MAX_RECOIL_REDUCTION = 180;
	const int BASE_RECOIL_REDUCTION = 20;
	//Spread
	const int MIN_SPREAD = 0;
	const int MAX_SPREAD = 180;
	const int BASE_SPREAD = 30;
	//Reload Time
	const float MIN_RELOAD_TIME = 0;
	const float MAX_RELOAD_TIME = 10;
	const float BASE_RELOAD_TIME = 2.0;

}

//Enumerated types needed

//0 is automatic, then 1 is a burst of 1, 2 is a burst of 2, 3 is a burst of 3....
enum FireMode{AUTO, SEMI_AUTO, BURST_TWO, BURST_THREE, BURST_FOUR, BURST_FIVE, BURST_SIX, BURST_SEVEN, BURST_EIGHT, BURST_NINE, BURST_TEN, BURST_ELEVEN};
//Used for timers
enum GunState{NONE, FIREING, RELOADING, SWITCHING, JAMMED, OTHER};

struct FireRate
{
	FireRate(int roundsPerMinute)
	{
		set(roundsPerMinute);
	}
	void set(int roundsPerMinute)
	{
		RPM = roundsPerMinute;
		fireTime = 60.0/RPM;
	}
	//rounds per minute
	int RPM;
	//how long it takes to fire one round
	float fireTime;
};

class Gun : public Weapon
{
public:
	
	/*********************************************
	ALL VARIBLES
	**********************************************/

	/**************************
	GUNS'S STATS
	**************************/
	int damage;
	FireRate fireRate;
	int minRange;
	int maxRange;
	int muzzelVelocity;
	int recoilReduction;
	int spread;
	float reloadTime;
	//Auto, semi, burstfire
	int fireMode;
	//The mag type the gun can use
	MagType magType;
	//What Magazine is loaded
	Magazine *mag;
	//The next round that will be fired
	Projectile* chamberedProjectile;
	//How long since it was last fired
	float timeSinceLastFired;
	//Tells you what the gun timer is being used for
	GunState gunState;
	//Used to determin if reloading is done 
	float gunTimer;
	//Gun Mods
	//GunMode* gunMods[];
	//Where bullets come out
	D3DXVECTOR2 fireLocation;
	//tells if the player has let go of fire since fireing began, used for no auto weapons
	bool canFireAgainSemiAuto;
	//Keeps track of how many shots have been fired in the burst
	int burstCount;
	//Keeps track of if the mag is in or out of the gun
	bool isMagInGun;



	/*********************************************
	ALL FUNCTIONS
	**********************************************/
	//Input1 is fire, input2 reload, input3 is for gunMod1, input4 is for gunMod2, input 5 is for gunMod3;
	virtual void act(float frameTime, bool input1, bool input2, bool input3, bool input4, bool input5);
	virtual void fire(D3DXVECTOR2 initialPos, float angle);
	//Accounts for if multiple bullets could leave the gun in one frame
	virtual void multiFire(float frameTime);
	//Takes the mag out of the gun
	virtual void removeMag();
	//Places the mag in the gun
	virtual void loadMag();
	virtual void recoil(float frameTime);
	//Updates all the projectile in the clip to meet the guns stats
	virtual void loadNewMag(Magazine* newMag);
	//Puts the next projectile in the chamber and removes it from the mag
	virtual void chamberNextProjectile();
	//
	


	/**************************
	INITALIZERS
	**************************/
	Gun(int damage, int rpm, int minRange, int maxRange, int muzzelVelocity, int recoilReduction, int spread, float reloadTime, int fireMode, MagType magType);
};


#endif