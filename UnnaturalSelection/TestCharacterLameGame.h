#ifndef TESTCHARACTERLAMEGAME_H
#define TESTCHARACTERLAMEGAME_H

#include "Character.h"
#include "game.h"
#include "Menu.h"

class TestCharacterLameGame : public Game {
private : 
	Menu* menu;

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