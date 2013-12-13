#ifndef _TESTSTUFF_H             // Prevent multiple definitions if this 
#define _TESTSTUFF_H	          // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "textDX.h"
#include "GearhartTutorialLevel.h"
#include "GearhartArenaLevel.h"
#include "GearhartBossLevel.h"
#include "LMap.h"
#include "gun.h"
#include "Menu.h"
#include "Background.h"
#include "HealthBar.h"
#include "Hud.h"
#include "Slides.h"
#include <vector>
using std::vector;
#include <ctime>
#include <sstream>
using std::stringstream;

enum LEVEL { STORY, MENU, PLAY };

static int controlState = 1;
static LEVEL mode;
static void incrementCounter(int index, string text);
static void endGameNow(int a, string b);
static int totalScore;

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
	TextureManager gunTM, magTM, projectileTM, boxTM, targetTexture, turretTexture;   // textures
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
	Menu* menu;
	Background* background;
	HealthBar* healthBar;
	Hud* hud;
	int spawnNumToPrint;
	int terrainNumToPrint;
	Menu* betweenLevel;
	MenuCol gunList;
	Slides *slides;

	void achievements();
	string recentAchievement;
	bool doneAchievements[10];

	void TestStuff::save();
	void TestStuff::load();
	void addScore(int in);
	
	std::string scoreString;
	int scores[10];
	int scoreIndex;
private:
	TextureManager terrainTexture;
	//make an array of levels
	LMap** levels;
	//LMap* testMap;
	int numLevels;
	//TutorialLevel* introMap;
	bool down;
};

#endif