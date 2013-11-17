#include "LMap.h"

LMap::~LMap()
{
	for(int i = 0; i < numTerrain; i++)
	{
		SAFE_DELETE(terrain[i])
	}
	delete[] terrain;
	for(int i = 0; i < numMags; i++)
	{
		SAFE_DELETE(mags[i]);
	}
	delete[] mags;
}

void LMap::collide(Character* ent, TerrainElement* t, int side)
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
		ent->setX((t->getCenterX()-(t->getWidth()+ent->getWidth())/2)-ent->getWidth()/2);
		break;
	case 2:
		ent->setVelocity(VECTOR2(ent->getVelocity().x,0));
		ent->setY(((t->getCenterY() + (t->getHeight()+ent->getHeight())/2)-ent->getHeight()/2));
		break;
	case 3:
		ent->setVelocity(VECTOR2(0,ent->getVelocity().y));
		ent->setX((t->getCenterX()+(t->getWidth()-ent->getWidth())/2)+ent->getWidth()/2);
		break;
	}
}

void LMap::update(float frameTime)
{
	VECTOR2 collisionVector;//get rid of later when using other collision detection function
	float angle, fT;
	if(input->isKeyDown('1'))
	{
		camera->zoom = max(0.1, camera->zoom - frameTime*.5);
	}
	if(input->isKeyDown('2'))
	{
		camera->zoom = min(10, camera->zoom + frameTime*.5);
	}
	if(!editor)
	{
		for(int i = 0; i < levelNS::NUM_CHARACTERS; i++)
		{
			characters[i]->cursor->update(frameTime);
			//getting hit
			for(int j = 0; j < levelNS::NUM_PROJECTILES; j++)
			{
				//if(characters[i]->collidesWith(*projectiles[i],collisionVector))
				//{
				//	//collision reaction of character hit
				//}
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
	//collision of bullets with terrain
	//for(int i = 0; i < levelNS::NUM_PROJECTILES; i++)
	//{
	//	for(int j = 0; j < numTerrain; j++)
	//	{
	//		if(terrain[j]!=0)
	//		{
	//			//if(projectiles[i]->collidesWith(*terrain[j],collisionVector))
	//			//{
	//			//	//make the bullet stop...
	//			//	projectiles[i]->setVisible(false);
	//			//	projectiles[i]->setActive(false);
	//			//}
	//		}
	//	}
	//}
	/*for(int i = 0; i < levelNS::NUM_PROJECTILES; i++)
	{
		projectiles[i]->update(frameTime);
	}*/
	if(!editor)
	{
		for(int i = 0; i < levelNS::NUM_CHARACTERS; i++)
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
	for(int i = 0; i < levelNS::NUM_PICKUP; i++)
	{
		dropped[i]->update(frameTime);
	}
	if(input->isKeyDown(VK_RETURN) && editor)
	{
		this->createFileFromLevel();
	}

	//temp UpdateFunction and collisions
	for(int i(0); i < numMags && mags[i] != 0; i++)
	{
		for(int j(0); j < mags[i]->projArrayIndex; j++)
		{
			if(!mags[i]->projArray[j]->rayUpdated)
			{
				float tempTime = frameTime;
				for(int k(0); k < numTerrain && terrain[k] != 0; k++)
				{
					if(projectileCollide(*mags[i]->projArray[j], *terrain[k], tempTime))
					{
						mags[i]->projArray[j]->setActive(false);
						mags[i]->projArray[j]->setVisible(false);
					}
				}
			}
		}
		mags[i]->updateMagsProjectiles(frameTime);
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
	if(!editor)
		camera->centerPosition = characters[0]->getCenter();
	
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
		for(int i = 0; i < levelNS::NUM_CHARACTERS; i++)
		{
			camera->draw(*characters[i]->body);
			camera->draw(*characters[i]->head);
			characters[i]->cursor->setXY(input->getMouseX(),input->getMouseY());
			//camera->draw(*characters[i]->cursor);
			characters[i]->cursor->draw();
			characters[i]->draw();
			if(characters[i]->currentWeapon != 0)
			{
				camera->draw(*characters[i]->currentWeapon);
			}
		}
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

bool LMap::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	if(!editor)
	{
		for(int i = 0; i < levelNS::NUM_CHARACTERS; i++)
		{
			characters[i] = new Character(gamePtr,graphics);
			characters[i]->initialize();
			characters[i]->setXY(100,300);
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
	if(!editor)
		camera = new Camera(GAME_WIDTH,GAME_HEIGHT,0,0,characters[0]->body->getX(),characters[0]->body->getY(),0.5);
	else
		camera = new Camera(GAME_WIDTH,GAME_HEIGHT,0,0,GAME_WIDTH/2,GAME_HEIGHT/2,0.5);
	return true;
}

LMap::LMap(Input* i, Graphics* g, int numT, int numM, bool edit)
{
	numTerrain = numT;
	numMags = numM;
	mags = new Magazine*[this->numMags];
	terrain = new TerrainElement*[this->numTerrain];
	editor = edit;
	this->levelFileName="testLevel.txt";
	graphics = g;
	input = i;
	for(int i = 0; i < numTerrain; i++)
	{
		terrain[i] = 0;
		//terrain[i]->setActive(false);
		//terrain[i]->setVisible(false);
	}
	for(int i = 0; i < numMags; i++)
	{
		mags[i] = 0;
	}
	for(int i = 0; i < levelNS::NUM_PICKUP; i++)
	{
		dropped[i] = new PickUp();
	}
	/*for(int i = 0; i < levelNS::NUM_PROJECTILES; i++)
	{
		projectiles[i] = new Projectile(
	}*/
	for(int i = 0; i < levelNS::NUM_SPAWNS; i++)
	{
		spawnPoints[i] = new VECTOR2(i,i);
	}
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

void LMap::buildFromFile(std::string fileName)
{
	fstream fin;
	fin.open(fileName);
	string line = "";
	getline(fin,line);
	int height = 0, width = 0, x = 0, y = 0;
	double degree = 0;
	while(!fin.fail() && line != "--")
	{
		std::cout << line << std::endl;
		height = atoi(line.c_str());
		getline(fin,line);
		width = atoi(line.c_str());
		getline(fin,line);
		x = atoi(line.c_str());
		getline(fin,line);
		y = atoi(line.c_str());
		getline(fin,line);
		degree = atof(line.c_str());
		if(width>=height)
		{
			TerrainElement* t = new TerrainElement(height,width,VECTOR2(x,y));
			t->setDegrees(degree);
			this->addTerrain(t);
		}
		else
		{
			TerrainElement* t = new TerrainElement(height,width,VECTOR2(x,y));
			t->setDegrees(degree);
			this->addTerrain(t);
		}
		getline(fin,line);
	}
}

void LMap::createFileFromLevel()
{
	ofstream fout;
	fout.open(this->levelFileName);
	fout << addedElements << std::endl;
	for(int i = 0; i < numTerrain; i++)
	{
		if(terrain[i]->getActive())
		{
			fout << terrain[i]->getHeight() << std::endl;
			fout << terrain[i]->getWidth() << std::endl;
			fout << terrain[i]->getX() << std::endl;
			fout << terrain[i]->getY() << std::endl;
			fout << terrain[i]->getDegrees() << std::endl;
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