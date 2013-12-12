#include "GearhartTurret.h"

Turret::~Turret()
{
	delete gun;
}

Turret::Turret(VECTOR2 position, Gun* g, Magazine* m,Character* c) : TerrainElement(100,100,position)
{
	target = c;
	gun = g;
	fireTime = 10;
	gun->loadNewMag(m);
	health = 10;
	target = c;
	this->setVelocity(VECTOR2(100,0));
	this->color = graphicsNS::WHITE;
	this->destructable = true;
	direction = 0;
}

void Turret::update(float frameTime)
{
	if(target->getCenter().x>-1550 && target->getCenter().y<1150)
	{
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
		float aimAngle = atan2(target->getCenterY()-this->getCenterY(), target->getCenterX()-this->getCenterX());
		gun->setAngle(aimAngle);
		gun->act(frameTime,true,false,false,false,false);
		gun->setX(this->getX());
		gun->setY(this->getY());
		float xPos = this->getX() + this->getVelocity().x*frameTime*direction;
		this->setX(xPos);
	}
}