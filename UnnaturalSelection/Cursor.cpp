#include "Cursor.h";

Cursor::Cursor(Game* game, Graphics* graphics) : game(game), graphics(graphics) {
	x = y = 0;
	ShowCursor(FALSE);
}

void Cursor::hideCursor() {
	ShowCursor(FALSE);
}

void Cursor::initialize() {
//Initialize the head texture
	if (!tm.initialize(graphics, cursorNS::GRAPHIC))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing the cursor texture... that's a curse"));

//Initialize this Head object
	Image::initialize(graphics, 
		cursorNS::WIDTH, cursorNS::HEIGHT, 
		1, &tm);

//Get the input object
	input = game->getInput();
}

void Cursor::setX(int mouseX) {
	x = mouseX;
}

void Cursor::setXY(int mouseX, int mouseY) {
	x = mouseX;
	y = mouseY;
}

void Cursor::setXY(D3DXVECTOR2 mousePos) {
	x = mousePos.x;
	y = mousePos.y;
}

void Cursor::setY(int mouseY) {
	y = mouseY;
}

void Cursor::showCursor() {
	ShowCursor(TRUE);
}

void Cursor::update(float frametime) {
	Image::update(frametime);

	spriteData.x = x - cursorNS::WIDTH / 2;
	spriteData.y = y - cursorNS::HEIGHT / 2;
}