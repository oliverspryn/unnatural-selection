#ifndef AI_H
#define AI_H

#include "Character.h"
#include "game.h"
#include "graphics.h"


class AI : public Character {
public : 
	AI(Game* game, Graphics* graphics, int charSize = 0, Character** chars = 0, int terrainSize = 0, TerrainElement** terrains = 0);
	virtual void update(float frameTime)
	{
		
	}
	


	//number of other characharers
	int characterSize;
	//The characters that exist
	Character** characters;
	//Number of terrain elements
	int terrainSize;
	//All terrain elements
	TerrainElement** terrain;

};

#endif