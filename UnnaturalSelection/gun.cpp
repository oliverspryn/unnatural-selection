//The implemintation of gun
//By Michael Wiegand
// 11/4/2013
#include"gun.h"


/**************************
INITALIZERS
**************************/
Gun::Gun(int damage, int rpm, int minRange, int maxRange, int muzzelVelocity, int recoilReduction, int spread, float reloadTime, FireMode fireMode, MagType magType, Magazine* mag): damage(damage), fireRate(rpm), minRange(minRange), maxRange(maxRange), muzzelVelocity(muzzelVelocity), recoilReduction(recoilReduction), spread(spread), reloadTime(reloadTime), fireMode(fireMode), magType(magType), mag(mag)
{
	timeSinceLastFired = 0;
	gunState = NONE;
	gunTimer = 0;
	fireLocation = D3DXVECTOR2(50, 0);
}

/*********************************************
ALL FUNCTIONS
**********************************************/
//Input1 is fire, input2 reload, input3 is for gunMod1, input4 is for gunMod2, input 5 is for gunMod3;
void Gun::act(float frameTime, bool input1, bool input2, bool input3, bool input4, bool input5)
{
	timeSinceLastFired += frameTime*input1;
	if(!input1 && timeSinceLastFired > fireRate.fireTime)
	{
		gunState = NONE;
	}
	if(timeSinceLastFired > 0 && input1 && gunState == NONE)
	{
		fire(frameTime);
		timeSinceLastFired = 0;
		gunState = FIREING;
	}
	else if(timeSinceLastFired > fireRate.fireTime && input1 && gunState == FIREING)
	{
		fire(frameTime);
		timeSinceLastFired = 0;
	}

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
void Gun::fire(float frameTime)
{
	mag->fire(D3DXVECTOR2(getCenterX()+fireLocation.x*cos(spriteData.angle), getCenterY()+fireLocation.x*sin(spriteData.angle)), spriteData.angle + spread*PI*(((rand()%1000)-500)/1000.0)/180);
}
void Gun::multiFire(float frameTime)
{

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
