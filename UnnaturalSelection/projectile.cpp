//The implemintation of projectile
//By Michael Wiegand
// 11/4/2013

#include "projectile.h"

/**************************
INITALIZERS
**************************/
Projectile::Projectile(TextureManager* tm, Game* gamePtr, int width, int height, int ncoils, int hitBoxRadius) : Entity()
{
	setGamePointer(gamePtr);
	initialize(gamePtr, width, height, ncoils, tm);
	distance = 0;
	lifeTime = 0;
	active = false;
	visible = false;
	//this->radius = 1;
	this->radius = hitBoxRadius;
	rayUpdated = false;
}

/*********************************************
ALL FUNCTIONS
**********************************************/
//Used for copy constructor
void Projectile::operator=(Projectile& in)
{
	spriteData = in.spriteData;
	textureManager = in.textureManager;
	setStats(in.damage, in.minRange, in.maxRange, in.muzzelVelocity);

}
Game* Projectile::setGamePointer(Game* set)
{
	static Game* gamePtr;
	if(set != 0)
	{
		gamePtr = set;
	}
	return gamePtr;
}
void Projectile::update(float frameTime)
{
	lifeTime += frameTime;
	distance += muzzelVelocity*frameTime;
	//The bullet will stop 
	if(distance > maxRange || (rayUpdated && frameTime < lifeTime))
	{
 		active = false;
		visible = false;
		return;
	}

	spriteData.x += frameTime*velocity.x;
	spriteData.y += frameTime*velocity.y;
	ray.setPosition(*getCenter());
}

bool Projectile::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	spriteData.angle = angle;
	return Entity::initialize(gamePtr, width, height, ncols, textureM);
}

//Puts the Projectile in the position to act
void Projectile::fire(D3DXVECTOR2 initialPos, float angle)
{
	active = true;
	visible = true;
	lifeTime = 0;
	distance = 0;
	spriteData.x = initialPos.x-(spriteData.width*spriteData.scale)/2;
	spriteData.y = initialPos.y-(spriteData.height*spriteData.scale)/2;
	spriteData.angle = angle;
	velocity = D3DXVECTOR2(muzzelVelocity*cos(angle), muzzelVelocity*sin(angle));
	ray = myLines::Ray(*getCenter(), velocity, maxRange);
	rayUpdated = false;
}

//Used to set stats of projectile
void Projectile::setStats(int damage, int minRange, int maxRange, int muzzelVelocity)
{
	this->damage = damage;
	this->minRange = minRange;
	this->maxRange = maxRange;
	this->muzzelVelocity = muzzelVelocity;
	active = false;
	visible = false;
}
void Projectile::setStaticHitTime(float in)
{
	maxTime = in;
	rayUpdated = true;
}