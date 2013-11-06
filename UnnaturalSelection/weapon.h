//This is the base class for all weapons and the interface
//By Michael Wiegand 
//11/4/2013
#ifndef WEAPON_H
#define WEAPON_H
#define WIN32_LEAN_AND_MEAN
#include "entity.h"

//The constant values for Weapon
namespace weaponNS
{
	const int DEFALT_WEIGHT = 10;

}

//Extends image to allow for the image to be easy to handeled
class Weapon : public Entity
{
public:
	/*********************************************
	ALL VARIBLES
	**********************************************/
	int weight;//
	
	/*********************************************
	ALL FUNCTIONS
	**********************************************/
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	//Input1 is fire, input2 reload, input3 is for gunMod1, input4 is for gunMod2, input 5 is for gunMod3;
	virtual void act(float frameTime, bool input1, bool input2, bool input3, bool input4, bool input5);
	//Takes care of displaying
	//virtual void draw();
	void setAngle(float angle)
	{
		spriteData.angle = angle;
	}
	/**************************
	INITALIZERS
	**************************/
	Weapon();

};





#endif