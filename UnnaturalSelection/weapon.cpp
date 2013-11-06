//The implemintation of weapon
//By Michael Wiegand
// 11/4/2013
#include "weapon.h"

/**************************
INITALIZERS
**************************/
Weapon::Weapon(): Entity()
{
	weight = weaponNS::DEFALT_WEIGHT;
}

/*********************************************
ALL FUNCTIONS
**********************************************/
bool Weapon::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//Input1 is fire, input2 reload, input3 is for gunMod1, input4 is for gunMod2, input 5 is for gunMod3;
void Weapon::act(float frameTime, bool input1, bool input2, bool input3, bool input4, bool input5)
{

}
//Takes care of displaying
//void Weapon::draw()
//{
//
//}