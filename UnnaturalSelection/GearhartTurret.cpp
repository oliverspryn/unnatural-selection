#include "GearhartTurret.h"

Turret::~Turret()
{
	delete[] shots;
}

Turret::Turret(VECTOR2 position) : TerrainElement(100,100,position)
{
	health = 0;
	this->setVelocity(VECTOR2(1000,0));
	shots = new Projectile*[10];
	for(int i = 0; i < 10; i++)
	{
		//shots[i] = new Projectile(
	}
	this->color = graphicsNS::WHITE;
	this->destructable = true;
}

void Turret::update(float frameTime)
{
	float xPos = this->getX() + this->getVelocity().x*frameTime;
	this->setX(xPos);
}