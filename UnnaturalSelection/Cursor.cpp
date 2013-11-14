#include "Cursor.h";

Cursor::Cursor(Game* game, Graphics* graphics) : game(game), graphics(graphics) {
	ShowCursor(FALSE);
}

Cursor::~Cursor() {
	SAFE_DELETE(game);
	SAFE_DELETE(graphics);
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

void Cursor::showCursor() {
	ShowCursor(TRUE);
}

void Cursor::update(float frametime) {
	Image::update(frametime);
	int x = input->getMouseX(), y = input->getMouseY();

	spriteData.x = x - cursorNS::WIDTH / 2;
	spriteData.y = y - cursorNS::HEIGHT / 2;
}