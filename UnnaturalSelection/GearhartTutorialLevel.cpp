#include "GearhartTutorialLevel.h"

extern Gun* gunz[4];

TutorialLevel::TutorialLevel(Input* i, Graphics* g) : LMap(i,g,1000,1000,100,5,10,false)
{
	numDoors = 5;
	levelScore = 0;
	numTurrets = 7;
	currentDoor = 0;
	this->room2TurretsKilled = 0;
	zoomValue = .5;
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
		doors[1] = new TerrainElement(128,2752,VECTOR2(-1603,68));
		doors[1]->initialize(gamePtr,textureM,ncols);
		doors[1]->generateSideEquations();
		LMap::addTerrain(doors[1]);
		doors[2] = new TerrainElement(128,2752,VECTOR2(-1603,800));
		doors[2]->initialize(gamePtr,textureM,ncols);
		doors[2]->generateSideEquations();
		LMap::addTerrain(doors[2]);
		//run and shoot door
		doors[3] = new TerrainElement(438,146,VECTOR2(4096,-1428));
		doors[3]->initialize(gamePtr,textureM,ncols);
		doors[3]->generateSideEquations();
		LMap::addTerrain(doors[3]);
		camera->zoom = zoomValue;
		turrets = new Turret*[this->numTurrets];

		turrets[0] = new Turret(100,100,VECTOR2(-700,-500),gunz[0],m,characters[0],FOLLOW);
		turrets[0]->initialize(gamePtr,turretTexture,ncols);
		turrets[0]->generateSideEquations();
		LMap::addTerrain(reinterpret_cast<TerrainElement*>(turrets[0]));
		
		for(int i = 1; i <4; i++)
		{
			turrets[i] = new Turret(100,100,VECTOR2(-700,100+(i*120)),gunz[0],m,characters[0]);
			turrets[i]->initialize(gamePtr,turretTexture,ncols);
			turrets[i]->generateSideEquations();
			LMap::addTerrain(reinterpret_cast<TerrainElement*>(turrets[i]));
		}
		for(int i = 4; i < 7;i++)
		{
			turrets[i] = new Turret(100,100,VECTOR2(1600,1694-((i-4)*1200)),gunz[0],m,characters[0],CHASE);
			turrets[i]->initialize(gamePtr,turretTexture,ncols);
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
	if(this->room2TurretsKilled>=this->numTurrets)
	{
		doors[3]->setActive(false);
		doors[3]->setVisible(false);
	}
	if(characters[0]->getCenterX() > 6607 && characters[0]->getCenterY() > 282)
	{
		this->levelDone = true;
	}
	//need to modify the implementation of this
	if(this->activeTargets==4)
	{
		//testing only
		//levelDone = false;

		//
		doors[0]->setActive(false);
		doors[0]->setVisible(false);
	}

	//alter for situation
	if(this->room2TurretsKilled == 1)
	{
		doors[1]->setActive(false);
		doors[1]->setVisible(false);
	}

	if(this->room2TurretsKilled == 4)
	{
		doors[2]->setActive(false);
		doors[2]->setVisible(false);
	}

	int fireNumber = 1+rand()%3;
	bool fire = false;
	
	for(int i = 0; i < this->numTurrets; i++)
	{
		if(characters[0]->getCenter().x>-1550 && i==0&&turrets[i]->getActive())
			turrets[i]->update(frameTime,true);
		if(characters[0]->getCenter().x>-1550 && i<=3&&this->room2TurretsKilled>=1&&turrets[i]->getActive())
		{
			if(i==fireNumber)
			{
				fire = true;
			}
			turrets[i]->update(frameTime,fire);
			fire = false;
		}
		if(i>3&&characters[0]->getX()>1259 && turrets[i]->getActive())
		{
 			if((i-4)==fireNumber)
			{
				fire = true;
			}
			turrets[i]->update(frameTime,fire);
		}
	}

	//collision with turrets on terrain
	VECTOR2 collisionVector;
	for(int i = 0; i < numTurrets; i++)
	{
		for(int j = 0; j < this->addedElements; j++)
		{
			if(turrets[i]!=terrain[j] && turrets[i]->collidesWith(*terrain[j],collisionVector))
			{
				turrets[i]->direction*=-1;
			}
		}
		if(turrets[i]->getHealth()<0 && turrets[i]->getActive())
		{
			turrets[i]->setActive(false);
			turrets[i]->setVisible(false);
			this->room2TurretsKilled++;
			levelScore+=100;
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

void TutorialLevel::givePlayerGun()
{
	LMap::givePlayerGun();
	for(int i = 0; i < this->numTurrets; i++)
	{
		testMag = new Magazine(3000, 1234567, 1234567, 0, 0, 0, ONE, testProjectile); 
		testGun = new Gun(*gunz[0]);
		testGun->loadNewMag(testMag);
		turrets[i]->gun = testGun;
		turrets[i]->gun->mag = testMag;
		this->mags[this->totalMags] = testMag;
		totalMags++;
	}
}