//The implemintation of gun
//By Michael Wiegand
// 11/4/2013
#include"gun.h"


/**************************
INITALIZERS
**************************/
Gun::Gun(int damage, int rpm, int minRange, int maxRange, int muzzelVelocity, int recoilReduction, int spread, float reloadTime, FireMode fireMode, MagType magType, Magazine* mag): damage(damage), fireRate(rpm), minRange(minRange), maxRange(maxRange), muzzelVelocity(muzzelVelocity), recoilReduction(recoilReduction), spread(spread), reloadTime(reloadTime), fireMode(fireMode), magType(magType)
{
	timeSinceLastFired = 0;
	chamberedProjectile = 0;
	gunState = NONE;
	gunTimer = 0;
	fireLocation = D3DXVECTOR2(50, 0);
	loadNewMag(mag);
}

/*********************************************
ALL FUNCTIONS
**********************************************/
//Input1 is fire, input2 reload, input3 is for gunMod1, input4 is for gunMod2, input 5 is for gunMod3;
void Gun::act(float frameTime, bool input1, bool input2, bool input3, bool input4, bool input5)
{
	timeSinceLastFired += frameTime;
	if(chamberedProjectile == 0 && timeSinceLastFired > fireRate.fireTime && mag != 0)
	{
		chamberNextProjectile();
	}
	if(chamberedProjectile != 0)
	{
		if(input1)
		{
			if(fireMode == AUTO)
			{
				if(gunState == NONE)
				{
					multiFire(frameTime);
					//fire(D3DXVECTOR2(getCenterX()+fireLocation.x*cos(spriteData.angle), getCenterY()+fireLocation.x*sin(spriteData.angle)), spriteData.angle + spread*PI*(((rand()%1000)-500)/1000.0)/180);
					timeSinceLastFired = 0;
					gunState = FIREING;
				}
				else if(gunState == FIREING)
				{
					multiFire(timeSinceLastFired);
				}
			}
		}
		else if(gunState == FIREING)
		{
			gunState = NONE;
		}
	}
	//if(timeSinceLastFired > 0 && input1 && gunState == NONE)
	//{
	//	fire(D3DXVECTOR2(getCenterX()+fireLocation.x*cos(spriteData.angle), getCenterY()+fireLocation.x*sin(spriteData.angle)), spriteData.angle + spread*PI*(((rand()%1000)-500)/1000.0)/180);
	//	timeSinceLastFired = 0;
	//	gunState = FIREING;
	//}
	//else if(timeSinceLastFired > fireRate.fireTime && input1 && gunState == FIREING)
	//{
	//	multiFire(timeSinceLastFired);
	//	/*timeSinceLastFired -= fireRate.fireTime;
	//	if(timeSinceLastFired > fireRate.fireTime)
	//	{
	//		multiFire(timeSinceLastFired);
	//	}*/
	//}

	//timeSinceLastFired += frameTime;
	//gunTimer -= frameTime;
	////Forces player to reclick fire when using semi auto weapons
	//canFireAgainSemiAuto = (!input1 && gunState == NONE); 

	////Handels what the gun should do if it is being used
	//if(gunState != NONE)
	//{
	//	if(gunState == FIREING)
	//	{
	//		if(fireMode == AUTO)
	//		{
	//			if(input1)
	//			{
	//				//NEEDS UPDATE
	//				if(timeSinceLastFired > fireRate.fireTime)
	//				{
	//					fire(frameTime);
	//					timeSinceLastFired -= fireRate.fireTime;
	//				}
	//			}
	//			else
	//			{
	//				gunState = NONE;
	//				gunTimer = 0;
	//			}
	//		}
	//		else
	//		{
	//			
	//		}
	//	}
	//	else if(gunState == RELOADING)
	//	{


	//	}
	//}
	//
	//if(gunState == NONE)
	//{
	//	if(input1 && timeSinceLastFired > fireRate.fireTime)
	//	{
	//		if(fireMode == AUTO)
	//		{
	//			timeSinceLastFired = 0;
	//			gunState = FIREING;
	//			gunTimer = fireRate.fireTime;
	//			fire(frameTime);
	//			return;
	//		}
	//		else if(canFireAgainSemiAuto)
	//		{
	//			timeSinceLastFired = 0;
	//			gunState = FIREING;
	//			gunTimer = fireRate.fireTime*fireMode;
	//			fire(frameTime);
	//			return;
	//		}
	//	}
	//	if(input2)
	//	{
	//		gunState = RELOADING;
	//		gunTimer = reloadTime;
	//		return;
	//	}

	//}
}
void Gun::fire(D3DXVECTOR2 initialPos, float angle)
{
	chamberedProjectile->fire(initialPos, angle);
	chamberedProjectile = 0;

}
void Gun::multiFire(float frameTime)
{
	int count = frameTime/fireRate.fireTime;
	timeSinceLastFired -= fireRate.fireTime*count;
	while(count > 0)
	{
		fire(D3DXVECTOR2(getCenterX()+(fireLocation.x+((count-1)*fireRate.fireTime*chamberedProjectile->muzzelVelocity))*cos(spriteData.angle), getCenterY()+(fireLocation.x+((count-1)*fireRate.fireTime*chamberedProjectile->muzzelVelocity))*sin(spriteData.angle)), spriteData.angle + spread*PI*(((rand()%1000)-500)/1000.0)/180);
		chamberNextProjectile();
		count--;
	}
	chamberedProjectile = 0;
}
void Gun::reload(float frameTime)
{

}
void Gun::switchMag(float frameTime, Magazine* newMag)
{

}
void Gun::recoil(float frameTime)
{

}
//Updates all the projectile in the clip to meet the guns stats
void Gun::loadNewMag(Magazine* newMag)
{
	mag = newMag;
	newMag->setProjectileStats(damage, minRange, maxRange, muzzelVelocity);
	if(chamberedProjectile == 0)
	{
		chamberNextProjectile();
	}
}
//Puts the next projectile in the chamber and removes it from the mag
void Gun::chamberNextProjectile()
{
	chamberedProjectile = mag->getNextProjectile();
}