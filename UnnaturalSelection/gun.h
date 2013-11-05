//This is the base class for all guns and the interface
//By Michael Wiegand
// 11/4/2013
#ifndef GUN_H
#define GUN_H
#include "weapon.h"
#include "magazine.h"

//The constant values for Guns
namespace gunNS
{
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
enum FireMode{AUTO, SEMI_AUTO, BURST_TWO, BURST_THREE, BURST_FOUR, BURST_FIVE};
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
		fireTime = RPM/60.0;
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
	FireMode fireMode;
	//The mag type the gun can use
	MagType magType;
	//What Magazine is loaded
	Magazine *mag;
	//How long since it was last fired
	float timeSinceLastFired;
	//Tells you what the gun timer is being used for
	GunState gunState;
	//Used to determin if reloading is done 
	float gunTimer;
	//Gun Mods
	//GunMode* gunMods[];

	/*********************************************
	ALL FUNCTIONS
	**********************************************/
	//Input1 is fire, input2 reload, input3 is for gunMod1, input4 is for gunMod2, input 5 is for gunMod3;
	virtual void act(float frameTime, bool &input1, bool &input2, bool &input3, bool &input4, bool &input5);
	virtual void fire();


	/**************************
	INITALIZERS
	**************************/
	Gun();
	Gun(int damage, int rpm, int minRange, int maxRange, int muzzelVelocity, int recoilReduction, int spread, float reloadTime, FireMode fireMode, MagType magType);
};


#endif