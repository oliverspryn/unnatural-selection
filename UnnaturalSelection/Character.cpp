#include "Character.h"

Character::Character(Game* game, Graphics* graphics) : game(game), graphics(graphics){
	head = 0;
	body = 0;
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
	currentWeapon = 0;
	currentMag = 0;
	weaponPos = D3DXVECTOR2(20, 0);
	reloadTimer = 0;
	reloadStep = 0;
}

Character::~Character() {
	SAFE_DELETE(body);
	delete cursor;
	SAFE_DELETE(gravity);
	SAFE_DELETE(head);
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
float Character::getCenterX() {
	return corners[0].x + body->getWidth() / 2.0f;
}

float Character::getCenterY() {
	int total = body->getHeight() + head->getHeight();

	return corners[0].y + total / 2.0f;
}

D3DXVECTOR2 Character::getCenter() {

	return D3DXVECTOR2(getCenterX(), getCenterY());
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

//Show the Character angle
	#ifdef SHOW_ANGLE
	sin.str("");
    sin << aimAngle;
	#endif

//Movement based on collision detection
	if (standingOn == 0 || !standingOn->getActive()) {
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

		body->walking = true;
	} else {
		faceDir = 0;
		body->walking = false;
	}

//Crouch, disabled, sad face :(
	//body->crouch = input->isKeyDown(characterNS::CROUCH);
	//head->crouch = input->isKeyDown(characterNS::CROUCH);

	if (standingOn != 0) {
		walk(frameTime);

		if (input->isKeyDown(characterNS::JUMP)) {
			jump();
			body->jumping = true;
		} else {
			body->jumping = false;
		}
	} else {
		walk(frameTime/3);
		body->jumping = true;
	}

//Ready? Aim... <insert "fire" statement here, when ready>
	
	//aimAngle = atan2(
	//	body->getY() - static_cast<float>(input->getMouseY()),
	//	body->getX() - static_cast<float>(input->getMouseX())
	//);

//Determine orientation of the player, based on the mouse direction
	if (aimAngle > PI2) { // Quadrant 1
		faceDir = 1;
	}

	if (aimAngle < PI2 && aimAngle > 0.0) { // Quadrant 2
		faceDir = -1;
	}

	if (aimAngle > -PI2 && aimAngle <= 0.0) { // Quadrant 3
		faceDir = -1;
	}

	if (aimAngle < -PI2 && aimAngle <= 0.0) { // Quadrant 4
		faceDir = 1;
	}

//Set the direction of the player
	body->faceDir = faceDir;
	head->faceDir = faceDir;

	body->update(frameTime);
	//cursor->update(frameTime);
	head->update(frameTime);

	updateCorners();

	if(currentWeapon != 0)
	{
		currentWeapon->setAngle(aimAngle);
		currentWeapon->setX(getCenterX() + weaponPos.x * std::cos(aimAngle) + weaponPos.y * std::sin(aimAngle) - currentWeapon->getWidth()/2);
		currentWeapon->setY(getCenterY() + weaponPos.y * std::cos(aimAngle) + weaponPos.x * std::sin(aimAngle) -currentWeapon->getHeight()/2);
		currentWeapon->update(frameTime);
		if(input->isKeyDown('R') && reloadStep == 0)
		{
			reloadStep = 1;
			reloadTimer = frameTime;
		}
		if(reloadStep != 0)
		{
			reloadTimer += frameTime;
			if(reloadTimer > static_cast<Gun*>(currentWeapon)->reloadTime)
			{
				static_cast<Gun*>(currentWeapon)->loadMag();
				reloadStep = 0;
			}
			else if(reloadTimer > static_cast<Gun*>(currentWeapon)->reloadTime/3)
			{
				static_cast<Gun*>(currentWeapon)->removeMag();
				currentMag->loadAmmo();
			}
		}
		currentWeapon->act(frameTime, input->getMouseLButton(), false, false, false, false);
	}
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