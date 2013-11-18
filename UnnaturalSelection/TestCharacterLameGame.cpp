#include "TestCharacterLameGame.h"

void testo();

TestCharacterLameGame::TestCharacterLameGame() {}

TestCharacterLameGame::~TestCharacterLameGame() {
	releaseAll();
}

void TestCharacterLameGame::ai() {}

void TestCharacterLameGame::collisions() {}

void TestCharacterLameGame::initialize(HWND hwnd) {
	Game::initialize(hwnd);
	menu = new Menu(this, graphics);

//Create the menu
	MenuCol items2;
	items2.push_back(MenuItem("Yay", true));
	items2.push_back(MenuItem("Yay1"));
	items2.push_back(MenuItem("Weep"));

	MenuCol items;
	items.push_back(MenuItem("Play", true));
	items.push_back(MenuItem("Level Select"));
	items.push_back(MenuItem("Customize Weapon"));
	items.push_back(MenuItem("Options", false, items2));
	items.push_back(MenuItem("Exit", false, testo));

	menu->initialize(items);
}

void TestCharacterLameGame::releaseAll() {
	Game::releaseAll();
}

void TestCharacterLameGame::render() {
	graphics->spriteBegin();
	menu->draw();
	graphics->spriteEnd();
}

void TestCharacterLameGame::resetAll() {
	Game::resetAll();
}

void TestCharacterLameGame::update() {
	menu->update(frameTime);
}

void testo() {
	MessageBox(NULL, "Yay!", "Error", MB_OK);
}