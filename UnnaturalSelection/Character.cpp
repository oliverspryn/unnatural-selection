#include "Character.h"

Character::Character(Graphics* graphics, Game* game) :
	aimAngle(characterNS::AIM_ANGLE),
	aimSpeed(characterNS::AIM_SPEED),
	crouch(false),
	damageBodyConst(characterNS::DAMAGE_BODY_CONST),
	damageHeadConst(characterNS::DAMAGE_HEAD_CONST),
	energy(characterNS::ENERGY),
	energyRegenRate(characterNS::ENERGY_REGEN_RATE),
	game(game),
	graphics(graphics),
	gravity(new D3DXVECTOR2(characterNS::GRAVITY_X, characterNS::GRAVITY_Y)),
	healthPoints(characterNS::HEALTH_POINTS),
	healthRegenRate(characterNS::HEALTH_REGEN_RATE),
	initialSpeed(characterNS::INITIAL_SPEED),
	input(game->getInput()),
	jumpTime(characterNS::JUMP_TIME),
	motion(new D3DXVECTOR2(0.0f, 0.0f)),
	runAcceleration(characterNS::RUN_ACCELERATION),
	runSpeed(characterNS::RUN_SPEED),
	stopSpeed(characterNS::STOP_SPEED),
	walkAcceleration(characterNS::WALK_ACCELERATION),
	walkSpeed(characterNS::WALK_SPEED) { }

Character::~Character() {
	SAFE_DELETE(body);
	SAFE_DELETE(head);
}

void Character::initialize() {
	body = new Body(graphics, game);
	head = new Head(graphics, game);
	text = new TextDX();

	body->initialize();
	head->initialize();

	if (text->initialize(graphics, 15, true, false, "Arial") == false) {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
	}

//Properly position the Head object with respect to the Body object
	setXY(0.0f, 0.0f);
}

void Character::draw() {
	body->draw();
	head->draw();
	text->setFontColor(graphicsNS::WHITE);
    text->print(sin.str(),20,20);
}

void Character::update(float frameTime) {
	body->update(frameTime);
	head->update(frameTime);
}

void Character::act() {
//Move left
	if (input->isKeyDown(characterNS::WALK_LEFT)) {
		walkLeft();
//Move right
	} else if (input->isKeyDown(characterNS::WALK_RIGHT)) {
		walkRight();
//Crouch
	} else if (input->isKeyDown(characterNS::CROUCH)) {
		//doCrouch();
//Jump
	} else if (input->isKeyDown(characterNS::JUMP)) {
		jump();
//No buttons pressed? Don't move
	} else {
		D3DXVECTOR2 v(0.0f, 0.0f);
		body->setVelocity(v);
		head->setVelocity(v);
	}

//Ready? Aim... <insert "fire" statement here, when ready>
	aimAngle = atan2(
		body->getY() - static_cast<float>(input->getMouseY()),
		body->getX() - static_cast<float>(input->getMouseX())
	);
	aimAngle *= 180 / 3.1415926f;
	sin.str("");
	sin << aimAngle;
}

bool Character::collidesWith(Entity &ent, VECTOR2 &collisionVector) {
	return body->collidesWith(ent, collisionVector) | head->collidesWith(ent, collisionVector);
}

void Character::walkLeft() {
	D3DXVECTOR2 v;
	oldVel = body->getVelocity();

//Start the character's movement
	if (body->getVelocity().x == 0) {
		v.x = -characterNS::INITIAL_SPEED;
		v.y = 0;
	} else {
	//Ramp up speed...
		if (oldVel.x > -characterNS::WALK_SPEED) {
			v.x = oldVel.x - characterNS::WALK_ACCELERATION;
			v.y = 0;
	//...nuff speed
		} else {
			v.x = -characterNS::WALK_SPEED;
			v.y = 0;
		}
	}

	body->setVelocity(v);
	head->setVelocity(v);
}

void Character::walkRight() {
	D3DXVECTOR2 v;
	oldVel = body->getVelocity();

//Start the character's movement
	if (oldVel.x == 0) {
		v.x = characterNS::INITIAL_SPEED;
		v.y = oldVel.y;
	} else {
	//Ramp up speed...
		if (oldVel.x < characterNS::WALK_SPEED) {
			v.x = oldVel.x + characterNS::WALK_ACCELERATION;
			v.y = oldVel.y;
	//...nuff speed
		} else {
			v.x = characterNS::WALK_SPEED;
			v.y = oldVel.y;
		}
	}

	body->setVelocity(v);
	head->setVelocity(v);
}

void Character::jump() {
	D3DXVECTOR2 v;
	oldVel = body->getVelocity();
	v.x = oldVel.x;	
	v.y = oldVel.y - characterNS::GRAVITY_Y * characterNS::JUMP_TIME;

	body->setVelocity(v);
	head->setVelocity(v);
}

void Character::setX(float x) {
	body->setX(x);
	head->setX(x + body->getWidth() / 2 - head->getWidth() / 2);
}

void Character::setY(float y) {
	body->setY(y + head->getHeight());
	head->setY(y);
}

void Character::setXY(float x, float y) {
	body->setX(x);
	head->setX(x + body->getWidth() / 2 - head->getWidth() / 2);

	body->setY(y + head->getHeight());
	head->setY(y);
}