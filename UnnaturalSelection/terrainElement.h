#ifndef _TERRAINELEMENT_H
#define _TERRAINELEMENT_H

#include "entity.h"
#include "line.h"

namespace terrainNS
{
	const int WIDTH = 100;            
    const int HEIGHT = 31;           
    const int X = GAME_WIDTH/4;   
    const int Y = GAME_HEIGHT/4;
    const float SPEED = 0;    
    const float MASS = 300.0f;    
    const int   TEXTURE_COLS = 1;
}

class TerrainElement : public Entity
{
public:
	void generateSideEquations();
	float getXCorner(float m1, float b1, float m2, float b2);
	TerrainElement();
	TerrainElement(int height = terrainNS::HEIGHT, int width = terrainNS::WIDTH, VECTOR2 center = VECTOR2(terrainNS::X,terrainNS::Y));
	TerrainElement(int height, int width, VECTOR2 center, int a, int r, int g, int b);
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	bool initialize(Game*, TextureManager*, int nCol);
	//appropriately make the entity do what it has to do
	virtual void collide(Entity* ent);
	bool destructable;
	bool collidesWithRay(myLines::Ray* in, float& frameTime);
	myLines::Ray sides[4];
	VECTOR2 corners[4];
	int getCollisionSide(D3DXVECTOR2 &collisionVector);
	char type;
};
//
//class StraightPath : public TerrainElement
//{
//public:
//	StraightPath(int height = terrainNS::HEIGHT, int width = terrainNS::WIDTH, VECTOR2 center = VECTOR2(terrainNS::X,terrainNS::Y));
//	void collide(Entity* ent);
//};
//
//class SlantedPath : public TerrainElement
//{
//public:
//	SlantedPath(int height = terrainNS::HEIGHT, int width = terrainNS::WIDTH, VECTOR2 center = VECTOR2(terrainNS::X,terrainNS::Y));
//	void collide(Entity* ent);
//};
//
//class Wall : public TerrainElement
//{
//public:
//	Wall(int height = terrainNS::HEIGHT, int width = terrainNS::WIDTH, VECTOR2 center = VECTOR2(terrainNS::X,terrainNS::Y));
//	void collide(Entity* ent);
//};

#endif