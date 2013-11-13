#include "LMap.h"

void LMap::update(float frameTime)
{
	VECTOR2 collisionVector;//get rid of later when using other collision detection function
	float angle, fT;
	for(int i = 0; i < levelNS::NUM_CHARACTERS; i++)
	{
		//getting hit
		for(int j = 0; j < levelNS::NUM_PROJECTILES; j++)
		{
			//if(characters[i]->collidesWith(*projectiles[i],collisionVector))
			//{
			//	//collision reaction of character hit
			//}
		}
		//being on level
		for(int j = 0; j < levelNS::NUM_TERRAIN; j++)
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
			//if(collidesWithMoving(&D3DXVECTOR2(c->getX()+c->getWidth(), c->getY()+c->getHeight()),const_cast<D3DXVECTOR2*>(&c->getVelocity()),t,angle,fT))
			if(this->checkCornerCollision(fT,t,c))
			{
				//stop them from falling through...
				characters[i]->update(fT);
				//characters[i]->setVisible(false);
				//characters[i]->setVelocity(VECTOR2(characters[i]->getVelocity().x,0));
				terrain[j]->collide(characters[i]);
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
	}

	//collision of bullets with terrain
	for(int i = 0; i < levelNS::NUM_PROJECTILES; i++)
	{
		for(int j = 0; j < levelNS::NUM_TERRAIN; j++)
		{
			//if(projectiles[i]->collidesWith(*terrain[j],collisionVector))
			//{
			//	//make the bullet stop...
			//	projectiles[i]->setVisible(false);
			//	projectiles[i]->setActive(false);
			//}
		}
	}
	/*for(int i = 0; i < levelNS::NUM_PROJECTILES; i++)
	{
		projectiles[i]->update(frameTime);
	}*/
	for(int i = 0; i < levelNS::NUM_CHARACTERS; i++)
	{
		characters[i]->update(frameTime);
		if(input->isKeyDown(VK_RIGHT))
		{
			characters[i]->right();
		}
		if(input->isKeyDown(VK_LEFT))
		{
			characters[i]->left();
		}
	}
	for(int i = 0; i < levelNS::NUM_PICKUP; i++)
	{
		dropped[i]->update(frameTime);
	}
	if(input->isKeyDown(VK_RETURN))
	{
		this->createFileFromLevel();
	}
}

bool LMap::checkCornerCollision(float& fT, TerrainElement* t, CharacterJ* c)
{
	float time1 = fT, time2 = fT, time3 = fT, time4 = fT, angle = fT;
	bool collide = false;
	if(collidesWithMoving(&D3DXVECTOR2(c->getX()+c->getWidth(), c->getY()+c->getHeight()),const_cast<D3DXVECTOR2*>(&c->getVelocity()),t,angle,time1))
		collide = true;
	//if(time1<0)
	//	time1 = fT;
	if(collidesWithMoving(&D3DXVECTOR2(c->getX()+c->getWidth(), c->getY()-c->getHeight()),const_cast<D3DXVECTOR2*>(&c->getVelocity()),t,angle,time2))
		collide = true;
	//if(time2<0)
	//	time2 = fT;
	if(collidesWithMoving(&D3DXVECTOR2(c->getX()-c->getWidth(), c->getY()+c->getHeight()),const_cast<D3DXVECTOR2*>(&c->getVelocity()),t,angle,time3))
		collide = true;
	//if(time3<0)
	//	time3 = fT;
	if(collidesWithMoving(&D3DXVECTOR2(c->getX()-c->getWidth(), c->getY()-c->getHeight()),const_cast<D3DXVECTOR2*>(&c->getVelocity()),t,angle,time4))
		collide = true;
	//if(time4<0)
	//	time4 = fT;
	fT = min(time1,min(time2,min(time3,time4)));
	return collide;
}

void LMap::draw()
{
	camera->centerPosition = *characters[0]->getCenter();
	/*for(int i = 0; i < levelNS::NUM_PROJECTILES; i++)
	{
		camera->draw(*projectiles[i]);
	}*/
	for(int i = 0; i < levelNS::NUM_CHARACTERS; i++)
	{
		camera->draw(*characters[i]);
		//characters[i]->draw();
	}
	for(int i = 0; i < levelNS::NUM_PICKUP; i++)
	{
		camera->draw(*dropped[i]);
		//dropped[i]->draw();
	}
	for(int i = 0; i < levelNS::NUM_TERRAIN; i++)
	{
		camera->draw(*terrain[i]);
		//terrain[i]->draw();
	}
}

bool LMap::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	for(int i = 0; i < levelNS::NUM_TERRAIN; i++)
	{
		if(!terrain[i]->initialize(gamePtr,textureM,ncols))
			return false;
	}
	if(!characters[0]->initialize(gamePtr,50,50,1,textureM))
		return false;
	camera = new Camera(GAME_WIDTH,GAME_HEIGHT,0,0,characters[0]->getX(),characters[0]->getY(),0.5);
	return true;
}

LMap::LMap(Input* i)
{
	input = i;
	for(int i = 0; i < levelNS::NUM_TERRAIN; i++)
	{
		terrain[i] = new StraightPath(0,000,VECTOR2(0,0));
		terrain[i]->setActive(false);
		terrain[i]->setVisible(false);
	}
	for(int i = 0; i < levelNS::NUM_CHARACTERS; i++)
	{
		characters[i] = new CharacterJ(50,50,VECTOR2(600,0));
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
	if(this->addedElements < levelNS::NUM_TERRAIN)
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
		if(collidesWithMovingRay(tempMP, tempMV, object->m[i], object->b[i], object->corners[i], object->corners[(3+i)%4], frameTime))
		{
			hit = true;
			angle = (i*PI/2)+ object->getRadians();
//			angle = (i%2?-1:1)*(i*PI/2)+ object->getRadians();
		}
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
			StraightPath* t = new StraightPath(height,width,VECTOR2(x,y));
			t->setDegrees(degree);
			this->addTerrain(t);
		}
		else
		{
			Wall* t = new Wall(height,width,VECTOR2(x,y));
			t->setDegrees(degree);
			this->addTerrain(t);
		}
		getline(fin,line);
	}
}

void LMap::createFileFromLevel()
{
	ofstream fout;
	fout.open("level.txt");
	for(int i = 0; i < levelNS::NUM_TERRAIN; i++)
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