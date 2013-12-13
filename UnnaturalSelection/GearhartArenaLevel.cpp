#include "GearhartArenaLevel.h"

extern Gun* gunz[4];
extern int weaponSelected;

ArenaLevel::ArenaLevel(Input* i, Graphics* g,int numKills) : LMap(i,g,1000,1000,10,10,10,false)
{
	killsToWin = numKills;
	totalKills = 0;
	levelScore=0;
}

bool ArenaLevel::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, TextureManager *targetTM, TextureManager *turretTM, Magazine* m)
{
	if(!LMap::initialize(gamePtr,width,height,ncols,textureM,targetTM))
		return false;
	for(int i = 0; i < this->totalCharacters; i++)
	{
		if(this->characters[i]!=0)
		{
			int v(2);
			this->characters[i]->body->color = D3DCOLOR_ARGB(255, v*(rand()%(255/v)), v*(rand()%(255/v)), v*(rand()%(255/v)));
			testProjectile = new Projectile(turretTM, gamePtr, 32, 8, entityNS::CIRCLE, 1);
			testMag = new Magazine(3000, 16, 16, 0, 0, 0, ONE, testProjectile); 
			testGun = new Gun(*gunz[weaponSelected]);
			testGun->loadNewMag(testMag);
			this->characters[i]->currentWeapon = testGun;
			this->characters[i]->currentMag = testMag;
			this->mags[i] = testMag;
		}
	}
	this->mapStartTime=120;
	this->mapTime = 120;
	return true;
}

void ArenaLevel::update(float frameTime)
{
	LMap::update(frameTime);
	if(numKills >= killsToWin)
	{
		this->levelDone = true;
	}
	for(int i = 0; i < this->totalCharacters; i++)
	{
		if(characters[i]->getX()<minX || characters[i]->getX()>maxX || characters[i]->getY()>maxY)
		{
			this->chooseSpawnPoint(characters[i]);
		}
	}
}