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


namespace weapontestNS
{
	const int BUFFER_SIZE = 20;
}


class WeaponTest: public Game
{
public:
	/*********************************************
	ALL VARIBLES
	**********************************************/
	TextureManager gunTM, magTM, projectileTM;   // textures
	Image   gunIM;
    Image   magIM;
    Image   projectileIM;
    Gun* testGun;
	Magazine* testMag;
	Projectile* testProjectile;
    bool    menuOn;
	char buffer[weapontestNS::BUFFER_SIZE];
    float   timer;         // time until new round starts
	int frameCount;


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
};

#endif