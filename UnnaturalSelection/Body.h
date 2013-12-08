#ifndef BODY_H
#define BODY_H

#include "entity.h"
#include "game.h"
#include "gameError.h"
#include "graphics.h"
#include "textureManager.h"

namespace bodyNS {
//Basic config
	const float ANIMATION_DELAY    = 0.1f;
	const int   COLS               = 8;
	const int   CROUCH_HEIGHT      = 34;
	const int   FACE_DIRECTION     = 1;  // 1 = right, 0 | -1 = left
	const char  GRAPHIC[]          = "pictures\\SpriteSheet2.png";
	const int   HEIGHT             = 128; // Height + frame
	const int   START_FRAME        = 0;  // Must face in the the direction of FACE_DIRECTION
	const int   STOP_FRAME         = 3;
	const int   WIDTH              = 128; // Width + frame

//Crouch
	const int   CROUCH_LEFT_START  = 0;
	const int   CROUCH_LEFT_STOP   = 3;
	const int   CROUCH_RIGHT_START = 4;
	const int   CROUCH_RIGHT_STOP  = 7;

//Fall
	const int   FALL_LEFT_START    = 3;
	const int   FALL_LEFT_STOP     = 3;
	const int   FALL_RIGHT_START   = 11;
	const int   FALL_RIGHT_STOP    = 11;

//Jump
	const int   JUMP_LEFT_START    = 3;
	const int   JUMP_LEFT_STOP     = 3;
	const int   JUMP_RIGHT_START   = 11;
	const int   JUMP_RIGHT_STOP    = 11;

//Idle
	const int   LOOK_LEFT_START    = 24;
	const int   LOOK_LEFT_STOP     = 24;
	const int   LOOK_RIGHT_START   = 16;
	const int   LOOK_RIGHT_STOP    = 16;

//Run
	const int   RUN_LEFT_START     = 16;
	const int   RUN_LEFT_STOP      = 16;
	const int   RUN_RIGHT_START    = 16;
	const int   RUN_RIGHT_STOP     = 16;

//Walk
	const int   WALK_LEFT_START    = 8;
	const int   WALK_LEFT_STOP     = 13;
	const int   WALK_RIGHT_START   = 0;
	const int   WALK_RIGHT_STOP    = 5;
}

class Body : public Entity {
private : 
	Game*          game;
	Graphics*      graphics;
	TextureManager tm;

public : 
	Body(Game* game, Graphics* graphics);
	~Body();

//Set character actions
	bool crouch;
	int faceDir;
	bool falling;
	bool jumping;
	bool running;
	bool walking;

//Basic config
	float animationDelay;
	int cols;
	int crouchHeight;
	char* graphic;
	int height;
	int heightBC;
	int startFrame;
	int stopFrame;
	int width;

//Crouch config
	int crouchLeftStart;
	int crouchLeftStop;
	int crouchRightStart;
	int crouchRightStop;

//Fall config
	int fallLeftStart;
	int fallLeftStop;
	int fallRightStart;
	int fallRightStop;

//Jump config
	int jumpLeftStart;
	int jumpLeftStop;
	int jumpRightStart;
	int jumpRightStop;

//Idle config
	int lookLeftStart;
	int lookLeftStop;
	int lookRightStart;
	int lookRightStop;

//Run config
	int runLeftStart;
	int runLeftStop;
	int runRightStart;
	int runRightStop;

//Walk config
	int walkLeftStart;
	int walkLeftStop;
	int walkRightStart;
	int walkRightStop;

	virtual void evalSize();
	virtual void initialize();
	virtual void update(float frametime);
};

#endif