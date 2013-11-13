#ifndef HEAD_H
#define HEAD_H

#include "entity.h"
#include "game.h"
#include "gameError.h"
#include "graphics.h"
#include "textureManager.h"

namespace headNS {
	const float ANIMATION_DELAY    = 0.2f;
	const int   COLS               = 4;
	const int   CROUCH_HEIGHT      = 18;
	const int   CROUCH_LEFT_START  = 0;
	const int   CROUCH_LEFT_STOP   = 3;
	const int   CROUCH_RIGHT_START = 4;
	const int   CROUCH_RIGHT_STOP  = 7;
	const char  GRAPHIC[]          = "pictures\\head.jpg";
	const int   HEIGHT             = 18;
	const int   LOOK_LEFT_START    = 0;
	const int   LOOK_LEFT_STOP     = 3;
	const int   LOOK_RIGHT_START   = 4;
	const int   LOOK_RIGHT_STOP    = 7;
	const int   START_FRAME        = 0;
	const int   STOP_FRAME         = 3;
	const int   WIDTH              = 18;
}

class Head : public Entity {
private : 
	Game*          game;
	Graphics*      graphics;
	TextureManager tm;

public : 
	Head(Graphics* graphics, Game* game);
	~Head();

	virtual void crouchLeft();
	virtual void initialize();
	virtual void update(float frametime);
};

#endif