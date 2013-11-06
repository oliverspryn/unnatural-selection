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
void Projectile::act(float* frameTime)
{
	

}

bool Projectile::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	spriteData.angle = angle;
	return Entity::initialize(gamePtr, width, height, ncols, textureM);
}