#ifndef AI_H
#define AI_H

#include "Character.h"
#include "game.h"
#include "graphics.h"

class AI : public Character {
public : 
	AI(Game* game, Graphics* graphics);
	virtual void update(float frameTime)
	{
		//throw "ertyui";
		frameTime++;
	}

};

#endif