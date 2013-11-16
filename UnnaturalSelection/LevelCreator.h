#ifndef _LEVELCREATOR_H
#define _LEVELCREATOR_H

#include "game.h"
#include "textureManager.h"
#include "textDX.h"
#include "LMap.h"
//#include "terrainElement.h"


class LevelCreator : public Game
{
public:
	LevelCreator();

	//destructor
	~LevelCreator();

	// Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
	void consoleCommand();
private:
	TextureManager terrainTexture;
	LMap* testMap;
};

#endif