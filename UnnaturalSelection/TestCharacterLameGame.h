#ifndef TESTCHARACTERLAMEGAME_H
#define TESTCHARACTERLAMEGAME_H

#include "Character.h"
#include "game.h"
#include "terrainElement.h"

class TestCharacterLameGame : public Game {
private : 
	Character* character;
	StraightPath* testBox;

	TextureManager gunTM, magTM, projectileTM, boxTM;   // textures
	Image   gunIM;
    Image   magIM;
    Image   projectileIM;
	Image	boxIM;

public : 
	TestCharacterLameGame();
	~TestCharacterLameGame();

	void ai();
	void collisions();
	//void consoleCommand();
	void initialize(HWND hwnd);
	void releaseAll();
	void render();
	void resetAll();
	void update();
};

#endif