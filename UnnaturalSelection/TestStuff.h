#ifndef _TESTSTUFF_H             // Prevent multiple definitions if this 
#define _TESTSTUFF_H	          // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "textDX.h"
#include "LMap.h"
#include "gun.h"
#include <vector>
using std::vector;
#include <ctime>
#include <sstream>
using std::stringstream;

namespace teststuffNS
{
	const float cameraMaxBorder(1/4.0f);
	const float cameraMinBorder(1/4.0f);



}

class TestStuff : public Game
{
public:
	TestStuff();

	//destructor
	~TestStuff();

	// Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
	TextureManager gunTM, magTM, projectileTM, boxTM, targetTexture;   // textures
	TextDX	hudFont;
	Image   gunIM;
    Image   magIM;
    Image   projectileIM;
	Image	boxIM;
    Gun* testGun;
	Magazine* testMag;
	Projectile* testProjectile;
	void buildFromFile(std::string fileName);
	string fileNames[5];
	int currentLevel;
	void consoleCommand();
	float gameTime;
	int score;
	bool endGame;
	bool infiniteTime;
	int oldTargets;
private:
	TextureManager terrainTexture;
	LMap* testMap;

	TextureManager openTM, storyTM, controlTM, endTM;
	Image open, story, control, end;
	int controlState;
};

#endif