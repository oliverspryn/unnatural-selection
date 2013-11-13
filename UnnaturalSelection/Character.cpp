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
	walkDir(0),
	walkSpeed(characterNS::WALK_SPEED) {
		walkDir = 0;
		standingOn = 0;
}

Character::~Character() {
	SAFE_DELETE(body);
	SAFE_DELETE(head);
}

void Character::initialize() {
	body = new Body(graphics, game);
	head = new Head(graphics, game);
	text = new TextDX();

	D3DXVECTOR2 v(0.0f, 0.0f);

	body->setVelocity(v);
	head->setVelocity(v);

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
	oldVel = body->getVelocity();

	if (standingOn == 0) {
		body->setVelocity(D3DXVECTOR2(body->getVelocity().x, body->getVelocity().y + frameTime*characterNS::GRAVITY_Y));
		head->setVelocity(D3DXVECTOR2(head->getVelocity().x, head->getVelocity().y + frameTime*characterNS::GRAVITY_Y));
	} else {
		int xpos = body->getX();

		if (body->getX() + body->getWidth() < standingOn->corners[0].x || body->getX() > standingOn->corners[3].x) {
			standingOn = 0;
		}
	}

//Move left or right
	if (input->isKeyDown(characterNS::WALK_LEFT) ^ input->isKeyDown(characterNS::WALK_RIGHT)) {
		walkDir = input->isKeyDown(characterNS::WALK_RIGHT) ? 1 : -1;
	} else {
		walkDir = 0;
	}

	if (standingOn != 0) {
		walk(frameTime);
	}

	if (input->isKeyDown(characterNS::JUMP)) {
		jump();
	}

//Ready? Aim... <insert "fire" statement here, when ready>
	aimAngle = atan2(
		body->getY() - static_cast<float>(input->getMouseY()),
		body->getX() - static_cast<float>(input->getMouseX())
	);
	aimAngle *= 180 / 3.1415926f;
	sin.str("");
	sin << aimAngle;

	body->update(frameTime);
	head->update(frameTime);
}

void Character::act() {

}

void Character::walk(float frametime) {
	D3DXVECTOR2 v(body->getVelocity());
	int currentDir = velSign();
	//v.y = body->getVelocity().y;
	
	//v.y = oldVel.y;
	//v.x = oldVel.x;

	//setVelocity(v);
	//return;
//No walking
	if (currentDir == 0) {
		if (walkDir == 0) {
			v.x = 0.0f;
		} else {
			v.x = characterNS::INITIAL_SPEED * walkDir;
		}
//Walking
	} else {
		if (walkDir == 0) {
			v.x -= currentDir * min(fabs(oldVel.x), characterNS::STOP_SPEED * frametime);
		} else if (walkDir == currentDir) {
			v.x += walkDir * sign(characterNS::WALK_SPEED - fabs(v.x)) * frametime * characterNS::WALK_ACCELERATION;
		} else {
			v.x -= currentDir * (characterNS::WALK_ACCELERATION + characterNS::STOP_SPEED) * frametime;
		}
	}

	body->setVelocity(v);
	head->setVelocity(v);
}

bool Character::collidesWith(Entity &ent, VECTOR2 &collisionVector) {
	return body->collidesWith(ent, collisionVector) | head->collidesWith(ent, collisionVector);
}

int Character::sign(float x) {
	return (x < 0) ? -1 : (x > 0);
}

int Character::velSign() {
	return sign(body->getVelocity().x);
}

void Character::walkLeft() {
	if (standingOn != 0) {
		D3DXVECTOR2 v;
		oldVel = body->getVelocity();
		v.y = oldVel.y;

	//Start the character's movement
		if (oldVel.x == 0) {
			v.x = -characterNS::INITIAL_SPEED;
	//Stop going right
		} else if (oldVel.x > 0) {
			v.x = oldVel.x - characterNS::STOP_SPEED;
		} else {
		//Ramp up speed...
			if (oldVel.x > -characterNS::WALK_SPEED) {
				v.x = oldVel.x - characterNS::WALK_ACCELERATION;
		//...nuff speed
			} else {
				v.x = -characterNS::WALK_SPEED;
			}
		}

		body->setVelocity(v);
		head->setVelocity(v);
	}
}

void Character::walkRight() {
	if (standingOn != 0) {
		D3DXVECTOR2 v;
		oldVel = body->getVelocity();
		v.y = oldVel.y;

	//Start the character's movement
		if (oldVel.x == 0) {
			v.x = characterNS::INITIAL_SPEED;
	//Stop going right
		} else if (oldVel.x < 0) {
			v.x = oldVel.x + characterNS::STOP_SPEED;
		} else {
		//Ramp up speed...
			if (oldVel.x < characterNS::WALK_SPEED) {
				v.x = oldVel.x + characterNS::WALK_ACCELERATION;
		//...nuff speed
			} else {
				v.x = characterNS::WALK_SPEED;
			}
		}

		body->setVelocity(v);
		head->setVelocity(v);
	}
}

void Character::jump() {
	if (standingOn != 0) {
		D3DXVECTOR2 v;
		oldVel = body->getVelocity();
		standingOn = 0;
	
		v.x = oldVel.x;	
		v.y = oldVel.y - characterNS::GRAVITY_Y * characterNS::JUMP_TIME;

		body->setVelocity(v);
		head->setVelocity(v);
	}
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

void Character::setVelocity(D3DXVECTOR2 v) {
	body->setVelocity(v);
	head->setVelocity(v);
}