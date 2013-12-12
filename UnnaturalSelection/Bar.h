#ifndef BAR_H
#define BAR_H

#include "game.h"
#include "gameError.h"
#include "graphics.h"
#include "image.h"
#include "textureManager.h"

enum Fill { FILL_LR, FILL_CENTER };
enum Mode { NO_BOUNDARY, BKG_COLOR, EDGE_BOUNDS };

namespace barNS {
	const char  BACKGROUND[]    = "pictures\\bar.jpg";
	const int   BOUNDARY_COLOR  = SETCOLOR_ARGB(255, 128, 128, 128);
	const int   BOUNDARY_MARGIN = 1;
	const Mode  BOUNDARY_MODE   = BKG_COLOR;
	const DWORD DEFAULT_COLOR   = SETCOLOR_ARGB(255, 4, 193, 208);
	const float DEFAULT_PERCENT = 1.0f;
	const Fill  FILL            = FILL_LR;
	const int   HEIGHT          = 1;
	const int   WIDTH           = 100;
}

class Bar {
private : 
	Game* game;
	Graphics* graphics;
	TextureManager tmBar;

	Mode boundaryMode;
	Fill fill;

protected : 
	Image bar;
	DWORD boundaryColor;
	DWORD color;
	int height;
	Image indicator1;
	Image indicator2;
	float percent;
	int width;
	float x;
	float xShould;
	float y;

public : 
	Bar(Game* game, Graphics* graphics);
	virtual ~Bar();

	virtual int   getHeight();
	virtual float getPercent();
	virtual int   getWidth();
	virtual float getX();
	virtual float getY();
	virtual void  setCenterX(float x);
	virtual void  setColor(DWORD color);
	virtual void  setHeight(int height);
	virtual void  setPercent(float percent);
	virtual void  setWidth(int width);
	virtual void  setX(float x);
	virtual void  setY(float y);

	virtual void  draw();
	virtual void  initialize(float health = barNS::DEFAULT_PERCENT);
	virtual void  update(float frameTime);
};

#endif