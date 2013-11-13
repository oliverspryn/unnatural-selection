#ifndef CHARACTER_H
#define CHARACTER_H

#include <cmath>
#include <sstream>

#include "Body.h"
#include "game.h"
#include "Head.h"
#include "LMap.h"
#include "textDX.h"
#include "terrainElement.h"

namespace characterNS {
//Character gameplay configuration
	const float AIM_ANGLE         = 90.0f;   // Initial angle, in degrees, which the Character is aiming a weapon
	const float AIM_SPEED         = 0.9f;    // The speed a which the Character can aim the weapon
	const float ENERGY            = 100.0f;  // Initial starting energy
	const int   DAMAGE_BODY_CONST = 5;       // A value decremeted from the Character who receives body damage
	const int   DAMAGE_HEAD_CONST = 10;      // A value decremeted from the Character who receives head damage
	const float ENERGY_REGEN_RATE = 1.002f;  // The rate, per frame, which the Character regerates energy
	const float HEALTH_POINTS     = 100.0f;  // Initial starting health
	const float HEALTH_REGEN_RATE = 1.0f;    // The rate, per frame, which the Character regerates health
	const float GRAVITY_X         = 1.0f;    // Direction and speed of gravity, in the X direction
	const float GRAVITY_Y         = 98.0f;   // Direction and speed of gravity, in the Y direction
	const float INITIAL_SPEED     = 10.0f;   // The speed at which the Character starting moving
	const float JUMP_TIME         = 0.5f;    // Amount of time for the jump to reach max height
	const float MASS              = 1.0f;    // The mass of the Character
	const float RUN_ACCELERATION  = 2.0f;    // The rate, per frame, which the speed will increase to running
	const float RUN_SPEED         = 30.0f;   // The maximum running speed
	const float STOP_SPEED        = 400.0f;  // The rate, per frame, which the speed will decrease to 0
	const float WALK_ACCELERATION = 200.0f;  // The rate, per frame, which the speed will increase to walking
	const float WALK_SPEED        = 300.0f;  // The maximum walking speed

//Input keys
	const UCHAR CROUCH            = VK_DOWN;
	const UCHAR JUMP              = VK_SPACE;
	const UCHAR WALK_LEFT         = VK_LEFT;
	const UCHAR WALK_RIGHT        = VK_RIGHT;
}

class Character {
protected : 
	int sign(float x);
	int velSign();

	//void doCrouch();
	virtual void jump();
	virtual void walk(float frametime);

	D3DXVECTOR2     oldVel;

	Game*           game;
	Graphics*       graphics;
	Input*          input;
	std::stringstream    sin;
	TextDX*         text;

public : 
	Character(Graphics* graphics, Game* game);
	~Character();

	virtual bool collidesWith(Entity &ent, D3DXVECTOR2 &collisionVector);
	virtual void draw();
	virtual void update(float frameTime);
	virtual void initialize();
	//virtual void onHit();

	virtual void setVelocity(D3DXVECTOR2 v);

	void setX(float x);
	void setY(float y);
	void setXY(float x, float y);

	float           aimAngle;
	float           aimSpeed;
	Body*           body;
	bool            crouch;
	int             damageBodyConst;
	int             damageHeadConst;
	float           energy;
	float           energyRegenRate;
	D3DXVECTOR2*    gravity;
	Head*           head;
	float           healthPoints;
	float           healthRegenRate;
	float           initialSpeed;
	float           jumpTime;
	D3DXVECTOR2*    motion;
	float           runAcceleration;
	float           runSpeed;
	StraightPath*   standingOn;
	float           stopSpeed;
	float           walkAcceleration;
	int             walkDir;
	float           walkSpeed;
};

#endif