#ifndef BAR_H
#define BAR_H

#include "game.h"
#include "gameError.h"
#include "graphics.h"
#include "image.h"
#include "textureManager.h"

namespace barNS {
	const char  BACKGROUND[]    = "pictures\\bar.jpg";
	const DWORD DEFAULT_COLOR   = SETCOLOR_ARGB(255, 4, 193, 208);
	const float DEFAULT_PERCENT = 1.0f;
	const int   HEIGHT          = 1;
	const int   WIDTH           = 400;
}

class Bar {
private : 
	Game* game;
	Graphics* graphics;
	TextureManager tmBar;

protected : 
	Image bar;
	DWORD color;
	int height;
	float percent;
	int width;
	float x;
	float y;

public : 
	Bar(Game* game, Graphics* graphics);
	virtual ~Bar();

	virtual int getHeight();
	virtual float getPercent();
	virtual int getWidth();
	virtual float getX();
	virtual float getY();
	virtual void setHeight(int height);
	virtual void setPercent(float percent);
	virtual void setWidth(int width);
	virtual void setX(float x);
	virtual void setY(float y);

	virtual void draw();
	virtual void initialize(float health = barNS::DEFAULT_PERCENT);
	virtual void setColor(DWORD color);
	virtual void update(float frameTime);
};

#endif