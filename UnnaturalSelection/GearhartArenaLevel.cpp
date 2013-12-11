#include "GearhartArenaLevel.h"

ArenaLevel::ArenaLevel(Input* i, Graphics* g,int numKills) : LMap(i,g,1000,1000,10,10,10,false)
{
	killsToWin = numKills;
	totalKills = 0;
}

bool ArenaLevel::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, TextureManager *targetTM, TextureManager *turretTM, Magazine* m)
{
	if(LMap::initialize(gamePtr,width,height,ncols,textureM,targetTM))
	{
		return true;
	}
	else
		return false;
}

void ArenaLevel::update(float frameTime)
{
	LMap::update(frameTime);
	if(numKills >= killsToWin)
	{
		this->levelDone = true;
	}
}