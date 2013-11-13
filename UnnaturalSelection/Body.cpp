#include "Body.h"

Body::Body(Graphics* graphics, Game* game) : 
	game(game), graphics(graphics) {
		collisionType = entityNS::BOX;
		spriteData.scale = 1.0f;
		spriteData.rect.bottom = bodyNS::HEIGHT / 2;
		spriteData.rect.left = -bodyNS::WIDTH / 2;
		spriteData.rect.right = bodyNS::WIDTH / 2;
		spriteData.rect.top = -bodyNS::HEIGHT / 2;
}

Body::~Body() {
	SAFE_DELETE(game);
	SAFE_DELETE(graphics);
}

void Body::initialize() {
//Initialize the head texture
	if (!tm.initialize(graphics, bodyNS::GRAPHIC))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the player's body texture... and floating heads are weird"));

//Initialize this Head object
	Entity::initialize(game, 
		bodyNS::WIDTH, bodyNS::HEIGHT, 
		bodyNS::COLS, &tm);

//Initialize the animation
	setFrames(bodyNS::START_FRAME, bodyNS::STOP_FRAME);
	setCurrentFrame(bodyNS::START_FRAME);
	setFrameDelay(bodyNS::ANIMATION_DELAY);
}

void Body::update(float frametime) {
	Entity::update(frametime);

	spriteData.x += velocity.x;
	spriteData.y += velocity.y;
}