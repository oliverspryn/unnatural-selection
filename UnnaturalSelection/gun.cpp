//The implemintation of gun
//By Michael Wiegand
// 11/4/2013
#include"gun.h"


/**************************
INITALIZERS
**************************/
Gun::Gun(const Gun& in): damage(in.damage), fireRate(in.fireRate.RPM), minRange(in.minRange), maxRange(in.maxRange), muzzelVelocity(in.muzzelVelocity), recoilReduction(in.recoilReduction), spread(in.spread), reloadTime(in.reloadTime), fireMode(in.fireMode), magType(in.magType)
{
	//Gun(in.damage, in.fireRate.RPM, in.minRange, in.maxRange, in.muzzelVelocity, in.recoilReduction, in.spread, in.reloadTime, in.fireMode, in.magType);
	timeSinceLastFired = 0;
	mag = 0;
	isMagInGun = false;
	chamberedProjectile = 0;
	gunState = NONE;
	gunTimer = 0;
	fireLocation = D3DXVECTOR2(50, 0);
	burstCount = 0;
	if(in.initialized)
	{
		input = in.input;
		audio = in.audio;
		graphics = in.graphics;
		textureManager = in.textureManager;
		spriteData.texture = textureManager->getTexture();
        float width = textureManager->getWidth();     // use full width of texture
        spriteData.width = width;
        float height = textureManager->getHeight();   // use full height of texture
        spriteData.height = height;
		cols = in.cols;                               // if 0 cols use 1

        // configure spriteData.rect to draw currentFrame
        spriteData.rect.left = (currentFrame % cols) * spriteData.width;
        // right edge + 1
        spriteData.rect.right = spriteData.rect.left + spriteData.width;
        spriteData.rect.top = (currentFrame / cols) * spriteData.height;
        // bottom edge + 1
        spriteData.rect.bottom = spriteData.rect.top + spriteData.height;
		initialized = true;
	}
}
Gun::Gun(int damage, int rpm, int minRange, int maxRange, int muzzelVelocity, int recoilReduction, int spread, float reloadTime, int fireMode, MagType magType): damage(damage), fireRate(rpm), minRange(minRange), maxRange(maxRange), muzzelVelocity(muzzelVelocity), recoilReduction(recoilReduction), spread(spread), reloadTime(reloadTime), fireMode(fireMode), magType(magType)
{
	timeSinceLastFired = 0;
	mag = 0;
	isMagInGun = false;
	chamberedProjectile = 0;
	gunState = NONE;
	gunTimer = 0;
	fireLocation = D3DXVECTOR2(50, 0);
	burstCount = 0;
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
		if(fireMode == AUTO)
		{
			if(input1)
			{
				if(gunState == NONE)
				{
					multiFire(max(fireRate.fireTime, frameTime));
					timeSinceLastFired = 0;
					gunState = FIREING;
				}
				else if(gunState == FIREING)
				{
					multiFire(timeSinceLastFired);
				}
				
			}
			else if(gunState == FIREING)
			{
				gunState = NONE;
			}
		}
		else//For Burst fire weapons
		{
			if(gunState == NONE)
			{
				if(input1)
				{
					burstCount = fireMode;
					multiFire(frameTime);
					timeSinceLastFired = 0;
					gunState = FIREING;
				}
			}
			else if(gunState == FIREING && burstCount > 0)
			{
				multiFire(timeSinceLastFired);
			}
			else if(!input1)
			{
				gunState = NONE;
			}
		}

	}
	else if(!isMagInGun)
	{
		timeSinceLastFired = 0;
	}
}
void Gun::fire(D3DXVECTOR2 initialPos, float angle)
{
	chamberedProjectile->fire(initialPos, angle);
	chamberedProjectile = 0;
	audio->playCue(GUN_SHOT);
}
void Gun::multiFire(float frameTime)
{
	int count = frameTime/fireRate.fireTime;
	float recoilTime = frameTime/count;
	if(fireMode != AUTO)//accounts for burst fire
	{
		if(gunState == NONE && count == 0)
		{
			count = 1;
		}
		count = min(burstCount, count);
		burstCount -= count;
	}
	timeSinceLastFired -= fireRate.fireTime*count;
	while(count > 0)
	{
		chamberNextProjectile();
		if(chamberedProjectile != 0)
		{
			float fireAngle = spriteData.angle + spread*PI*(((rand()%1000)-500)/1000.0)/180;
			D3DXVECTOR2 fp(getCenterX() + cos(spriteData.angle)*fireLocation.x - sin(spriteData.angle)*fireLocation.y, getCenterY() + cos(spriteData.angle)*fireLocation.y + sin(spriteData.angle)*fireLocation.x);
			//fire(fp, fireAngle);
			fire(fp + D3DXVECTOR2(((count-1)*fireRate.fireTime*chamberedProjectile->muzzelVelocity)*cos(fireAngle), ((count-1)*fireRate.fireTime*chamberedProjectile->muzzelVelocity)*sin(fireAngle)), fireAngle);
			recoil(recoilTime);
		}
		count--;
	}
}
//Takes the mag out of the gun
void Gun::removeMag()
{
	isMagInGun = false;
}
//Places the mag in the gun
void Gun::loadMag()
{
	if(mag != 0)
	{
		isMagInGun = true;
		chamberNextProjectile();
	}
}
void Gun::recoil(float frameTime)
{
	if(mag != 0)
	{
		frameTime = 1;
		int recoil = mag->recoil - recoilReduction;
		if(recoil > 0)
		{
			setRadians(getRadians() + frameTime*((rand()%recoil)-(510*recoil/1000))*PI/180);
		}
	}
}
//Updates all the projectile in the clip to meet the guns stats
void Gun::loadNewMag(Magazine* newMag)
{
	mag = newMag;
	isMagInGun = true;
	newMag->setProjectileStats(damage, minRange, maxRange, muzzelVelocity);
	chamberNextProjectile();
}
//Puts the next projectile in the chamber and removes it from the mag
void Gun::chamberNextProjectile()
{
	if(chamberedProjectile == 0 && isMagInGun)
	{
		chamberedProjectile = mag->getNextProjectile();
	}
}