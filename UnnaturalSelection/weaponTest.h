//Game used to test weapon, gun
//By Michael Wiegand
// 11/5/2013

#ifndef WEAPONTEST_H
#define WEAPONTEST_H
#define WIN32_LEAN_AND_MEAN

#include <string>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "dashboard.h"
#include "gun.h"
#include "camera.h"


namespace weapontestNS
{
	const int BUFFER_SIZE = 20;
}

class LineEq
{
public:
	float yInter;
	float xInter;
	float getSlope()
	{
		return yInter/xInter;
	}

};

class WeaponTest: public Game
{
public:
	/*********************************************
	ALL VARIBLES
	**********************************************/
	TextureManager gunTM, magTM, projectileTM, boxTM;   // textures
	Image   gunIM;
    Image   magIM;
    Image   projectileIM;
	Image	boxIM;
    Gun* testGun;
	Magazine* testMag;
	Projectile* testProjectile;
	Entity* testBox;
    bool    menuOn;
	char buffer[weapontestNS::BUFFER_SIZE];
    float   timer;         // time until new round starts
	int frameCount;
	Camera camera;

	/*********************************************
	ALL FUNCTIONS
	**********************************************/

	// Constructor
    WeaponTest();
    // Destructor
    virtual ~WeaponTest();
    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void consoleCommand(); // process console command
    void roundStart();  // start a new round of play
    void releaseAll();
    void resetAll();
	bool collidesWithMoving(Entity* moving, Entity* object, D3DXVECTOR2 &collisionVector, float &frameTime);
};

#endif