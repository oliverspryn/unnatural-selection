//The implemintation of gun
//By Michael Wiegand
// 11/4/2013
#include"gun.h"


/**************************
INITALIZERS
**************************/
Gun::Gun(): fireRate(gunNS::BASE_RPM)
{
	spriteData.width = 128;           // size of Ship1
    spriteData.height = 32;
    spriteData.x = 100;                   // location on screen
    spriteData.y = 100;
    spriteData.rect.bottom = 128;    // rectangle to select parts of an image
    spriteData.rect.right = 32;
    velocity.x = 0;
    velocity.y = 0;
	spriteData.angle = 0;
    radius = 0;
	collisionType = entityNS::NONE;
 
	using namespace gunNS;

	Gun(BASE_DAMAGE, BASE_RPM, BASE_MIN_RANGE, BASE_MAX_RANGE, BASE_MUZZEL_VELOCITY, BASE_RECOIL_REDUCTION, BASE_SPREAD, BASE_RELOAD_TIME, AUTO, ONE, 0);
}
Gun::Gun(int damage, int rpm, int minRange, int maxRange, int muzzelVelocity, int recoilReduction, int spread, float reloadTime, FireMode fireMode, MagType magType, Magazine* mag): damage(damage), fireRate(rpm), minRange(minRange), maxRange(maxRange), muzzelVelocity(muzzelVelocity), recoilReduction(recoilReduction), spread(spread), reloadTime(reloadTime), fireMode(fireMode), magType(magType), mag(mag)
{
	timeSinceLastFired = 0;
	gunState = NONE;
	gunTimer = 0;
}

/*********************************************
ALL FUNCTIONS
**********************************************/
//Input1 is fire, input2 reload, input3 is for gunMod1, input4 is for gunMod2, input 5 is for gunMod3;
void Gun::act(float frameTime, bool &input1, bool &input2, bool &input3, bool &input4, bool &input5)
{
	;
}
void Gun::fire()
{
	;
}