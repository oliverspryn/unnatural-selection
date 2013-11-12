#ifndef __LMAP_H
#define __LMAP_H

#include "projectile.h"
#include "terrainElement.h"
#include "camera.h"

class Character : public Entity
{
public:
	Character(int height, int width, VECTOR2 center)
	{
		spriteData.height = height;
		spriteData.width = width;
		spriteData.x = center.x;
		spriteData.y = center.y;
		this->velocity = VECTOR2(0,100);
		collisionType = entityNS::BOX;
		edge.left = (width/2)*-1;
		edge.right = width/2;
		edge.top = (height/2)*-1;
		edge.bottom = (height/2);
		mass = terrainNS::MASS;
	}
	void update(float frameTime)
	{
		spriteData.y += velocity.y * frameTime;
		spriteData.x += velocity.x * frameTime;
	}
	void right()
	{
		velocity.x = 50;
	}

};

class PickUp : public Entity
{};

class GameType
{};

namespace levelNS
{
	const int NUM_PROJECTILES = 10;
	const int NUM_CHARACTERS = 10;
	const int NUM_SPAWNS = 10;
	const int NUM_TERRAIN = 10;
	const int NUM_PICKUP = 10;
}

class LMap
{
	Projectile* projectiles[levelNS::NUM_PROJECTILES];
	Character* characters[levelNS::NUM_CHARACTERS];
	//MapElement* items[levelNS::NUM_ITEMS];//things like spawn points, no collision
	TerrainElement* terrain[levelNS::NUM_TERRAIN];
	PickUp* dropped[levelNS::NUM_PICKUP];//if they are touching it and choose to pick it up pick it up
	VECTOR2* spawnPoints[levelNS::NUM_SPAWNS];
	int player;
	//has a pointer to input so that it can easily run all the updating and what not
	Input* input;
	Camera* camera;

public:
	LMap(Input* i);
	void update(float frameTime);
	void draw();
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void collision();
};

#endif