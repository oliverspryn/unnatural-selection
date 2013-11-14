#ifndef HEAD_H
#define HEAD_H

#include "entity.h"
#include "game.h"
#include "gameError.h"
#include "graphics.h"
#include "textureManager.h"

namespace headNS {
//Basic config
	const float ANIMATION_DELAY    = 0.2f;
	const int   COLS               = 4;
	const int   CROUCH_HEIGHT      = 18;
	const int   FACE_DIRECTION     = 1;  // 1 = right, 0 | -1 = left
	const char  GRAPHIC[]          = "pictures\\head.jpg";
	const int   HEIGHT             = 18; // Height + frame
	const int   START_FRAME        = 0;  // Must face in the the direction of FACE_DIRECTION
	const int   STOP_FRAME         = 3;
	const int   WIDTH              = 18; // Width + frame

//Crouch
	const int   CROUCH_LEFT_START  = 0;
	const int   CROUCH_LEFT_STOP   = 3;
	const int   CROUCH_RIGHT_START = 4;
	const int   CROUCH_RIGHT_STOP  = 7;

//Fall
	const int   FALL_LEFT_START    = 0;
	const int   FALL_LEFT_STOP     = 3;
	const int   FALL_RIGHT_START   = 4;
	const int   FALL_RIGHT_STOP    = 7;

//Jump
	const int   JUMP_LEFT_START    = 0;
	const int   JUMP_LEFT_STOP     = 3;
	const int   JUMP_RIGHT_START   = 4;
	const int   JUMP_RIGHT_STOP    = 7;

//Idle
	const int   LOOK_LEFT_START    = 0;
	const int   LOOK_LEFT_STOP     = 3;
	const int   LOOK_RIGHT_START   = 4;
	const int   LOOK_RIGHT_STOP    = 7;

//Run
	const int   RUN_LEFT_START     = 0;
	const int   RUN_LEFT_STOP      = 3;
	const int   RUN_RIGHT_START    = 4;
	const int   RUN_RIGHT_STOP     = 7;

//Walk
	const int   WALK_LEFT_START    = 0;
	const int   WALK_LEFT_STOP     = 3;
	const int   WALK_RIGHT_START   = 4;
	const int   WALK_RIGHT_STOP    = 7;
}

class Head : public Entity {
private : 
	Game*          game;
	Graphics*      graphics;
	TextureManager tm;

public : 
	Head(Game* game, Graphics* graphics);
	~Head();

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