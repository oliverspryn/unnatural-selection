#include "GearhartBossLevel.h"

BossLevel::BossLevel(Input* i, Graphics* g) : LMap(i,g,1000,1000,10,50,1000)
{
	pressed = false;
	numKills=0;
	levelScore=0;
}

void BossLevel::update(float frameTime)
{
	if(numKills ==3)
	{
		this->levelDone = true;
	}
	LMap::update(frameTime);
	//if(!pressed && input->isKeyDown(VK_RETURN))
	//{
	//	numKills++;
	//	pressed = true;
	//}
	//if(pressed && !input->isKeyDown(VK_RETURN))
	//{
	//	pressed = false;
	//}
	if(numKills>0&&numKills<2) 
	{
		for(int i = 3; i < 15; i++)
		{
			if(terrain[i]!=0)
			{
				terrain[i]->setActive(false);
				terrain[i]->setVisible(false);
			}
		}
		for(int i = 0; i < this->numTargets; i++)
		{
			if(targets[i]!=0)
			{
				targets[i]->setActive(false);
				targets[i]->setVisible(false);
			}
		}
	}
	if(numKills==2)
	{
		for(int i = 15; i < this->numTerrain;i++)
		{
			if(terrain[i]!=0)
			{
				terrain[i]->setActive(false);
				terrain[i]->setVisible(false);
			}
		}
	}
}

bool BossLevel::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, TextureManager *targetTM, TextureManager *turretTM, Magazine* m)
{
	if(!LMap::initialize(gamePtr,width,height,ncols,textureM,targetTM,turretTM,m))
		return false;
	characters[0]->setX(this->spawnPoints[1]->getX());
	characters[0]->setY(this->spawnPoints[1]->getY());
	if(characters[1]!=0)
	{
		characters[1]->setX(this->spawnPoints[0]->getX());
		characters[1]->setY(this->spawnPoints[0]->getY());
	}
	this->mapStartTime=120;
	this->mapTime = 120;
	return true;
}