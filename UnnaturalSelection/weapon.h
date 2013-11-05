//This is the base class for all weapons and the interface
//By Michael Wiegand 
//11/4/2013
#ifndef WEAPON_H
#define WEAPON_H
#include "image.h"

//The constant values for Weapon
namespace weaponNS
{
	const int DEFALT_WEIGHT = 10;

}

//Extends image to allow for the image to be easy to handeled
class Weapon : public Image
{
public:
	//All varible used in interface
	int weight;//
	
	//All functions needed
	virtual void act(float frameTime, bool &input1, bool &input2, bool &input3, bool &input4, bool &input5){}
};





#endif