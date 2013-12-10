#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <ctime>

#include "game.h"
#include "graphics.h"
#include "image.h"
#include "textureManager.h"

namespace backgroundNS {
	const int  EARTH_TINT_MIN    = 0;
	const int  GLOW_ALPHA_MIN    = 120;
	const int  SUN_ALPHA_MIN     = 0;
	const int  SUN_Y_START       = 35;

	const int  EARTH_TINT_TARGET = 255;
	const int  GLOW_ALPHA_TARGET = 170;
	const int  SUN_ALPHA_TARGET  = 255;
	const int  SUN_Y_TARGET      = 0;

	const char EARTH[]           = "pictures\\earth.png";
	const char GLOWING_EARTH[]   = "pictures\\glowing-earth.png";
	const char STARS[]           = "pictures\\stars.jpg";
	const char SUN[]             = "pictures\\sun.png";
}

class Background {
private : 
	double fadeDuration;
	Game* game;
	Graphics* graphics;
	double multiplier;
	clock_t start;
	double timer;

	Image earth;
	Image glowEarth;
	Image stars;
	Image sun;

	TextureManager tmEarth;
	TextureManager tmGlowEarth;
	TextureManager tmStars;
	TextureManager tmSun;

public : 
	Background(Game* game, Graphics* graphics);
	~Background();

	void draw();
	void initialize(double fadeDuration);
	void update(float frameTime);
};

#endif