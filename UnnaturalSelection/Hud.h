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
	const char  BKG[]           = "pictures\\hud.png";
	const int   BKG_HEIGHT      = 80;
	const int   BKG_WIDTH       = 338;
	const int   BKG_X           = GAME_WIDTH / 2 - BKG_WIDTH / 2;
	const int   BKG_Y           = GAME_HEIGHT - BKG_HEIGHT;

	const float DEFAULT_HEALTH   = 1.0f;
	const float DEFAULT_RELOAD   = 0.0f;
	const float DEFAULT_TIME     = 0.0f;

	const Mode  HEALTH_BORDER    = NO_BOUNDARY;
	const int   HEALTH_BORDER_LB = 0;
	const int   HEALTH_HEIGHT    = 5;
	const int   HEALTH_WIDTH     = 315;
	const int   HEALTH_X         = GAME_WIDTH / 2 - HEALTH_WIDTH / 2;
	const int   HEALTH_Y         = GAME_HEIGHT - 65;

	const Mode  RELOAD_BORDER    = NO_BOUNDARY;
	const int   RELOAD_BORDER_LB = 0;
	const int   RELOAD_HEIGHT    = 5;
	const int   RELOAD_WIDTH     = 315;
	const int   RELOAD_X         = GAME_WIDTH / 2 - RELOAD_WIDTH / 2;
	const int   RELOAD_Y         = GAME_HEIGHT - 45;

	const Mode  TIME_BORDER      = BKG_COLOR;
	const int   TIME_BORDER_LB   = 3;
	const int   TIME_HEIGHT      = 10;
	const int   TIME_WIDTH       = GAME_WIDTH - (TIME_HEIGHT * 2);
	const int   TIME_X           = 10;
	const int   TIME_Y           = 10;
}

class Hud {
private : 
	Image bkg;
	Game* game;
	Graphics* graphics;
	TextureManager tmBkg;

	float health;
	float reload;
	float time;

	HealthBar* hb;
	HealthBar*      rb;
	HealthBar*      tb;

public : 
	Hud(Game* game, Graphics* graphics);
	~Hud();

	float getHealth();
	float getReload();
	float getTime();
	void  setHealth(float health);
	void  setReload(float reload);
	void  setTime(float time);

	void draw();
	void initialize(float health = hudNS::DEFAULT_HEALTH, float reload = hudNS::DEFAULT_RELOAD, float time = hudNS::DEFAULT_TIME);
	void update(float frameTime);
};

#endif