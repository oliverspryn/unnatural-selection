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
	items2.push_back(MenuItem("Old Reliable (Auto) - Fire Rate: 30 rps, Damage: 2, Accuracy: Low", menuNS::ALIGN_CENTER, true));
	items2.push_back(MenuItem("Little Awesome (Semi) - Fire Rate: 15 rps, Damage: 3, Accuracy: Medium", menuNS::ALIGN_CENTER));
	items2.push_back(MenuItem("Schrodinger Shotgun (Semi) - Pellets: 6, Damage: 1, Accuracy: Very Low", menuNS::ALIGN_CENTER));

	MenuCol items;
	items.push_back(MenuItem("Play", menuNS::ALIGN_CENTER, items2));
	items.push_back(MenuItem("Exit", menuNS::ALIGN_CENTER, items2));

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