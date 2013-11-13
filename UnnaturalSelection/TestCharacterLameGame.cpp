#include "TestCharacterLameGame.h"

TestCharacterLameGame::TestCharacterLameGame() {

}

TestCharacterLameGame::~TestCharacterLameGame() {
	SAFE_DELETE(testBox);
	releaseAll();
}

void TestCharacterLameGame::ai() {

}

void TestCharacterLameGame::collisions() {
	D3DXVECTOR2 v;

	if (character->collidesWith(*testBox, v)) {
		v.x = 0.0f;
		v.y = 0.0f;

		character->setVelocity(v);
		character->setY(testBox->getY() - 86);
		character->standingOn = testBox;
	}
}

void TestCharacterLameGame::initialize(HWND hwnd) {
	Game::initialize(hwnd);
	character = new Character(graphics, this);

//Box things 
	if (!boxTM.initialize(graphics,"pictures\\box(64x64).png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing box texture"));
	if (!boxIM.initialize(graphics,64,64,entityNS::BOX,&projectileTM))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing box"));

	testBox = new StraightPath(32, 512, D3DXVECTOR2(GAME_WIDTH/2-300, 400));
	testBox->initialize(this, &boxTM, entityNS::ROTATED_BOX);
	testBox->generateSideEquations();

	character->initialize();
	character->setXY(200, 200);
}

void TestCharacterLameGame::releaseAll() {
	Game::releaseAll();
}

void TestCharacterLameGame::render() {
	graphics->spriteBegin();
	character->draw();
	testBox->draw();
	graphics->spriteEnd();
}

void TestCharacterLameGame::resetAll() {
	Game::resetAll();
}

void TestCharacterLameGame::update() {
	character->act();
	character->update(frameTime);
	testBox->update(frameTime);
}