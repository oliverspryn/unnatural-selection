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
#include "terrainElement.h"


namespace weapontestNS
{
	const int BUFFER_SIZE = 20;
}

class FunctionTimer
{
public:
	FunctionTimer(int size): size(size)
	{
		top = 0;
		time = new float[size];
		counts = new int[size];
		updated = new bool[size];
		beginTimer = new LARGE_INTEGER[size];
		endTimer = new LARGE_INTEGER[size];
		message = new std::string[size];
		for(int i(0); i < size; i++)
		{
			time[i] = 0;
			counts[i] = 0;
			updated[i] = false;
			message[i] = "No function";
		}
	}
	~FunctionTimer()
	{
		delete [] time;
		delete [] counts;
		delete [] updated;
		delete [] beginTimer;
		delete [] endTimer;
		delete [] message;
	}
	//updates all the bools so the count adds one
	void nextFrame()
	{
		for(int i(0); i < size; i++)
		{
			updated[i] = false;
		}
	}
	void starting(int index)
	{
		if(!(updated)[index])
		{
			(counts)[index]++;
			(updated)[index] = true;
		}
		QueryPerformanceCounter(&(beginTimer)[index]);
	}
	void ending(int index, LARGE_INTEGER &timerFreq)
	{
		QueryPerformanceCounter(&(endTimer)[index]);
		(time)[index] += (float)((endTimer)[index].QuadPart-(beginTimer)[index].QuadPart)/(float)timerFreq.QuadPart;
	}
	float getAverageTime(int index)
	{
		if(index < size && (counts)[index] > 0)
		{
			return (time)[index]/(counts)[index];
		}
		else
		{
			return 0;
		}
	}
	std::string getName(int index)
	{
		if(index < size)
		{
			return (message)[index];
		}else{
			return "Not In Bounds";
		}
	}
	int getSize()
	{
		return size;
	}
private:
	int size;
	float (*time);
	int (*counts);
	bool (*updated);
	LARGE_INTEGER (*beginTimer);
	LARGE_INTEGER (*endTimer);
	std::string (*message);
	int top;


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
	//Entity* testBox;
	StraightPath* testBox;
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
	bool collidesWithMoving(D3DXVECTOR2* movingPos, D3DXVECTOR2* movingVelocity, TerrainElement* object, float &angle, float &frameTime);
	bool collidesWithMovingRay(D3DXVECTOR2* movingPos, D3DXVECTOR2* movingVelocity, float slope, float b, D3DXVECTOR2 corner1, D3DXVECTOR2 corner2, float &frameTime);
};

#endif