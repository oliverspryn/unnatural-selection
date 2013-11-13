#include "Head.h"

Head::Head(Graphics* graphics, Game* game) : 
	game(game), graphics(graphics) {
		collisionType = entityNS::BOX;
		spriteData.scale = 1.0f;
		spriteData.rect.bottom = headNS::HEIGHT / 2;
		spriteData.rect.left = -headNS::WIDTH / 2;
		spriteData.rect.right = headNS::WIDTH / 2;
		spriteData.rect.top = -headNS::HEIGHT / 2;
}

Head::~Head() {
	SAFE_DELETE(game);
	SAFE_DELETE(graphics);
}

void Head::initialize() {
//Initialize the head texture
	if (!tm.initialize(graphics, headNS::GRAPHIC))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the player's head texture... and we don't want headless people"));

//Initialize this Head object
	Entity::initialize(game, 
		headNS::WIDTH, headNS::HEIGHT, 
		headNS::COLS, &tm);

//Initialize the animation
	setFrames(headNS::START_FRAME, headNS::STOP_FRAME);
	setCurrentFrame(headNS::START_FRAME);
	setFrameDelay(headNS::ANIMATION_DELAY);
}

void Head::update(float frametime) {
	Entity::update(frametime);

	spriteData.x += velocity.x * frametime;
	spriteData.y += velocity.y * frametime;
}

void Head::crouchLeft() {
	setCurrentFrame(headNS::CROUCH_LEFT_START);
}