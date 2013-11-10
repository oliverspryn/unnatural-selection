#ifndef _TERRAINELEMENT_H
#define _TERRAINELEMENT_H

#include "entity.h"

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
	TerrainElement();
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	bool initialize(Game*, TextureManager*, int nCol);
};

class StraightPath : public TerrainElement
{
public:
	StraightPath(int height = terrainNS::HEIGHT, int width = terrainNS::WIDTH, VECTOR2 center = VECTOR2(terrainNS::X,terrainNS::Y));
	
};

#endif