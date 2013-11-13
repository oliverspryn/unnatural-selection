#include "LMap.h"

void LMap::update(float frameTime)
{
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
	}
	for(int i = 0; i < levelNS::NUM_PICKUP; i++)
	{
		dropped[i]->update(frameTime);
	}
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
	camera = new Camera(GAME_WIDTH,GAME_HEIGHT,0,0,characters[0]->getX(),characters[0]->getY(),1);
	return true;
}

LMap::LMap(Input* i)
{
	input = i;
	for(int i = 0; i < levelNS::NUM_TERRAIN-1; i++)
	{
		terrain[i] = new StraightPath(50,5000,VECTOR2((i*5000),500));
	}
	terrain[levelNS::NUM_TERRAIN-1] = new Wall(1000,50,VECTOR2(500,-500));
	for(int i = 0; i < levelNS::NUM_CHARACTERS; i++)
	{
		characters[i] = new CharacterJ(50,50,VECTOR2(0,0));
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
}

void LMap::collision()
{
	VECTOR2 collisionVector;
	float angle, frameTime;
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
			if(collidesWithMoving(characters[i],terrain[j],angle,frameTime))
			{
				//stop them from falling through...
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
}

bool LMap::collidesWithMoving(Entity* moving, TerrainElement* object, float &angle, float &frameTime)
{

	//Gives the place that intersects on the circle
	//float x = (k+k*(a*a)-sqrt(r*r*a*a+r*r*a*a*a*a))/(1+a*a);
	//float y = sqrt(r*r-(x-k)*(x-k))+h;
	//Equation for one 
	bool hit(false);
	for(int i(0); i < 4; i++)
	{
		if(collidesWithMovingRay(moving, object->m[i], object->b[i], object->corners[i], object->corners[(3+i)%4], frameTime))
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

bool LMap::collidesWithMovingRay(Entity* moving, float slope, float b, D3DXVECTOR2 corner1, D3DXVECTOR2 corner2, float &frameTime)
{
	//the angle between the box and projectile
	float m1 = moving->getVelocity().y/moving->getVelocity().x;
	float x1 = moving->getCenterX();
	float y1 = moving->getCenterY();
	float b1 = y1 - m1*x1;

	float x = getXIntercept(m1, b1, slope, b);

	//If the plane is horizontal 
	if(corner1.y == corner2.y)
	{
		if(min(corner1.x, corner2.x) < x1 && x1 < max(corner1.x, corner2.x))
		//makes sure it is with in the frame time
		if(abs(frameTime*moving->getVelocity().x) > abs(x-x1))
		{
			frameTime = (x1-x)/moving->getVelocity().x;
			return true;
		}else{
			return false;
		}
	}

	if(min(corner1.y, corner2.y) < m1*x + b1 && m1*x + b1 < max(corner1.y, corner2.y))
	if(min(corner1.x, corner2.x) < x1 + abs(moving->getVelocity().x*frameTime) && x1 - abs(moving->getVelocity().x*frameTime) < max(corner1.x, corner2.x))
	//makes sure it is with in the frame time
	if(abs(frameTime*moving->getVelocity().x) > abs(x-x1))
	{
		frameTime = (x1-x)/moving->getVelocity().x;
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