#ifndef _TESTSTUFF_H             // Prevent multiple definitions if this 
#define _TESTSTUFF_H	          // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "textDX.h"
#include "LMap.h"
#include <vector>
using std::vector;
#include <ctime>
#include <sstream>
using std::stringstream;

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
private:
	TextureManager terrainTexture;
	LMap* testMap;
};

#endif