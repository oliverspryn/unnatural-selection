//The implemintation of weaponTest
//By Michael Wiegand
// 11/5/2013

#include "weaponTest.h"
#include <sstream>
#include <math.h>
#include "line.h"

class Boxxy: public Entity
{
public:
	Boxxy(): Entity()
	{
		setX(900);
		setY(GAME_HEIGHT/2);
		spriteData.width = 64;           // size of Ship1
		spriteData.height = 64;
		collisionType = entityNS::ROTATED_BOX;
		//this->setW

		//spriteData.rect.bottom = this->getCenterY()-32;    // rectangle to select parts of an image
		//spriteData.rect.right = this->getCenterX()+32;
		//spriteData.rect.left = this->getCenterX()-32;
		//spriteData.rect.top = this->getCenterY()+32;
		spriteData.scale = 1;
		this->setDegrees(45);

		RECT r;
		r.bottom = 32;
		r.top = -32;
		r.left = -16;
		r.right = 16;
		edge = r;
		//this->E
		mass = 1;
	}
};

//=============================================================================
// Constructor
//=============================================================================
WeaponTest::WeaponTest(): camera(400, 400, 0, 0, GAME_WIDTH/2, GAME_HEIGHT/2, 1), fTimer(4)
{
	fTimer.Add("Draw");
	fTimer.Add("Collision Detection");
	fTimer.Add("RayTrace");
    menuOn = true;
	testBox = 0;
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
	if(testBox != 0)
	{
		delete testBox;
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

	//Box things 
	if (!boxTM.initialize(graphics,"pictures\\box(64x64).png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing box texture"));
	if (!boxIM.initialize(graphics,64,64,entityNS::BOX,&projectileTM))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing box"));

	testBox = new TerrainElement(32, 128, D3DXVECTOR2(GAME_WIDTH/2+300, 300));
	testBox->initialize(this, &boxTM, entityNS::ROTATED_BOX);
	//testBox->setRadians(-PI/2);
	//testBox->setDegrees(0.001);
	testBox->generateSideEquations();
	
	//testBox->setSpriteDataRect(r);*/
	


	testProjectile = new Projectile(&projectileTM, this, 8, 8, entityNS::CIRCLE, 1);
//	testMag = 0;
	//testProjectile->setStats(30, 100, 100, 200);

	testMag = new Magazine(40000, 40000, 40000, 1, 100, 100, ONE, testProjectile); 
	//testGun = 0;
	testGun = new Gun(10, 30*60*60, 100, 600, 200, 100, 30, 2.0, 0, ONE);
	testGun->loadNewMag(testMag);
	//testGun->setRadians(PI/2);
	//My initialize code
	//testGun->mag = testMag;

	testGun->initialize(this, 128, 32, entityNS::NONE, &gunTM);
	//testGun->mag = testMag;
	//testMag->projectile = testProjectile;
//	testMag->projArray[0] = testProjectile;
	testGun->setX(GAME_WIDTH/2-testGun->getWidth()/2-0);
	testGun->setY(GAME_HEIGHT/2);
    
	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void WeaponTest::update()
{
	fTimer.nextFrame();
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
		//testGun->setAngle(atan2(input->getMouseY()-testGun->getCenterY(), input->getMouseX()-testGun->getCenterX()));
		testGun->setAngle(atan2(camera.getRealPos(input->getMouseX(), input->getMouseY()).y-testGun->getCenterY(), camera.getRealPos(input->getMouseX(), input->getMouseY()).x-testGun->getCenterX()));
		
		testGun->act(frameTime, input->getMouseLButton(), input->getMouseRButton(), false, false, false);
		//testGun->mag->updateMagsProjectiles(frameTime);
		if(input->getMouseLButton())
		{
			//testMag->fire(D3DXVECTOR2(input->getMouseX()+10, input->getMouseY() - 10), PI*(((rand()%1000)-500)/1000.0)/6);
		}
		if(input->getMouseRButton())
		{
			//testGun->fire(frameTime);
			camera.centerPosition = D3DXVECTOR2(input->getMouseX(), input->getMouseY());
		}
		//testMag->updateMagsProjectiles(frameTime);
		//testMag->projectile->update(frameTime);
		if(input->isKeyDown('1'))
		{
			camera.zoom = max(0.1, camera.zoom - frameTime*.5);
		}
		if(input->isKeyDown('2'))
		{
			camera.zoom = min(10, camera.zoom + frameTime*.5);
		}
		if(input->isKeyDown('3'))
		{
			testBox->setDegrees(testBox->getDegrees()+45*frameTime);
			testBox->generateSideEquations();
		}
		if(input->isKeyDown('4'))
		{
			testBox->setDegrees(testBox->getDegrees()-45*frameTime);
			testBox->generateSideEquations();
		}

		/*if(testProjectile->getActive())
		{
			testProjectile->update(frameTime);
		}*/
		testBox->update(frameTime);

		//Used for collisions
		VECTOR2 collisionVector;
		fTimer.starting(1);
		for(int i(0); i < testMag->size+1; i++)
		{
			if(testMag->projArray[i]->getActive())
			{
				float ft = frameTime;
				float angle = 0;
				if(collidesWithMoving(const_cast<D3DXVECTOR2*>(testMag->projArray[i]->getCenter()), const_cast<D3DXVECTOR2*>(&testMag->projArray[i]->getVelocity()), testBox, angle, ft))
//				if(collidesWithMovingRay(testMag->projArray[i], testBox->m[0], testBox->b[0], testBox->corners[0], testBox->corners[3], collisionVector, frameTime))
				{
					//throw "GHJKL:";
//					float newAngle = angle;
//					newAngle -= abs(testMag->projArray[i]->getRadians()-newAngle);
					//newAngle = (testMag->projArray[i]->getRadians()+PI);
					//newAngle -= (newAngle - testMag->projArray[i]->getRadians());
					//newAngle = PI - newAngle;
					//testMag->projArray[i]->update(frameTime-ft);
//					testMag->projArray[i]->setVelocity(D3DXVECTOR2(testMag->projArray[i]->muzzelVelocity*cos(newAngle),testMag->projArray[i]->muzzelVelocity*sin(newAngle)));
//					testMag->projArray[i]->setRadians(newAngle);

					testMag->projArray[i]->setActive(false);
					testMag->projArray[i]->setVisible(false); 
				}else{
					//Need to use mag update just for this
					//testMag->projArray[i]->update(frameTime);
				}
			}
		}
		fTimer.ending(1, timerFreq);
		if(testMag != 0)
		{
			testMag->updateMagsProjectiles(frameTime);
		}
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
 //   VECTOR2 collisionVector;
	//float frameTime = 0;
 //   for(int i(0); i < testMag->size+1; i++)
	//{
	//	if(testMag->projArray[i]->getActive())
	//	{
	//		if(collidesWithMoving(testMag->projArray[i], testBox, collisionVector, frameTime))
	//		{
	//			//throw "GHJKL:";
	//			testMag->projArray[i]->setActive(false);
	//			testMag->projArray[i]->setVisible(false); 
	//		}
	//	}
	//}
}

//=============================================================================
// Render game items
//=============================================================================
void WeaponTest::render()
{
	fTimer.starting(0);
    graphics->spriteBegin();                // begin drawing sprites

	graphics->setBackColor(graphicsNS::CYAN);
	//testProjectile->draw();
	testMag->displayMagsProjectiles();
	//testMag->projectile->draw();
	testGun->draw();
	testBox->draw();
	camera.draw(*testBox);
	camera.draw(*testGun);
	for(int i(0); i < testMag->size+1; i++)
	{
		camera.draw(*testMag->projArray[i]);

	}

    graphics->spriteEnd();                  // end drawing sprites
	fTimer.ending(0, timerFreq);
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
        console->print("ftimes");
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
	if (command == "ftimes")
    {
		for(int i(0); i < fTimer.getSize(); i++)
		{
			std::stringstream temp;
			temp << fTimer.getName(i) << ": " << fTimer.getAverageTime(i)/(timer/frameCount);
			console->print(temp.str());
		}
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
	boxTM.onLostDevice();

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
	boxTM.onResetDevice();

    Game::resetAll();
    return;
}




float getXIntersept(float m1, float b1, float m2, float b2)
{
	return ((b2-b1)/(m1-m2));
}


bool WeaponTest::collidesWithMoving(D3DXVECTOR2* movingPos, D3DXVECTOR2* movingVelocity, TerrainElement* object, float &angle, float &frameTime)
{

	//Gives the place that intersects on the circle
	//float x = (k+k*(a*a)-sqrt(r*r*a*a+r*r*a*a*a*a))/(1+a*a);
	//float y = sqrt(r*r-(x-k)*(x-k))+h;
	//Equation for one 
	bool hit(false);
	myLines::Ray movingLine(*movingPos, *movingVelocity, sqrt(movingVelocity->x*movingVelocity->x + movingVelocity->y*movingVelocity->y)*frameTime);
	float ct = frameTime;
	fTimer.starting(2);
	for(int i(0); i < 4; i++)
	{
//		D3DXVECTOR2 tempDist = object->corners[(3+i)%4]-object->corners[i];
//		myLines::Ray tempLineSide(object->corners[i], tempDist, (i%2?object->getHeight():object->getWidth()));
		float ft = frameTime;

		if(movingLine.getTimeOfIntersectRay(object->sides[i], ft))
		//if(movingLine.getTimeOfIntersectRay(tempLineSide, ft))
		{
			if(0 <= ft && ft < ct)
			//if(collidesWithMovingRay(movingPos, movingVelocity, object->m[i], object->b[i], object->corners[i], object->corners[(3+i)%4], frameTime))
			{
				hit = true;
				ct = ft;
				angle = (i*PI/2)+ object->getRadians();
	//			angle = (i%2?-1:1)*(i*PI/2)+ object->getRadians();
			}
		}
	}
	fTimer.ending(2, timerFreq);
	//Only one Plane
  	/*if(collidesWithMovingRay(moving, object->m[2], object->b[2], object->corners[2], object->corners[(3+2)%4], collisionVector, frameTime))
	{
		return true;
	}*/
	if(hit)
	{
		frameTime = ct;
		return true;
	}
	return false;
	
}

bool WeaponTest::collidesWithMovingRay(D3DXVECTOR2* movingPos, D3DXVECTOR2* movingVelocity, float slope, float b, D3DXVECTOR2 corner1, D3DXVECTOR2 corner2, float &frameTime)
{
	//the angle between the box and projectile
	float m1 = movingVelocity->y/movingVelocity->x;
	float x1 = movingPos->x;
	float y1 = movingPos->y;
	float b1 = y1 - m1*x1;
	float d = abs(-PI/2);

	float x = getXIntersept(m1, b1, slope, b);

	//If the plane is horizontal 
	if(corner1.y == corner2.y)
	{
		if(min(corner1.x, corner2.x) < x1 && x1 < max(corner1.x, corner2.x))
		//makes sure it is with in the frame time
		if(abs(frameTime*movingVelocity->x) > abs(x-x1))
		{
			frameTime = (x1-x)/movingVelocity->x;
			return true;
		}else{
			return false;
		}
	}

	if(min(corner1.y, corner2.y) < m1*x + b1 && m1*x + b1 < max(corner1.y, corner2.y))
	if(min(corner1.x, corner2.x) < x1 + abs(movingVelocity->x*frameTime) && x1 - abs(movingVelocity->x*frameTime) < max(corner1.x, corner2.x))
	//makes sure it is with in the frame time
	if(abs(frameTime*movingVelocity->x) > abs(x-x1))
	{
		frameTime = (x1-x)/movingVelocity->x;
		return true;
	}else{
		return false;
	}

	return false;
}