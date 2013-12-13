#ifndef CHARACTER_H
#define CHARACTER_H
//#define SHOW_ANGLE

#include <cmath>

#include "Body.h"
#include "Cursor.h"
#include "game.h"
//#include "Head.h"
#include "terrainElement.h"
#include "gun.h"

#ifdef SHOW_ANGLE
#include <sstream>
#include "textDX.h"
#endif

namespace characterNS {
//Character gameplay configuration
	const float AIM_ANGLE         = 90.0f;   // Initial angle, in degrees, which the Character is aiming a weapon
	const float AIM_SPEED         = 0.9f;    // The speed a which the Character can aim the weapon
	const float ENERGY            = 100.0f;  // Initial starting energy
	const int   DAMAGE_BODY_CONST = 5;       // A value decremeted from the Character who receives body damage
	const int   DAMAGE_HEAD_CONST = 10;      // A value decremeted from the Character who receives head damage
	const float ENERGY_REGEN_RATE = 1.002f;  // The rate, per frame, which the Character regerates energy
	const float HEALTH_POINTS     = 300.0f;  // Initial starting health
	const float HEALTH_REGEN_RATE = 1.0f;    // The rate, per frame, which the Character regerates health
	const float GRAVITY_X         = 1.0f;    // Direction and speed of gravity, in the X direction
	const float GRAVITY_Y         = 980.0f;  // Direction and speed of gravity, in the Y direction
	const float INITIAL_SPEED     = 50.0f;   // The speed at which the Character starting moving
	const float END_SPEED		  = 100.0f;	 // The speed at which the character stops imeaditly
	const float JUMP_TIME         = 0.7f;    // Amount of time for the jump to reach max height
	const float MASS              = 1.0f;    // The mass of the Character
	const float RUN_ACCELERATION  = 2.0f;    // The rate, per frame, which the speed will increase to running
	const float RUN_SPEED         = 30.0f;   // The maximum running speed
	const float STOP_SPEED        = 800.0f;  // The rate, per frame, which the speed will decrease to 0
	const float WALK_ACCELERATION = 600.0f;  // The rate, per frame, which the speed will increase to walking
	const float WALK_SPEED        = 500.0f;  // The maximum walking speed

//Input keys
	const UCHAR CROUCH            = 'S';
	const UCHAR JUMP              = VK_SPACE;
	const UCHAR WALK_LEFT         = 'A';
	const UCHAR WALK_RIGHT        = 'D';
}

class Character {
protected : 
	int sign(float x);
	virtual void jump();
	virtual void updateCorners();
	int velSign();
	virtual void walk(float frametime);

	Game*           game;
	Graphics*       graphics;
	Input*          input;

	#ifdef SHOW_ANGLE
	std::stringstream sin;
	TextDX          aimText;
	#endif

public : 
	Character(Game* game, Graphics* graphics, float hp = characterNS::HEALTH_POINTS);
	virtual ~Character();

	virtual bool collidesWith(Entity &ent, D3DXVECTOR2 &collisionVector);
	virtual void draw();
	virtual void initialize();
	virtual void update(float frameTime);
	virtual void update(float frameTime, bool rightButton, bool leftButton, bool jumpButton, bool shootButton, bool reloadButton);

	float getCenterX();
	float getCenterY();
	D3DXVECTOR2 getCenter();
	int   getHeight();
	float getVelMagnitude();
	D3DXVECTOR2 getVelocity();
	float getVelocityX();
	float getVelocityY();
	int   getWidth();
	float getX();
	float getY();

	virtual void setVelocity(D3DXVECTOR2 v);
	virtual void setVelocityX(float x);
	virtual void setVelocityY(float y);
	void setX(float x);
	void setXC(float x);
	void setXY(float x, float y);
	void setXYC(float x, float y);
	void setY(float y);
	void setYC(float y);

	float           aimAngle;
	Body*           body;
	D3DXVECTOR2     corners[4];
	Cursor*         cursor;
	int             damageBodyConst;
	int             damageHeadConst;
	float           energy;
	float           energyRegenRate;
	int             faceDir;
	D3DXVECTOR2*    gravity;
	//Head*           head;
	float			startHealth;
	float           healthPoints;
	float           healthRegenRate;
	float           initialSpeed;
	float           jumpTime;
	float           runAcceleration;
	float           runSpeed;
	TerrainElement*   standingOn;
	float           stopSpeed;
	float           walkAcceleration;
	float           walkSpeed;
	float			charFrameTime;
	float			reloadTimer;
	bool			reloadStep;

	Weapon*			currentWeapon;
	Magazine*		currentMag;
	D3DXVECTOR2		weaponPos;

	int			invertColorCount;
};

#endif