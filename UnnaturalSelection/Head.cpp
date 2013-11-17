#include "Head.h"

Head::Head(Game* game, Graphics* graphics) : game(game), graphics(graphics) {
//Set default actions
	crouch = false;
	faceDir = headNS::FACE_DIRECTION;
	falling = false;
	jumping = false;
	running = false;
	walking = false;

//Set basic config
	animationDelay = headNS::ANIMATION_DELAY;
	cols = headNS::COLS;
	crouchHeight = headNS::CROUCH_HEIGHT;
	graphic = const_cast<char*>(headNS::GRAPHIC);
	height = headNS::HEIGHT;
	heightBC = height;
	startFrame = headNS::START_FRAME;
	stopFrame = headNS::STOP_FRAME;
	width = headNS::WIDTH;

//Set crouch config
	crouchLeftStart = headNS::CROUCH_LEFT_START;
	crouchLeftStop = headNS::CROUCH_LEFT_STOP;
	crouchRightStart = headNS::CROUCH_RIGHT_START;
	crouchRightStop = headNS::CROUCH_LEFT_STOP;
		
//Set fall config
	fallLeftStart = headNS::FALL_LEFT_START;
	fallLeftStop = headNS::FALL_LEFT_STOP;
	fallRightStart = headNS::FALL_RIGHT_START;
	fallRightStop = headNS::FALL_LEFT_STOP;

//Set jump config
	jumpLeftStart = headNS::JUMP_LEFT_START;
	jumpLeftStop = headNS::JUMP_LEFT_STOP;
	jumpRightStart = headNS::JUMP_RIGHT_START;
	jumpRightStop = headNS::JUMP_LEFT_STOP;

//Set idle config
	lookLeftStart = headNS::LOOK_LEFT_START;
	lookLeftStop = headNS::LOOK_LEFT_STOP;
	lookRightStart = headNS::LOOK_RIGHT_START;
	lookRightStop = headNS::LOOK_LEFT_STOP;

//Set run config
	runLeftStart = headNS::RUN_LEFT_START;
	runLeftStop = headNS::RUN_LEFT_STOP;
	runRightStart = headNS::RUN_RIGHT_START;
	runRightStop = headNS::RUN_LEFT_STOP;

//Set walk config
	walkLeftStart = headNS::WALK_LEFT_START;
	walkLeftStop = headNS::WALK_LEFT_STOP;
	walkRightStart = headNS::WALK_RIGHT_START;
	walkRightStop = headNS::WALK_LEFT_STOP;

//Final settings
	collisionType = entityNS::BOX;
	spriteData.scale = 1.0f;
	
	evalSize();
}

Head::~Head() {
	//SAFE_DELETE(game);
	//SAFE_DELETE(graphic);
	//SAFE_DELETE(graphics);
}

void Head::evalSize() {
	spriteData.rect.bottom = height / 2;
	spriteData.rect.left = -height / 2;
	spriteData.rect.right = height / 2;
	spriteData.rect.top = -height / 2;
}

void Head::initialize() {
//Initialize the head texture
	if (!tm.initialize(graphics, graphic))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the player's head texture... and we don't want headless people"));

//Initialize this Head object
	Entity::initialize(game, 
		width, height, 
		cols, &tm);

//Initialize the animation
	setFrames(startFrame, stopFrame);
	setCurrentFrame(startFrame);
	setFrameDelay(animationDelay);
}

void Head::update(float frametime) {
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
			setCurrentFrame(fallRightStart);
		} else {
			setCurrentFrame(fallLeftStart);
		}
	} else if (jumping) {
		if (faceDir < 0) {
			setCurrentFrame(jumpRightStart);
		} else {
			setCurrentFrame(jumpLeftStart);
		}
	} else if (running) {
		if (faceDir < 0) {
			setCurrentFrame(runRightStart);
		} else {
			setCurrentFrame(runLeftStart);
		}
	} else if (walking) {
		if (faceDir < 0) {
			setCurrentFrame(walkRightStart);
		} else {
			setCurrentFrame(walkLeftStart);
		}
	} else {
		if (faceDir < 0) {
			setCurrentFrame(lookRightStart);
		} else {
			setCurrentFrame(lookLeftStart);
		}
	}
	
	spriteData.x += velocity.x * frametime;
	spriteData.y += velocity.y * frametime;
}