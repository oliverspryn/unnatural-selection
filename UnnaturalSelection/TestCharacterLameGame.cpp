#include "TestCharacterLameGame.h"

TestCharacterLameGame::TestCharacterLameGame() {

}

TestCharacterLameGame::~TestCharacterLameGame() {
	releaseAll();
}

void TestCharacterLameGame::ai() {

}

void TestCharacterLameGame::collisions() {

}

void TestCharacterLameGame::initialize(HWND hwnd) {
	Game::initialize(hwnd);
	character = new Character(graphics, this);

	character->initialize();
	character->setXY(100, 300);
}

void TestCharacterLameGame::releaseAll() {
	Game::releaseAll();
}

void TestCharacterLameGame::render() {
	graphics->spriteBegin();
	character->draw();
	graphics->spriteEnd();
}

void TestCharacterLameGame::resetAll() {
	Game::resetAll();
}

void TestCharacterLameGame::update() {
	character->act();
	character->update(frameTime);
}