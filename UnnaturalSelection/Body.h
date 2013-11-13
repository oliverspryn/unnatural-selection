#ifndef BODY_H
#define BODY_H

#include "entity.h"
#include "game.h"
#include "gameError.h"
#include "graphics.h"
#include "textureManager.h"

namespace bodyNS {
	const float ANIMATION_DELAY    = 0.2f;
	const int   COLS               = 4;
	const int   CROUCH_HEIGHT      = 16;
	const int   CROUCH_LEFT_START  = 0;
	const int   CROUCH_LEFT_STOP   = 3;
	const int   CROUCH_RIGHT_START = 4;
	const int   CROUCH_RIGHT_STOP  = 7;
	const char  GRAPHIC[]          = "pictures\\body.jpg";
	const int   HEIGHT             = 66;
	const int   LOOK_LEFT_START    = 0;
	const int   LOOK_LEFT_STOP     = 3;
	const int   LOOK_RIGHT_START   = 4;
	const int   LOOK_RIGHT_STOP    = 7;
	const int   START_FRAME        = 0;
	const int   STOP_FRAME         = 3;
	const int   WIDTH              = 34;
}

class Body : public Entity {
private : 
	Game*          game;
	Graphics*      graphics;
	TextureManager tm;

public : 
	Body(Graphics* graphics, Game* game);
	~Body();

	//virtual void crouchLeft();
	virtual void initialize();
	virtual void update(float frametime);
};

#endif