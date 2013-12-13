#include "GearhartTurret.h"

Turret::~Turret()
{
	delete gun;
}

Turret::Turret(int height,int width, VECTOR2 position, Gun* g, Magazine* m,Character* c, turretPattern mo) : TerrainElement(height,width,position)
{
	yDirection = 0;
	motion = mo;
	sight = 500;
	target = c;
	gun = g;
	fireTime = 10;
	gun->loadNewMag(m);
	health = 10;
	target = c;
	if(mo==FOLLOW)
		this->setVelocity(VECTOR2(150,150));
	else
		this->setVelocity(VECTOR2(300,150));
	this->color = graphicsNS::WHITE;
	this->destructable = true;
	direction = (rand()%2==1?1:-1);
}

void Turret::update(float frameTime,bool fire)
{
	if(motion == FOLLOW || motion==CHASE)
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
	}
	float aimAngle = atan2(target->getCenterY()-this->gun->getCenterY(), target->getCenterX()-this->gun->getCenterX());
	gun->setAngle(aimAngle);
	if(fire)
		gun->act(frameTime,true,false,false,false,false);
	float xPos = this->getX() + this->getVelocity().x*frameTime*direction;
	if(motion==CHASE)
	{
		if(target->getY()<this->getY())
		{
			yDirection = -1;
		}
		else if(target->getY()>this->getY())
		{
			yDirection = 1;
		}
		else
		{
			yDirection = 0;
		}
	}
	float yPos = this->getY() + this->getVelocity().y*frameTime*yDirection;
	//here
	D3DXVECTOR2 tempDist = target->getCenter() - *const_cast<D3DXVECTOR2*>(getCenter());
	if(tempDist.x*tempDist.x + tempDist.y*tempDist.y > 200*200)
	{
		this->setX(xPos);
		this->setY(yPos);
	}
	gun->setX(this->getX());
	gun->setY(this->getY());
	this->generateSideEquations();
}