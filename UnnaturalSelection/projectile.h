//This is the base structure for all projectiles and the interface
//by Michael Wiegand
// 11/4/2013
#ifndef PROJECTILE_H
#define PROJECTILE_H
#define WIN32_LEAN_AND_MEAN
#include "entity.h"
#include "line.h"

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
	float lifeTime;
	//The speed the projectile travels at
	int muzzelVelocity;
	
	//The line
	myLines::Ray ray;
	bool rayUpdated;
	float maxTime;

	/*********************************************
	ALL FUNCTIONS
	**********************************************/
	//Used for copy constructor
	virtual void operator=(Projectile& in);
	virtual void update(float frameTime);
	Game* setGamePointer(Game* set);
	//Takes care of hitbot, image, and collision
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	//Puts the Projectile in the position to act
	virtual void fire(D3DXVECTOR2 initialPos, float angle);
	//Used to set stats of projectile
	virtual void setStats(int damage, int minRange, int maxRange, int muzzelVelocity);
	virtual void setStaticHitTime(float in);

	/**************************
	INITALIZERS
	**************************/
	Projectile(TextureManager* tm, Game* gamePtr, int width, int height, int ncoils, int hitBoxRadius);
};


#endif