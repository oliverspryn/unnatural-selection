//The implemintation of weaponTest
//By Michael Wiegand
// 11/5/2013

#include "weaponTest.h"
#include <sstream>
#include <math.h>

//=============================================================================
// Constructor
//=============================================================================
WeaponTest::WeaponTest()
{
    menuOn = true;
	timer = 0;
	frameCount = 0;
	
    initialized = false;
}

//=============================================================================
// Destructor
//=============================================================================
WeaponTest::~WeaponTest()
{
    releaseAll();           // call onLostDevice() for every graphics item
	if(testGun > 0)
	{
		delete testGun;
	}
	if(testMag > 0)
	{
		delete testMag;
	}
	if(testProjectile > 0)
	{
		delete testProjectile;
	}
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void WeaponTest::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

    // Gun texture
    if (!gunTM.initialize(graphics,"pictures\\AssultRifle(128x32).png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun texture"));

    // Weapon texture
    if (!magTM.initialize(graphics,"pictures\\mag(8x8).png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mag texture"));

    // Projectile textures
    if (!projectileTM.initialize(graphics,"pictures\\projectile(8x8).png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing projectile textures"));

    if (!gunIM.initialize(graphics,0,0,0,&gunTM))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gun"));

    if (!magIM.initialize(graphics,0,0,0,&magTM))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mag"));

	if (!projectileIM.initialize(graphics,0,0,0,&projectileTM))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing projectile"));

	testProjectile = new Projectile(&projectileTM, this, 8, 8, entityNS::CIRCLE, 1);
//	testMag = 0;
	//testProjectile->setStats(30, 100, 100, 200);

	testMag = new Magazine(400, 90, 90, 1, 100, 20, ONE, testProjectile);
	//testGun = 0;
	testGun = new Gun(10, 60*60, 100, 400, 700, 20, 5, 2.0, BURST_THREE, ONE, testMag);
	//My initialize code
	//testGun->mag = testMag;

	testGun->initialize(this, 128, 32, entityNS::NONE, &gunTM);
	//testGun->mag = testMag;
	//testMag->projectile = testProjectile;
//	testMag->projArray[0] = testProjectile;
	testGun->setX(GAME_WIDTH/2-testGun->getWidth()/2);
	testGun->setY(GAME_HEIGHT/2);
    
	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void WeaponTest::update()
{
	timer += frameTime;
	frameCount += 1;
    if (menuOn)
    {
        if (input->anyKeyPressed())
        {
            menuOn = false;
            input->clearAll();
            roundStart();
        }
    } 
    else 
    {
		testGun->setAngle(atan2(input->getMouseY()-testGun->getCenterY(), input->getMouseX()-testGun->getCenterX()));
		testGun->act(frameTime, input->getMouseLButton(), input->getMouseRButton(), false, false, false);
		//testGun->mag->updateMagsProjectiles(frameTime);
		if(input->getMouseLButton())
		{
			//testMag->fire(D3DXVECTOR2(input->getMouseX()+10, input->getMouseY() - 10), PI*(((rand()%1000)-500)/1000.0)/6);
		}
		if(input->getMouseRButton())
		{
			//testGun->fire(frameTime);
		}
		testMag->updateMagsProjectiles(frameTime);
		//testMag->projectile->update(frameTime);
		

		/*if(testProjectile->getActive())
		{
			testProjectile->update(frameTime);
		}*/
    }
}

//=============================================================================
// Start a new round of play
//=============================================================================
void WeaponTest::roundStart()
{
    // Start ships on opposite sides of Star in stable clockwise orbit
   
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void WeaponTest::ai()
{

}

//=============================================================================
// Handle collisions
//=============================================================================
void WeaponTest::collisions()
{
    VECTOR2 collisionVector;
    
}

//=============================================================================
// Render game items
//=============================================================================
void WeaponTest::render()
{
    graphics->spriteBegin();                // begin drawing sprites

	graphics->setBackColor(graphicsNS::CYAN);
	//testProjectile->draw();
	testMag->displayMagsProjectiles();
	//testMag->projectile->draw();
	testGun->draw();

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// process console commands
//=============================================================================
void WeaponTest::consoleCommand()
{
    command = console->getCommand();    // get command from console
    if(command == "")                   // if no command
        return;

    if (command == "help")              // if "help" command
    {
        console->print("Console Commands:");
        console->print("fps");
        console->print("afps");
        return;
    }
    if (command == "fps")
    {
		std::stringstream temp;
		temp << "FPS: " << 1.0/frameTime;
		console->print(temp.str());
		return;
    }
	if (command == "afps")
    {
		std::stringstream temp;
		temp << "Average FPS: " << 1.0/(timer/frameCount);
		console->print(temp.str());
		return;
    }
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void WeaponTest::releaseAll()
{
    gunTM.onLostDevice();
    magTM.onLostDevice();
    projectileTM.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void WeaponTest::resetAll()
{
    gunTM.onResetDevice();
    magTM.onResetDevice();
    projectileTM.onResetDevice();

    Game::resetAll();
    return;
}
