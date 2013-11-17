#ifndef CURSOR_H
#define CURSOR_H

#include "game.h"
#include "graphics.h"
#include "image.h"
#include "textureManager.h"

namespace cursorNS {
	const char GRAPHIC[] = "pictures\\target.png";
	const int  HEIGHT    = 32;
	const int  WIDTH     = 32;
}

class Cursor : public Image {
private : 
	Game*          game;
	Graphics*      graphics;
	Input*         input;
	TextureManager tm;
	int            x;
	int            y;

public : 
	Cursor(Game* game, Graphics* graphics);

	void hideCursor();
	void initialize();
	void setX(int mouseX);
	void setXY(int mouseX, int mouseY);
	void setXY(D3DXVECTOR2 mousePos);
	void setY(int mouseY);
	void showCursor();
	void update(float frametime);
};

#endif