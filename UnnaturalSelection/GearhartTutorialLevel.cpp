#include "GearhartTutorialLevel.h"

TutorialLevel::TutorialLevel(Input* i, Graphics* g) : LMap(i,g)
{
	numDoors = 3;
	numTurrets = 5;
	currentDoor = 0;
	this->room2TurretsKilled = 0;
}

//need to fix issues with door collision detection not quite working
bool TutorialLevel::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, TextureManager *targetTM, TextureManager *turretTexture)
{
	if(LMap::initialize(gamePtr,width,height,ncols,textureM,targetTM))
	{
		doors = new TerrainElement*[numDoors];
		//target door
		doors[0] = new TerrainElement(438,146,VECTOR2(-1726,-1542));
		doors[0]->initialize(gamePtr,textureM,ncols);
		doors[0]->generateSideEquations();
		LMap::addTerrain(doors[0]);
		//duck and cover door
		//doors[1] = new TerrainElement(438,146,VECTOR2(1109,1483));
		//doors[1]->initialize(gamePtr,textureM,ncols);
		//doors[1]->generateSideEquations();
		//LMap::addTerrain(doors[1]);
		////run and shoot door
		//doors[2] = new TerrainElement(438,146,VECTOR2(4096,-1428));
		//doors[2]->initialize(gamePtr,textureM,ncols);
		//doors[2]->generateSideEquations();
		//LMap::addTerrain(doors[2]);
		
		turrets = new Turret*[this->numTurrets];
		for(int i = 0; i < this->numTurrets; i++)
		{
			turrets[i] = new Turret(VECTOR2(-1135,-540));
			turrets[i]->initialize(gamePtr,300,420,1,turretTexture);
			turrets[i]->generateSideEquations();
			LMap::addTerrain(reinterpret_cast<TerrainElement*>(turrets[i]));
		}
		return true;
	}
	else
		return false;
}

void TutorialLevel::update(float frameTime)
{
	LMap::update(frameTime);
	//maybe modify later to check in a different way...
	if(characters[0]->getCenterX() > 6607 && characters[0]->getCenterY() > 282)
	{
		this->levelDone = true;
	}
	//need to modify the implementation of this
	if(this->activeTargets==0)
	{
		//testing only
		//levelDone = false;

		//
		doors[0]->setActive(false);
		doors[0]->setVisible(false);
	}

	if(this->room2TurretsKilled == 5)
	{
		doors[1]->setActive(false);
		doors[1]->setVisible(false);
	}

	for(int i = 0; i < this->numTurrets; i++)
	{
		turrets[i]->update(frameTime);
	}

	//collision with turrets on terrain
	VECTOR2 collisionVector;
	for(int i = 0; i < this->numTurrets; i++)
	{
		for(int j = 0; j < this->addedElements; j++)
		{
			if(turrets[i]!=terrain[j] && turrets[i]->collidesWith(*terrain[j],collisionVector))
			{
				turrets[i]->setVelocity(turrets[i]->getVelocity()*-1);
			}
		}
		//need to make turrets killable
		//going to double detection on turrets... should probably change later
		for(int j = 0; j < this->totalCharacters; j++)
		{
			for(int k = 0; k < this->numMags && mags[j]!=0; k++)
			{
				float tempTime = frameTime;
				for(int l = 0; l < mags[j]->projArrayIndex; j++)
				{
					if(!mags[j]->projArray[l]->rayUpdated)
					{
						//check collisions with turret
						if(projectileCollide(*mags[j]->projArray[l], *turrets[i], tempTime))
						{
							//do stuff with turret getting damage
						}
					}
				}
			}
		}
	}
}

void TutorialLevel::draw()
{
	LMap::draw();
	for(int i = 0; i < this->numTurrets; i++)
	{
		if(turrets[i]!=0)
			;//this->camera->draw(*turrets[i]);
	}
}