#ifndef TESTCHARACTERLAMEGAME_H
#define TESTCHARACTERLAMEGAME_H

#include "Character.h"
#include "game.h"

class TestCharacterLameGame : public Game {
private : 
	Character* character;

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