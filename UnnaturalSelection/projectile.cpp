//The implemintation of projectile
//By Michael Wiegand
// 11/4/2013

#include "projectile.h"

/**************************
INITALIZERS
**************************/
Projectile::Projectile(TextureManager* tm, Game* gamePtr, int width, int height, int ncoils, int hitBoxRadius)
{
	initialize(gamePtr, width, height, ncoils, tm);
	active = false;
	visible = false;
	this->radius = hitBoxRadius;
}


/*********************************************
ALL FUNCTIONS
**********************************************/
//Used for copy constructor
void Projectile::operator=(Projectile& in)
{
	spriteData = in.spriteData;
	setStats(in.damage, in.minRange, in.maxRange, in.muzzelVelocity);
}
void Projectile::update(float frameTime)
{
	lifeTime += frameTime;
	distance += muzzelVelocity*frameTime;
	//The bullet will stop 
	if(distance > maxRange)
	{
		active = false;
		visible = false;
		return;
	}

	spriteData.x += frameTime*velocity.x;
	spriteData.y += frameTime*velocity.y;
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
	spriteData.x = initialPos.x;
	spriteData.y = initialPos.y;
	spriteData.angle = angle;
	velocity = D3DXVECTOR2(muzzelVelocity*cos(angle), muzzelVelocity*sin(angle));

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