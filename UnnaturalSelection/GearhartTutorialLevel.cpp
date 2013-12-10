#include "GearhartTutorialLevel.h"

extern Gun* gunz[4];

TutorialLevel::TutorialLevel(Input* i, Graphics* g) : LMap(i,g,1000,1000,10,5,10,false)
{
	numDoors = 3;
	numTurrets = 5;
	currentDoor = 0;
	this->room2TurretsKilled = 0;
}

bool TutorialLevel::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, TextureManager *targetTM, TextureManager *turretTexture, Magazine* m)
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
		doors[1] = new TerrainElement(438,146,VECTOR2(1109,1483));
		doors[1]->initialize(gamePtr,textureM,ncols);
		doors[1]->generateSideEquations();
		LMap::addTerrain(doors[1]);
		//run and shoot door
		doors[2] = new TerrainElement(438,146,VECTOR2(4096,-1428));
		doors[2]->initialize(gamePtr,textureM,ncols);
		doors[2]->generateSideEquations();
		LMap::addTerrain(doors[2]);
		
		turrets = new Turret*[this->numTurrets];
		for(int i = 0; i < this->numTurrets; i++)
		{
			//turrets[i] = new Turret(VECTOR2(-1135,430+(i*100)),new Gun(*reinterpret_cast<Gun*>(characters[0]->currentWeapon)),new Magazine(30000,30000,30000,0,0,0,ONE,reinterpret_cast<Gun*>(characters[0]->currentWeapon)->mag->projectile));
			turrets[i] = new Turret(VECTOR2(-1135,430+(i*100)),gunz[0],m,characters[0]);
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

	//alter for situation
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
	for(int i = 0; i < 1; i++)
	{
		for(int j = 0; j < this->addedElements; j++)
		{
			if(turrets[i]!=terrain[j] && turrets[i]->collidesWith(*terrain[j],collisionVector))
			{
				turrets[i]->setVelocity(turrets[i]->getVelocity()*-1);
			}
		}
		if(turrets[i]->getHealth()<0 && turrets[i]->getActive())
		{
			turrets[i]->setActive(false);
			turrets[i]->setVisible(false);
			this->room2TurretsKilled++;
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