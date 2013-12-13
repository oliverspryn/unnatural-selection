#include "LMap.h"

extern Gun* gunz[4];
extern int weaponSelected;

LMap::~LMap()
{
	for(int t = 0; t < addedElements; t++)
	{
		SAFE_DELETE(terrain[t]);
	}
	//delete[] terrain;
	for(int i = 0; i < numMags; i++)
	{
		SAFE_DELETE(mags[i]);
	}
	//delete[] mags;
	for(int i = 0; i < numCharacters; i++)
	{
		SAFE_DELETE(characters[i]);
	}
	//delete[] characters;
	for(int i = 0; i < numSpawns; i++)
	{
		SAFE_DELETE(spawnPoints[i]);
	}
	//delete[] spawnPoints;
}

void LMap::collide(Character* ent, TerrainElement* t, int side)
{
	if(t->type = 'B')
	{
		switch(side)
		{
		case 0:
			if(ent->getVelocityY() >= 0)
			{
				ent->standingOn = t;
				ent->setVelocity(VECTOR2(ent->getVelocity().x,0));
				ent->setY((t->getCenterY() - (t->getHeight()+ent->getHeight())/2)-ent->getHeight()/2);
			}
			break;
		case 1:
			ent->setVelocity(VECTOR2(0,ent->getVelocity().y));
			ent->setX((t->getCenterX()-(t->getWidth()+ent->getWidth())/2)-24.1);
			break;
		case 2:
			ent->setVelocity(VECTOR2(ent->getVelocity().x,0));
			ent->setY(((t->getCenterY() + (t->getHeight()+ent->getHeight())/2)-ent->getHeight()/2));
			break;
		case 3:
			ent->setVelocity(VECTOR2(0,ent->getVelocity().y));
			ent->setX((t->getCenterX()+(t->getWidth()-ent->getWidth())/2)+24.1);
			break;
		}
	}
}

void LMap::update(float frameTime)
{
	if(mapTime > 0)
	{
		mapTime -= frameTime;
	}else{
		mapTime = 0;
	}
	//should be removed later
	/*if(this->activeTargets==0)
	{
		this->levelDone=true;
	}*/
	if(guns&&first)
	{
		this->givePlayerGun();
		first = false;
	}
	VECTOR2 collisionVector;//get rid of later when using other collision detection function
	float angle, fT;
#if defined(DEBUG) | defined(_DEBUG)
	if(input->isKeyDown('1'))
	{
		camera->zoom = max(0.1, camera->zoom - frameTime*.5);
	}
	if(input->isKeyDown('2'))
	{
		camera->zoom = min(10, camera->zoom + frameTime*.5);
	}
#endif
	if(!editor)
	{
		for(int i = 0; i < this->totalCharacters; i++)
		{
			if(characters[i]!=0)
			{
				if(characters[i]->standingOn!=0 && !characters[i]->standingOn->getActive())
				{
					characters[i]->standingOn = 0;
				}
				characters[i]->cursor->update(frameTime);
				//getting hit
				for(int j = 0; j < levelNS::NUM_PROJECTILES; j++)
				{
					//if(characters[i]->collidesWith(*projectiles[i],collisionVector))
					//{
					//	//collision reaction of character hit
					//}
				}

				//target collision
				for(int j = 0; j < numTargets; j++)
				{
					if(targets[j]!=0)
					{
						fT = frameTime;
						auto c = characters[i];
						auto t = targets[j];
						if(characters[i]->body->collidesWith(*targets[j],collisionVector))
						{
							int side = targets[j]->getCollisionSide(collisionVector*-1);//put in call to side finder function
							collide(characters[i],targets[j],side);
						}
					}
				}

				//being on level
				for(int j = 0; j < numTerrain; j++)
				{
					if(terrain[j]!=0)
					{
						fT = frameTime;
						//if(collidesWithMoving(&D3DXVECTOR2(characters[i]->getX(), characters[i]->getY()-characters[i]->getHeight()),const_cast<D3DXVECTOR2*>(&characters[i]->getVelocity()),terrain[j],angle,fT))
						//{
						//	//stop them from falling through...
						//	characters[i]->update(fT);
						//	//characters[i]->setVisible(false);
						//	//characters[i]->setVelocity(VECTOR2(characters[i]->getVelocity().x,0));
						//	terrain[j]->collide(characters[i]);
						//}
						auto c = characters[i];
						auto t = terrain[j];
						if(characters[i]->body->collidesWith(*terrain[j],collisionVector))
						{
							int side = terrain[j]->getCollisionSide(collisionVector*-1);//put in call to side finder function
							collide(characters[i],terrain[j],side);
						}
					}
				}
				//keep track of corner locations for each
				//keep track of equations for all sides

				//can they pick up an item?
				for(int j = 0; j < levelNS::NUM_PICKUP; j++)
				{
					if(characters[i]->collidesWith(*dropped[j],collisionVector))
					{
						if(input->isKeyDown(VK_UP))
						{
							//have player pickup item
						}
					}
				}
				//characters[i]->update(frameTime);
			}
		}
	}
	for(int i = 0; i < levelNS::NUM_PICKUP; i++)
	{
		dropped[i]->update(frameTime);
	}

	//temp UpdateFunction and collisions
	for(int i(0); i < numMags && mags[i] != 0; i++)
	{
		//update projectiles
		for(int j(0); j < mags[i]->projArrayIndex; j++)
		{
			if(mags[i]->projArray[j]->getActive())
			{
				if(!mags[i]->projArray[j]->rayUpdated)
				{
					float tempTime = frameTime;
					for(int k(0); k < numTerrain && terrain[k] != 0; k++)
					{
						if(!terrain[k]->destructable && projectileCollide(*mags[i]->projArray[j], *terrain[k], tempTime))
						{
							mags[i]->projArray[j]->setActive(false);
							mags[i]->projArray[j]->setVisible(false);
						}
						if(terrain[k]->destructable && i<totalCharacters && collidesWithTurret(terrain[k],mags[i]->projArray[j], tempTime))
						{
							mags[i]->projArray[j]->setActive(false);
							mags[i]->projArray[j]->setVisible(false);
							terrain[k]->setHealth(terrain[k]->getHealth()-mags[i]->projArray[j]->damage);
						}
					}
				}
				float tempTime = frameTime;
				for(int k(0); k < totalTargets; k++)
				{
					if(targets[k] != 0 && targets[k]->getActive())
					{
						if(projectileCollide(*mags[i]->projArray[j], *targets[k], tempTime))
						{
							mags[i]->projArray[j]->setActive(false);
							mags[i]->projArray[j]->setVisible(false);
							targets[k]->setHealth(targets[k]->getHealth() - mags[i]->projArray[j]->damage);
							if(targets[k]->getHealth() < 0)
							{
								targets[k]->setActive(false);
								targets[k]->setVisible(false);
								this->activeTargets--;
								this->levelScore+=50;
							}
						}
					}
				}
				//here is some work in progress code stuffs
				for(int k(0); k < totalCharacters; k++)
				{
					if(characters[k] != 0 && characters[k]->body->getActive())
					{
						//stuff here do things
						//collidesWithCharacter(Entity* c, Entity* p, float& fT)
						float fT = frameTime;
						if(k!=i&&collidesWithCharacter(characters[k],mags[i]->projArray[j],fT))
						{
							mags[i]->projArray[j]->setVisible(false);
							mags[i]->projArray[j]->setActive(false);
							characters[k]->charFrameTime=fT;
							characters[k]->healthPoints-=mags[i]->projArray[j]->damage;
							if(characters[k]->invertColorCount == 0)
							{
								characters[k]->body->color = D3DCOLOR_ARGB(510,255,255,255) - characters[k]->body->color;
							}
							characters[k]->invertColorCount = 5;


							if(characters[k]->healthPoints <= 0)
							{
								this->chooseSpawnPoint(characters[k]);
								//if it was killed by the player
								if(i==0)
								{
									numKills++;
									this->levelScore+=100;
								}
							}
						}
					}
				}
			}
		}
		mags[i]->updateMagsProjectiles(frameTime);
	}
	//update character
	if(!editor)
	{
		for(int i = 0; i < totalCharacters; i++)
		{
			if(characters[i]!=0)
			{
				if(characters[i]->charFrameTime >= 0)
				{
					characters[i]->update(characters[i]->charFrameTime);
				}else{
					characters[i]->update(frameTime);
				}
				characters[i]->charFrameTime = -1;
			}
		}
	}
}

//bool LMap::checkCornerCollision(float& fT, TerrainElement* t, Character* c)
//{
//	float time1 = fT, time2 = fT, time3 = fT, time4 = fT, angle = fT;
//	bool collide = false;
//	//if(collidesWithMoving(&D3DXVECTOR2(c->getX()+c->getWidth(), c->getY()+c->getHeight()),const_cast<D3DXVECTOR2*>(&c->getVelocity()),t,angle,time1))
//	//	collide = true;
//	////if(time1<0)
//	////	time1 = fT;
//	//if(collidesWithMoving(&D3DXVECTOR2(c->getX()+c->getWidth(), c->getY()-c->getHeight()),const_cast<D3DXVECTOR2*>(&c->getVelocity()),t,angle,time2))
//	//	collide = true;
//	////if(time2<0)
//	////	time2 = fT;
//	//if(collidesWithMoving(&D3DXVECTOR2(c->getX()-c->getWidth(), c->getY()+c->getHeight()),const_cast<D3DXVECTOR2*>(&c->getVelocity()),t,angle,time3))
//	//	collide = true;
//	////if(time3<0)
//	////	time3 = fT;
//	//if(collidesWithMoving(&D3DXVECTOR2(c->getX()-c->getWidth(), c->getY()-c->getHeight()),const_cast<D3DXVECTOR2*>(&c->getVelocity()),t,angle,time4))
//	//	collide = true;
//	//if(time4<0)
//	//	time4 = fT;
//	//myLines::Ray motionRays(D3DXVECTOR2(c->getX()+c->getWidth(), c->getY()+c->getHeight()), c->getVelocity(), sqrt(c->getVelocity().x*c->getVelocity().x + c->getVelocity().y*c->getVelocity().y)*fT);
//	//if(t->collidesWithRay(&motionRays, time1)) collide = true;
//	//motionRays.setPosition(D3DXVECTOR2(c->getX()+c->getWidth(), c->getY()-c->getHeight()));
//	//if(t->collidesWithRay(&motionRays, time2)) collide = true;
//	//motionRays.setPosition(D3DXVECTOR2(c->getX()-c->getWidth(), c->getY()+c->getHeight()));
//	//if(t->collidesWithRay(&motionRays, time3)) collide = true;
//	//motionRays.setPosition(D3DXVECTOR2(c->getX()-c->getWidth(), c->getY()-c->getHeight()));
//	//if(t->collidesWithRay(&motionRays, time4)) collide = true;
//
//	//fT = min(time1,min(time2,min(time3,time4)));
//	return collide;
//}

void LMap::draw()
{
	//if(!editor)
		//if(characters[0]!=0)
			//camera->centerPosition = characters[0]->getCenter();
	
	for(int i = 0; i < numTargets; i++)
	{
		if(targets[i]!=0)
		{
			camera->draw(*targets[i]);
		}
	}

	for(int i = 0; i < numMags; i++)
	{
		if(mags[i] != 0)
		{
			for(int j(0); j < mags[i]->size + 1; j++)
			{
				camera->draw(*mags[i]->projArray[j]);
			}
		}else{
			break;
		}
	}

	if(!editor)
	{
		for(int i = 0; i < totalCharacters; i++)
		{
			if(characters[i]!=0)
			{
				if(i > 0)
				{
				AI* tempAI = reinterpret_cast<AI*>(characters[i]);
				//camera->draw(tempAI->hb->indicator2, graphicsNS::ORANGE);
				camera->draw(tempAI->hb->indicator1, graphicsNS::WHITE);
				camera->draw(tempAI->hb->bar, graphicsNS::BLACK);				
				}

				camera->draw(*characters[i]->body);
//				camera->draw(*characters[i]->head);
				characters[i]->cursor->setXY(input->getMouseX(),input->getMouseY());
				//camera->draw(*characters[i]->cursor);
				if(i == 0)
				{
					characters[i]->cursor->draw();
				}
				characters[i]->draw();
				if(characters[i]->currentWeapon != 0)
				{
					camera->draw(*characters[i]->currentWeapon, false, characters[i]->faceDir > 0);
				}
			}
		}
	}
	if(editor)
	{
		for(int i = 0; i < totalSpawns; i++)
			camera->draw(*spawnPoints[i]);
	}
	for(int i = 0; i < levelNS::NUM_PICKUP; i++)
	{
		camera->draw(*dropped[i]);
		//dropped[i]->draw();
	}
	for(int i = 0; i < numTerrain; i++)
	{
		if(terrain[i]!=0)
			camera->draw(*terrain[i]);
		//terrain[i]->draw();
	}
}

bool LMap::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, TextureManager *targetTM, TextureManager *turretTM,Magazine* m)
{
	for(int i = 0; i < totalCharacters; i++)
	{
		if(characters[i]!=0)
		{
			characters[i]->initialize();
			chooseSpawnPoint(characters[i]);
		}
	}
	for(int i = 0; i < numTerrain; i++)
	{
		if(terrain[i]!=0)
		{
			if(!terrain[i]->initialize(gamePtr,textureM,ncols))
				return false;
		}
	}
	for(int i = 0; i < numSpawns; i++)
	{
		if(spawnPoints[i]!=0)
		{
			if(!spawnPoints[i]->initialize(gamePtr,textureM,ncols))
				return false;
		}
	}
	for(int i = 0; i < numTargets; i++)
	{
		if(targets[i]!=0)
		{
			if(!targets[i]->initialize(gamePtr,targetTM,ncols))
				return false;
		}
	}
	camera = new Camera(GAME_WIDTH,GAME_HEIGHT,0,0,(maxX+minX)/2,(maxY+minY)/2,1);
	//if(!editor)
//		camera = new Camera(GAME_WIDTH,GAME_HEIGHT,0,0,characters[0]->body->getX(),characters[0]->body->getY(),0.5);
	//else
//		camera = new Camera(GAME_WIDTH,GAME_HEIGHT,0,0,GAME_WIDTH/2,GAME_HEIGHT/2,0.5);
	return true;
}

void LMap::chooseSpawnPoint(Character* c)
{
	//do stuffs here
	int point = rand()%totalSpawns;
	while(spawnPoints[point]==0 || !spawnPoints[point]->getActive())
	{
		point = rand()%totalSpawns;
	}
	c->setVelocityX(0);
	c->setVelocityY(0);
	c->setX(spawnPoints[point]->getX());
	c->setY(spawnPoints[point]->getY());
	c->healthPoints = c->startHealth;
}

LMap::LMap(Input* i, Graphics* g, int numT, int numM, int numC, int numS, int numTarget, bool edit)
{
	mapStartTime = 60;
	mapTime = 60;
	guns = !edit;
	totalMags=0;
	first = true;
	numKills = 0;
	targetsDestroyed = true;
	activeTargets = 0;
	totalTargets = 0;
	levelDone = false;
	totalTargets = 0;
	totalSpawns = 0;
	this->numTargets = numTarget;
	totalCharacters = 0;
	minX = 0;
	minY = 0;
	maxX = 0;
	maxY = 0;
	numTerrain = numT;
	numMags = numM;
	numCharacters = numC;
	numSpawns = numS;
	mags = new Magazine*[this->numMags];
	terrain = new TerrainElement*[this->numTerrain];
	characters = new Character*[this->numCharacters];
	spawnPoints = new TerrainElement*[this->numSpawns];
	targets = new TerrainElement*[this->numTargets];
	editor = edit;
	this->levelFileName="testLevel.txt";
	graphics = g;
	input = i;
	for(int i = 0; i < numTerrain; i++)
	{
		terrain[i] = 0;
	}
	for(int i = 0; i < numMags; i++)
	{
		mags[i] = 0;
	}
	for(int i = 0; i < numCharacters; i++)
	{
		characters[i] = 0;
	}
	for(int i = 0; i < numSpawns; i++)
	{
		spawnPoints[i] = 0;
	}
	for(int i = 0; i < numTargets; i++)
	{
		targets[i] = 0;
	}
	//maybe get rid of pickups...
	for(int i = 0; i < levelNS::NUM_PICKUP; i++)
	{
		dropped[i] = new PickUp();
	}
	/*for(int i = 0; i < levelNS::NUM_PROJECTILES; i++)
	{
		projectiles[i] = new Projectile(
	}*/
	addedElements = 0;
}

void LMap::collision()
{
	
}

bool LMap::addTerrain(TerrainElement* t)
{
	bool added = true;
	if(this->addedElements < numTerrain)
	{
		terrain[addedElements] = t;
		terrain[addedElements]->setActive(true);
		terrain[addedElements]->setVisible(true);
		addedElements++;
		if(t->getX() < minX)
			minX = t->getX();
		if(t->getX()+t->getWidth() > maxX)
			maxX = t->getX()+t->getWidth();
		if(t->getY() < minY)
			minY = t->getY();
		if(t->getY()+t->getHeight() > maxY)
			maxY = t->getY()+t->getHeight();
	}
	else
		added = false;
	return added;
}

bool LMap::addSpawnPoint(TerrainElement* pt)
{
	bool added = true;
	if(this->totalSpawns<this->numSpawns)
	{
		spawnPoints[totalSpawns] = pt;
		totalSpawns++;
	}
	else
		added = false;
	return added;
}

bool LMap::addCharacter(Character* c)
{
	bool added = true;
	if(this->totalCharacters<this->numCharacters)
	{
		characters[totalCharacters] = c;
		//this->numCharacters++;
		totalCharacters++;
	}
	else
		added = false;
	return added;
}

bool LMap::addTarget(TerrainElement* target)
{
	bool added = true;
	if(this->totalTargets<this->numTargets)
	{
		targets[totalTargets] = target;
		totalTargets++;
		activeTargets++;
	}
	else
		added = false;
	return added;
}

bool LMap::collidesWithMoving(D3DXVECTOR2* movingPos, D3DXVECTOR2* movingVelocity, TerrainElement* object, float &angle, float &frameTime)
{
	D3DXVECTOR2 tempMV = *movingVelocity;
	D3DXVECTOR2 tempMP = *movingPos;

	//Gives the place that intersects on the circle
	//float x = (k+k*(a*a)-sqrt(r*r*a*a+r*r*a*a*a*a))/(1+a*a);
	//float y = sqrt(r*r-(x-k)*(x-k))+h;
	//Equation for one 
	bool hit(false);
	for(int i(0); i < 4; i++)
	{
//		if(collidesWithMovingRay(tempMP, tempMV, object->m[i], object->b[i], object->corners[i], object->corners[(3+i)%4], frameTime))
//		{
//			hit = true;
//			angle = (i*PI/2)+ object->getRadians();
////			angle = (i%2?-1:1)*(i*PI/2)+ object->getRadians();
//		}
	}
	//Only one Plane
  	/*if(collidesWithMovingRay(moving, object->m[2], object->b[2], object->corners[2], object->corners[(3+2)%4], collisionVector, frameTime))
	{
		return true;
	}*/
	if(hit)
	{
		return true;
	}
	return false;
	
}

bool LMap::collidesWithMovingRay(D3DXVECTOR2 movingPos, D3DXVECTOR2 movingVelocity, float slope, float b, D3DXVECTOR2 corner1, D3DXVECTOR2 corner2, float &frameTime)
{

	if(movingVelocity.x == 0)
	{
		/*movingVelocity.x = movingVelocity.y;
		movingVelocity.y = 0;
		float xtemp = movingPos.x;
		movingPos.x = movingPos.y;
		movingPos.y = xtemp;
		b = -1*b/slope;
		slope = 1/slope;*/
		/*xtemp = corner1.x;
		corner1.x = corner1.y;
		corner1.y = xtemp;
		xtemp = corner2.x;
		corner2.x = corner2.y;
		corner2.y = xtemp;
		std::swap(corner1, corner2);*/
	}
	//the angle between the box and projectile
	float m1 = movingVelocity.y/movingVelocity.x;
	float x1 = movingPos.x;
	float y1 = movingPos.y;
	float b1 = y1 - m1*x1;

	float x = getXIntercept(m1, b1, slope, b);

	//If the plane is horizontal 
	if(corner1.y == corner2.y)
	{
		if(min(corner1.x, corner2.x) <= x1 && x1 <= max(corner1.x, corner2.x))
		//makes sure it is with in the frame time
		if(abs(frameTime*movingVelocity.x) >= abs(x-x1))
		{
			frameTime = (x1-x)/movingVelocity.x;
			return true;
		}else{
			return false;
		}
	}

	if(min(corner1.y, corner2.y) <= m1*x + b1 && m1*x + b1 <= max(corner1.y, corner2.y))
	if(min(corner1.x, corner2.x) <= x1 + abs(movingVelocity.x*frameTime) && x1 - abs(movingVelocity.x*frameTime) <= max(corner1.x, corner2.x))
	//makes sure it is with in the frame time
	if(abs(frameTime*movingVelocity.x) >= abs(x-x1))
	{
		frameTime = (x1-x)/movingVelocity.x;
		return true;
	}else{
		return false;
	}

	return false;
}

float LMap::getXIntercept(float m1, float b1, float m2, float b2)
{
	return ((b2-b1)/(m1-m2));
}

//void LMap::buildFromFile(std::string fileName)
//{
//	fstream fin;
//	fin.open(fileName);
//	string line = "";
//	getline(fin,line);
//	int height = 0, width = 0, x = 0, y = 0;
//	double degree = 0;
//	while(!fin.fail() && line != "--")
//	{
//		height = atoi(line.c_str());
//		getline(fin,line);
//		width = atoi(line.c_str());
//		getline(fin,line);
//		x = atoi(line.c_str());
//		getline(fin,line);
//		y = atoi(line.c_str());
//		getline(fin,line);
//		degree = atof(line.c_str());
//		TerrainElement* t = new TerrainElement(height,width,VECTOR2(x,y));
//		t->setDegrees(degree);
//		t->initialize(this,&terrainTexture,0);
//		t->generateSideEquations();
//		this->addTerrain(t);
//		getline(fin,line);
//	}
//}

void LMap::createFileFromLevel(int terNum, int spawn, float zoom)
{
	ofstream fout;
	fout.open(this->levelFileName);
	fout << zoom << std::endl;
	fout << terNum << std::endl;
	fout << spawn << std::endl;
	for(int i = 0; i < numTerrain; i++)
	{
		if(terrain[i]!=0 && terrain[i]->getActive())
		{
			fout << terrain[i]->getHeight() << std::endl;
			fout << terrain[i]->getWidth() << std::endl;
			fout << terrain[i]->getX() << std::endl;
			fout << terrain[i]->getY() << std::endl;
			fout << terrain[i]->getDegrees() << std::endl;
			fout << terrain[i]->color << std::endl;
		}
	}
	for(int i = 0; i < this->numSpawns; i++)
	{
		if(spawnPoints[i]!=0 && spawnPoints[i]->getActive())
		{
			fout << spawnPoints[i]->getX() << std::endl;
			fout << spawnPoints[i]->getY() << std::endl;
		}
	}
	for(int i = 0; i < this->numTargets; i++)
	{
		if(targets[i]!=0 && targets[i]->getActive())
		{
			fout << targets[i]->getX() << std::endl;
			fout << targets[i]->getY() << std::endl;
			fout << targets[i]->color << std::endl;
			fout << targets[i]->getHealth() << std::endl;
		}
	}
	fout.close();
}

bool LMap::collidesWithCharacter(Character* c, TerrainElement* t, float& fT)
{
	bool hit = false;
	float frameTime = fT;
	for(int j(0); j < 4; j++)
	{
		myLines::Ray movingLine(c->corners[j], c->body->getVelocity(), c->getVelMagnitude()*frameTime);
		for(int i(0); i < 4; i++)
		{
			if(movingLine.getTimeOfIntersectRay(t->sides[i], frameTime))
			{
				hit = true;
			}
		}
	}
	if(hit)
	{
		fT = frameTime;
	}
	return hit;
}

bool LMap::projectileCollide(Projectile &proj, TerrainElement &terra, float &frameTime)
{
	bool hit(false);
	//D3DXVECTOR2 pos(proj.getX(), proj.getY());
	//myLines::Ray movingLine(pos, proj.getVelocity(), proj.muzzelVelocity*frameTime);
	float ct = frameTime;
	for(int i(0); i < 4; i++)
	{
		float ft = frameTime;
		if(proj.ray.getTimeOfIntersectRay(terra.sides[i], ft))
		{
			if(0 <= ft && ft < ct)
			{
				hit = true;
				ct = ft;
			}
		}
	}
	
	if(hit)
	{
		frameTime = ct;
		proj.setStaticHitTime(frameTime);
		return true;
	}
	//proj.setStaticHitTime(frameTime);
	return false;
}

bool LMap::collidesWithCharacter(Character* c, Projectile* p, float& fT)
{
	for(int i(0); i < 4; i++)
	{
		VECTOR2 characterStartP = VECTOR2(c->getCenterX(),c->getCenterY()+20*i-30);
		VECTOR2 characterV = c->getVelocity();
		VECTOR2 bulletStartP = VECTOR2(p->getCenterX(),p->getCenterY());
		VECTOR2 bulletV = p->getVelocity();
		//end positions
		VECTOR2 characterEndP = characterStartP + fT*characterV;
		VECTOR2 bulletEndP = bulletStartP + fT*bulletV;
		//difference between ends
		VECTOR2 diff = bulletEndP-characterEndP;

		//needs work here
		float d = (p->getHeight()/2)+(c->getWidth()/2);
		d/=2;
		float magDiff = graphics->Vector2Length(&diff);

		if((magDiff*magDiff)<(d*d))
		{
			//calculate time of collision
			VECTOR2 A = bulletStartP-characterStartP;
			VECTOR2 B = bulletV-characterV;
			float aDotB = graphics->Vector2Dot(&A,&B);
			float aSquared = graphics->Vector2Dot(&A,&A);
			float bSquared = graphics->Vector2Dot(&B,&B);
			float top = (-1*aDotB)-sqrt(aDotB-(bSquared*(aSquared-(d*d))));
			fT = top/bSquared;
			return true;
		}
	}
	return false;
}
bool LMap::collidesWithTurret(TerrainElement* t,Projectile* p, float& fT)
{
	for(int i(0); i < 4; i++)
	{
		VECTOR2 characterStartP = VECTOR2(t->getCenterX(),t->getCenterY()+20*i-30);
		VECTOR2 characterV = t->getVelocity();
		VECTOR2 bulletStartP = VECTOR2(p->getCenterX(),p->getCenterY());
		VECTOR2 bulletV = p->getVelocity();
		//end positions
		VECTOR2 characterEndP = characterStartP + fT*characterV;
		VECTOR2 bulletEndP = bulletStartP + fT*bulletV;
		//difference between ends
		VECTOR2 diff = bulletEndP-characterEndP;

		//needs work here
		float d = (p->getHeight()/2)+(t->getWidth()/2);
		d/=2;
		float magDiff = graphics->Vector2Length(&diff);

		if((magDiff*magDiff)<(d*d))
		{
			//calculate time of collision
			VECTOR2 A = bulletStartP-characterStartP;
			VECTOR2 B = bulletV-characterV;
			float aDotB = graphics->Vector2Dot(&A,&B);
			float aSquared = graphics->Vector2Dot(&A,&A);
			float bSquared = graphics->Vector2Dot(&B,&B);
			float top = (-1*aDotB)-sqrt(aDotB-(bSquared*(aSquared-(d*d))));
			fT = top/bSquared;
			return true;
		}
	}
	return false;
}

void LMap::givePlayerGun()
{
	int ammos = 5*((weaponSelected/3)-1);
	if(ammos == 0)
	{
		ammos = 5;
	}
	testMag = new Magazine(3000, ammos, ammos, 0, 0, 0, ONE, testProjectile);
	testGun = new Gun(*gunz[weaponSelected]);
	testGun->loadNewMag(testMag);
	this->characters[0]->currentWeapon = testGun;
	this->characters[0]->currentMag = testMag;
	this->characters[0]->currentWeapon = testGun;
	this->characters[0]->currentMag = testMag;
	this->mags[0] = testMag;
	totalMags++;
	for(int i(1); i < totalCharacters; i++)
	{
		totalMags++;
		testMag = new Magazine(3000, 8, 8, 0, 0, 0, ONE, testProjectile); 
		testGun = new Gun(*gunz[rand()%3+1]);
		testGun->loadNewMag(testMag);
		this->characters[i]->currentWeapon = testGun;
		this->characters[i]->currentMag = testMag;
		this->mags[i] = testMag;

	}
}