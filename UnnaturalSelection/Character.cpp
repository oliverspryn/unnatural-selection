#include "Character.h"

Character::Character(Game* game, Graphics* graphics) : game(game), graphics(graphics){
	aimAngle = 0.0f;
	damageBodyConst = characterNS::DAMAGE_BODY_CONST;
	damageHeadConst = characterNS::DAMAGE_HEAD_CONST;
	energy = characterNS::ENERGY;
	energyRegenRate = characterNS::ENERGY_REGEN_RATE;
	faceDir = 0;
	gravity = new D3DXVECTOR2(characterNS::GRAVITY_X, characterNS::GRAVITY_Y);
	healthPoints = characterNS::HEALTH_POINTS;
	healthRegenRate = characterNS::HEALTH_REGEN_RATE;
	initialSpeed = characterNS::INITIAL_SPEED;
	input = game->getInput();
	jumpTime = characterNS::JUMP_TIME;
	runAcceleration = characterNS::RUN_ACCELERATION;
	runSpeed = characterNS::RUN_SPEED;
	standingOn = 0;
	stopSpeed = characterNS::STOP_SPEED;
	walkAcceleration = characterNS::WALK_ACCELERATION;
	walkSpeed = characterNS::WALK_SPEED;
	charFrameTime = -1;
}

Character::~Character() {
	SAFE_DELETE(body);
	SAFE_DELETE(cursor);
	SAFE_DELETE(gravity);
	SAFE_DELETE(head);
	SAFE_DELETE(standingOn);
}

bool Character::collidesWith(Entity &ent, VECTOR2 &collisionVector) {
	return body->collidesWith(ent, collisionVector) | head->collidesWith(ent, collisionVector);
}

void Character::draw() {
	//body->draw();
	//head->draw();
	//cursor->draw();

	#ifdef SHOW_ANGLE
	aimText.setFontColor(graphicsNS::BLACK);
    aimText.print(sin.str(),20,20);
	#endif
}

#pragma region
int Character::getCenterX() {
	return body->getWidth() / 2;
}

int Character::getCenterY() {
	int total = body->getHeight() + head->getHeight();

	return total / 2;
}

int Character::getHeight() {
	return body->getHeight() + head->getHeight();
}

D3DXVECTOR2 Character::getVelocity() {
	return body->getVelocity();
}

float Character::getVelocityX() {
	return body->getVelocity().x;
}

float Character::getVelocityY() {
	return body->getVelocity().y;
}

float Character::getVelMagnitude() {
	return sqrt(pow(body->getVelocity().x, 2) + pow(body->getVelocity().y, 2));
}

int Character::getWidth() {
	return body->getWidth();
}

float Character::getX() {
	return corners[0].x;
}

float Character::getY() {
	return corners[0].y;
}
#pragma endregion

void Character::initialize() {
	body = new Body(game, graphics);
	cursor = new Cursor(game, graphics);
	head = new Head(game, graphics);

	body->initialize();
	cursor->initialize();
	head->initialize();

//Generate the aim angle text
	#ifdef SHOW_ANGLE
	if(aimText.initialize(graphics, 15, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
	#endif

//Generate the corners of the sprite
	updateCorners();

//Properly position the Head object with respect to the Body object
	setXY(0.0f, 0.0f);
}

void Character::jump() {
	D3DXVECTOR2 v;
	standingOn = 0;
	
	v.x = body->getVelocity().x;	
	v.y = body->getVelocity().y - characterNS::GRAVITY_Y * characterNS::JUMP_TIME;

	setVelocity(v);
}

#pragma region
void Character::setVelocity(D3DXVECTOR2 v) {
	body->setVelocity(v);
	head->setVelocity(v);
}

void Character::setVelocityX(float x) {
	D3DXVECTOR2 v;
	v.x = x;
	v.y = body->getVelocity().y;

	body->setVelocity(v);
	head->setVelocity(v);
}

void Character::setVelocityY(float y) {
	D3DXVECTOR2 v;
	v.x = body->getVelocity().x;
	v.y = y;

	body->setVelocity(v);
	head->setVelocity(v);
}

void Character::setX(float x) {
	body->setX(x);
	head->setX(x + body->getWidth() / 2 - head->getWidth() / 2);
}

void Character::setXC(float x) {
	body->setX(x - body->getWidth() / 2);
	head->setX(x - body->getWidth() / 2 - head->getWidth() / 2);
}

void Character::setXY(float x, float y) {
	body->setX(x);
	head->setX(x + body->getWidth() / 2 - head->getWidth() / 2);

	body->setY(y + head->getHeight());
	head->setY(y);
}

void Character::setXYC(float x, float y) {
	body->setX(x - body->getWidth() / 2);
	head->setX(x - body->getWidth() / 2 - head->getWidth() / 2);

	int total = body->getHeight() + head->getHeight();

	body->setY(y - total / 2 + head->getHeight());
	head->setY(y - total / 2);
}

void Character::setY(float y) {
	body->setY(y + head->getHeight());
	head->setY(y);
}

void Character::setYC(float y) {
	int total = body->getHeight() + head->getHeight();

	body->setY(y - total / 2 + head->getHeight());
	head->setY(y - total / 2);
}
#pragma endregion

int Character::sign(float x) {
	return (x < 0) ? -1 : (x > 0);
}

void Character::update(float frameTime) {
	updateCorners();

//Show the Character angle
	#ifdef SHOW_ANGLE
	sin.str("");
    sin << aimAngle;
	#endif

//Movement based on collision detection
	if (standingOn == 0) {
		D3DXVECTOR2 v (
			body->getVelocity().x, 
			body->getVelocity().y + frameTime * characterNS::GRAVITY_Y
		);

		setVelocity(v);
	} else {
		int xpos = body->getX();

		if (body->getX() + body->getWidth() < standingOn->corners[0].x || body->getX() > standingOn->corners[3].x) {
			standingOn = 0;
		}
	}

//Move left or right
	if (input->isKeyDown(characterNS::WALK_LEFT) ^ input->isKeyDown(characterNS::WALK_RIGHT)) {
		faceDir = input->isKeyDown(characterNS::WALK_RIGHT) ? 1 : -1;
	} else {
		faceDir = 0;
	}

//Crouch, disabled, sad face :(
	//body->crouch = input->isKeyDown(characterNS::CROUCH);
	//head->crouch = input->isKeyDown(characterNS::CROUCH);

	if (standingOn != 0) {
		walk(frameTime);

		if (input->isKeyDown(characterNS::JUMP)) {
			jump();
		}
	} else {
		walk(frameTime/3);
	}

//Ready? Aim... <insert "fire" statement here, when ready>
	//aimAngle = atan2(
	//	body->getY() - static_cast<float>(input->getMouseY()),
	//	body->getX() - static_cast<float>(input->getMouseX())
	//);

//Determine orientation of the player, based on the mouse direction
	if (aimAngle > PI2) { // Quadrant 1
		faceDir = -1;
	}

	if (aimAngle < PI2 && aimAngle > 0.0) { // Quadrant 2
		faceDir = 1;
	}

	if (aimAngle > -PI2 && aimAngle <= 0.0) { // Quadrant 3
		faceDir = 1;
	}

	if (aimAngle < -PI2 && aimAngle <= 0.0) { // Quadrant 4
		faceDir = -1;
	}

//Set the direction of the player
	body->faceDir = faceDir;
	head->faceDir = faceDir;

	body->update(frameTime);
	//cursor->update(frameTime);
	head->update(frameTime);
}

void Character::updateCorners() {
	corners[0].x = body->getX();
	corners[0].y = head->getY();
	corners[1].x = body->getX();
	corners[1].y = body->getY() + body->getHeight();
	corners[2].x = body->getX() + body->getWidth();
	corners[2].y = body->getY() + body->getHeight();
	corners[3].x = body->getX() + body->getWidth();
	corners[3].y = head->getY();
}

int Character::velSign() {
	return sign(body->getVelocity().x);
}

void Character::walk(float frametime) {
	D3DXVECTOR2 v(body->getVelocity());
	int currentDir = velSign();

//No walking
	if (currentDir == 0) {
		if (faceDir == 0) {
			v.x = 0.0f;
		} else {
			v.x = characterNS::INITIAL_SPEED * faceDir;
		}
//Walking
	} else {
		if (faceDir == 0) {
			v.x -= currentDir * min(fabs(body->getVelocity().x), characterNS::STOP_SPEED * frametime);
			if(abs(v.x) < characterNS::END_SPEED)
			{
				v.x = 0;
			}
		} else if (faceDir == currentDir) {
			v.x += faceDir * sign(characterNS::WALK_SPEED - fabs(v.x)) * frametime * characterNS::WALK_ACCELERATION;
		} else {
			v.x -= currentDir * (2*characterNS::WALK_ACCELERATION + characterNS::STOP_SPEED) * frametime;
		}
	}

	setVelocity(v);
}