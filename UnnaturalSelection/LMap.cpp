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
	for(int i = 0; i < levelNS::NUM_ITEMS; i++)
	{
		items[i]->update(frameTime);
	}
	for(int i = 0; i < levelNS::NUM_PICKUP; i++)
	{
		dropped[i]->update(frameTime);
	}
}

void LMap::draw()
{
	/*for(int i = 0; i < levelNS::NUM_PROJECTILES; i++)
	{
		projectiles[i]->draw();
	}*/
	for(int i = 0; i < levelNS::NUM_CHARACTERS; i++)
	{
		characters[i]->draw();
	}
	for(int i = 0; i < levelNS::NUM_ITEMS; i++)
	{
		items[i]->draw();
	}
	for(int i = 0; i < levelNS::NUM_PICKUP; i++)
	{
		dropped[i]->draw();
	}
	for(int i = 0; i < levelNS::NUM_TERRAIN; i++)
	{
		terrain[i]->draw();
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
	return true;
}

LMap::LMap(Input* i)
{
	input = i;
	for(int i = 0; i < levelNS::NUM_TERRAIN; i++)
	{
		terrain[i] = new StraightPath(50,100,VECTOR2((i*150),500));
	}
	for(int i = 0; i < levelNS::NUM_CHARACTERS; i++)
	{
		characters[i] = new Character(50,50,VECTOR2(0,0));
	}
	for(int i = 0; i < levelNS::NUM_ITEMS; i++)
	{
		items[i] = new MapElement();
	}
	for(int i = 0; i < levelNS::NUM_PICKUP; i++)
	{
		dropped[i] = new PickUp();
	}
	/*for(int i = 0; i < levelNS::NUM_PROJECTILES; i++)
	{
		projectiles[i] = new Projectile(
	}*/
}

void LMap::collision()
{
	VECTOR2 collisionVector;
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
			if(characters[i]->collidesWith(*terrain[j],collisionVector))
			{
				//stop them from falling through...
				//characters[i]->setVisible(false);
				//characters[i]->setVelocity(VECTOR2(characters[i]->getVelocity().x,0));
				characters[i]->setY((terrain[j]->getCenterY() - terrain[j]->getWidth()/2)-characters[i]->getWidth()/2);
			}
		}
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