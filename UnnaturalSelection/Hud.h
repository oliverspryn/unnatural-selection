#ifndef HUD_H
#define HUD_H

#include "Bar.h"
#include "entity.h"
#include "game.h"
#include "gameError.h"
#include "graphics.h"
#include "HealthBar.h"
#include "image.h"
#include "textureManager.h"

namespace hudNS {
	const char  BACKGROUND[]     = "pictures\\hud-bkg.png";
	const int   BACKGROUND_H     = 80;
	const int   BACKGROUND_W     = 338;
	const float DEFAULT_HEALTH   = 1.0f;
	const float DEFAULT_SCORE    = 0.0f;
	const float DEFAULT_TIME     = 0.0f;

	const bool  HEALTH_BORDER    = false;
	const int   HEALTH_BORDER_LB = 0;
	const int   HEALTH_HEIGHT    = 5;
	const int   HEALTH_WIDTH     = 315;
	const int   HEALTH_X         = GAME_WIDTH / 2 - HEALTH_WIDTH / 2;
	const int   HEALTH_Y         = GAME_HEIGHT - 65;

	const bool  RELOAD_BORDER    = false;
	const int   RELOAD_BORDER_LB = 0;
	const int   RELOAD_HEIGHT    = 5;
	const int   RELOAD_WIDTH     = 315;
	const int   RELOAD_X         = GAME_WIDTH / 2 - RELOAD_WIDTH / 2;
	const int   RELOAD_Y         = GAME_HEIGHT - 45;

	const bool  TIME_BORDER      = true;
	const int   TIME_BORDER_LB   = 3;
	const int   TIME_HEIGHT      = 10;
	const int   TIME_WIDTH       = GAME_WIDTH - (TIME_HEIGHT * 2);
	const int   TIME_X           = 10;
	const int   TIME_Y           = 10;
}

class Hud {
private : 
	Game* game;
	Graphics* graphics;
	TextureManager tmBkg;

	HealthBar* hb;
	Bar*      rb;
	Bar*      tb;

public : 
	Hud(Game* game, Graphics* graphics);
	~Hud();

	float getHealth();
	float getScore();
	float getTime();
	void  setHealth(float health);
	void  setScore(float score);
	void  setTime(float time);

	void draw();
	void initialize(float health = hudNS::DEFAULT_HEALTH, float score = hudNS::DEFAULT_SCORE, float time = hudNS::DEFAULT_TIME);
	void update(float frameTime);
};

#endif