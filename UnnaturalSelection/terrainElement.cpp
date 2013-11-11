#include "terrainElement.h"

TerrainElement::TerrainElement()
{
	
}

bool TerrainElement::initialize(Game* gPtr, TextureManager* texture, int nCol)
{
	return Entity::initialize(gPtr,spriteData.width,spriteData.height,nCol,texture);
}

bool TerrainElement::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	return Entity::initialize(gamePtr,width,height,ncols,textureM);
}

StraightPath::StraightPath(int height, int width, VECTOR2 center)
{
	spriteData.height = height;
	spriteData.width = width;
	spriteData.x = center.x;
	spriteData.y = center.y;
	collisionType = entityNS::BOX;
	edge.left = (width/2)*-1;
	edge.right = width/2;
	edge.top = (height/2)*-1;
	edge.bottom = (height/2);
	mass = terrainNS::MASS;
}