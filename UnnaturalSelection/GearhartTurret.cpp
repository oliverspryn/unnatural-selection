#include "GearhartTurret.h"

Turret::~Turret()
{
	delete gun;
}

Turret::Turret(VECTOR2 position, Gun* g, Magazine* m,Character* c) : TerrainElement(100,100,position)
{
	target = c;
	gun = g;
	gun->loadNewMag(m);
	health = 10;
	this->setVelocity(VECTOR2(100,0));
	this->color = graphicsNS::WHITE;
	this->destructable = true;
	direction = 0;
}

void Turret::update(float frameTime)
{
	gun->act(frameTime,true,false,false,false,false);
	if(target->getX()<this->getX())
	{
		direction = -1;
	}
	else if(target->getX()>this->getX())
	{
		direction = 1;
	}
	else
	{
		direction = 0;
	}
	float xPos = this->getX() + this->getVelocity().x*frameTime*direction;
	this->setX(xPos);
}