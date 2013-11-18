#ifndef __LMAP_H
#define __LMAP_H
#define WIN32_LEAN_AND_MEAN
#include "terrainElement.h"
#include "Character.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
//std::cout;
//std::endl;
using std::fstream;
using std::ofstream;
using std::string;
#include "camera.h"

class CharacterJ : public Entity
{
public:
	float gravity;
	CharacterJ(int height, int width, VECTOR2 center)
	{
		spriteData.height = height;
		spriteData.width = width;
		spriteData.x = center.x;
		spriteData.y = center.y;
		this->velocity = VECTOR2(0,150);
		collisionType = entityNS::BOX;
		edge.left = (width/2)*-1;
		edge.right = width/2;
		edge.top = (height/2)*-1;
		edge.bottom = (height/2);
		mass = terrainNS::MASS;
		gravity = 20;
	}
	void update(float frameTime)
	{
		//velocity.y += frameTime*gravity;
		spriteData.y += velocity.y * frameTime;
		spriteData.x += velocity.x * frameTime;
	}
	void right()
	{
		velocity.x = 100;
	}
	void left()
	{
		velocity.x = -100;
	}
};

class PickUp : public Entity
{};

class GameType
{};

namespace levelNS
{
	const int NUM_PROJECTILES = 10;
	const int NUM_CHARACTERS = 1;
	const int NUM_SPAWNS = 10;
	const int NUM_TERRAIN = 100;
	const int NUM_PICKUP = 10;
}

class LMap
{
public:
	~LMap();
	int minX, maxX, minY, maxY;
	int numTerrain, numCharacters, numSpawns, numMags, totalSpawns;//totalSpawns is the number of active spawn points
	int numTargets, totalTargets;//num is the available ones total is the ones created
	int totalCharacters;//characters added in
	int addedElements;
	Magazine** mags;
	Character** characters;
	//MapElement* items[levelNS::NUM_ITEMS];//things like spawn points, no collision
	TerrainElement** terrain;
	PickUp* dropped[levelNS::NUM_PICKUP];//if they are touching it and choose to pick it up pick it up
	TerrainElement** spawnPoints;
	TerrainElement** targets;
	int player;
	//has a pointer to input so that it can easily run all the updating and what not
	Input* input;
	Graphics* graphics;
	Camera* camera;
	bool collidesWithMoving(D3DXVECTOR2* movingPos, D3DXVECTOR2* movingVelocity, TerrainElement* object, float &angle, float &frameTime);
	bool collidesWithMovingRay(D3DXVECTOR2 movingPos, D3DXVECTOR2 movingVelocity, float slope, float b, D3DXVECTOR2 corner1, D3DXVECTOR2 corner2, float &frameTime);
	bool collidesWithCharacter(Character* c, TerrainElement* t, float& fT);
	//	bool checkCornerCollision(float& fT, TerrainElement* t, Character* c);
	static float getXIntercept(float m1, float b1, float m2, float b2);
	void collide(Character* ent, TerrainElement* t, int side);
	LMap(Input* i, Graphics* g, int numT = 1000, int numM = 1000, int numC = 1, int numS = 5, int numTarget = 10, bool edit = false);
	void update(float frameTime);
	void draw();
	bool addTerrain(TerrainElement* t);
	bool addSpawnPoint(TerrainElement* pt);
	bool addTarget(TerrainElement* target);
	bool addCharacter(Character* c);
	//void buildFromFile(std::string fileName);
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, TextureManager *targetTM);
	void createFileFromLevel(int terrain, int spawn, float zoom);
	void collision();
	bool editor;
	//used for opening and saving levels to and from files
	string levelFileName;
	//used for bullet collisions
	bool projectileCollide(Projectile &proj, TerrainElement &terra, float &frameTime);
	void chooseSpawnPoint(Character* c);
	bool levelDone;
	int activeTargets;
};

#endif