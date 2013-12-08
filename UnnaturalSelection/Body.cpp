#include "Body.h"

Body::Body(Game* game, Graphics* graphics) : game(game), graphics(graphics) {
//Set default actions
	crouch = false;
	faceDir = bodyNS::FACE_DIRECTION;
	falling = false;
	jumping = false;
	running = false;
	walking = false;

//Set basic config
	animationDelay = bodyNS::ANIMATION_DELAY;
	cols = bodyNS::COLS;
	crouchHeight = bodyNS::CROUCH_HEIGHT;
	graphic = const_cast<char*>(bodyNS::GRAPHIC);
	height = bodyNS::HEIGHT;
	heightBC = height;
	startFrame = bodyNS::START_FRAME;
	stopFrame = bodyNS::STOP_FRAME;
	width = bodyNS::WIDTH;

//Set crouch config
	crouchLeftStart = bodyNS::CROUCH_LEFT_START;
	crouchLeftStop = bodyNS::CROUCH_LEFT_STOP;
	crouchRightStart = bodyNS::CROUCH_RIGHT_START;
	crouchRightStop = bodyNS::CROUCH_LEFT_STOP;
		
//Set fall config
	fallLeftStart = bodyNS::FALL_LEFT_START;
	fallLeftStop = bodyNS::FALL_LEFT_STOP;
	fallRightStart = bodyNS::FALL_RIGHT_START;
	fallRightStop = bodyNS::FALL_LEFT_STOP;

//Set jump config
	jumpLeftStart = bodyNS::JUMP_LEFT_START;
	jumpLeftStop = bodyNS::JUMP_LEFT_STOP;
	jumpRightStart = bodyNS::JUMP_RIGHT_START;
	jumpRightStop = bodyNS::JUMP_LEFT_STOP;

//Set idle config
	lookLeftStart = bodyNS::LOOK_LEFT_START;
	lookLeftStop = bodyNS::LOOK_LEFT_STOP;
	lookRightStart = bodyNS::LOOK_RIGHT_START;
	lookRightStop = bodyNS::LOOK_LEFT_STOP;

//Set run config
	runLeftStart = bodyNS::RUN_LEFT_START;
	runLeftStop = bodyNS::RUN_LEFT_STOP;
	runRightStart = bodyNS::RUN_RIGHT_START;
	runRightStop = bodyNS::RUN_LEFT_STOP;

//Set walk config
	walkLeftStart = bodyNS::WALK_LEFT_START;
	walkLeftStop = bodyNS::WALK_LEFT_STOP;
	walkRightStart = bodyNS::WALK_RIGHT_START;
	walkRightStop = bodyNS::WALK_RIGHT_STOP;

//Final settings
	collisionType = entityNS::BOX;
	spriteData.scale = 1.0f;
	
	evalSize();
}

Body::~Body() {
//	SAFE_DELETE(game);
//	SAFE_DELETE(graphic);
//	SAFE_DELETE(graphics);
}

void Body::evalSize() {
	spriteData.rect.bottom = height / 2;
	spriteData.rect.left = -(width - 20) / 2;
	spriteData.rect.right = (width - 20) / 2;
	spriteData.rect.top = -height / 2;

	edge.bottom = height / 2;
	edge.left = -24;
	edge.right = 24;
	edge.top = -height / 2;
}

void Body::initialize() {
//Initialize the body texture
	if (!tm.initialize(graphics, graphic))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the player's body texture... and floating heads are awkward"));

//Initialize this Body object
	Entity::initialize(game, 
		width, height, 
		cols, &tm);

//Initialize the animation
	setFrames(startFrame, stopFrame);
	setCurrentFrame(startFrame);
	setFrameDelay(animationDelay);
}

void Body::update(float frametime) {
	Entity::update(frametime);
	height = heightBC;
	
//React to character actions
	if (crouch) {
		height = crouchHeight;

		if (faceDir < 0) {
			setCurrentFrame(crouchRightStart);
		} else {
			setCurrentFrame(crouchLeftStart);
		}
	} else if (falling) {
		if (faceDir < 0) {
			setFrames(fallRightStart, fallRightStop);
		} else {
			setFrames(fallLeftStart, fallLeftStop);
		}
	} else if (jumping) {
		if (faceDir < 0) {
			setFrames(jumpRightStart, jumpRightStop);
		} else {
			setFrames(jumpLeftStart, jumpLeftStop);
		}
	} else if (running) {
		if (faceDir < 0) {
			setCurrentFrame(runRightStart);
		} else {
			setCurrentFrame(runLeftStart);
		}
	} else if (walking) {
		if (faceDir < 0) {
			setFrames(walkRightStart, walkRightStop);
		} else {
			setFrames(walkLeftStart, walkLeftStop);
		}
	} else {
		if (faceDir < 0) {
			setCurrentFrame(lookRightStart);
		} else {
			setCurrentFrame(lookLeftStart);
		}
	}
	
	spriteData.height = height;
	spriteData.x += velocity.x * frametime;
	spriteData.y += velocity.y * frametime;
}