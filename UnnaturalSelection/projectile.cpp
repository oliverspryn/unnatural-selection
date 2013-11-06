//The implemintation of projectile
//By Michael Wiegand
// 11/4/2013

#include "projectile.h"

/**************************
INITALIZERS
**************************/
Projectile::Projectile(int damage, int minRange, int maxRange, int muzzelVelocity, int angle, VECTOR2 position, TextureManager* tm, int hitBoxRadious, Game* gamePtr)
{
	this->initialize(gamePtr, tm->getWidth(), tm->getHeight(), entityNS::CIRCLE, tm);
}
Projectile::Projectile()
{

}


/*********************************************
ALL FUNCTIONS
**********************************************/
void Projectile::update(float frameTime)
{
	spriteData.x += frameTime*velocity.x;
	spriteData.y += frameTime*velocity.y;
	lifeTime += frameTime;
	distance += muzzelVelocity*frameTime;
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