#include "AI.h"

AI::AI(Game* game, Graphics* graphics) : Character(game, graphics) {
		//throw "ertyui";
	target = 0;
	firing = false;
	sightDistance = 500;
	minShootDistance = 50;
	shootDistance = 1400;

	hb = new HealthBar(game, graphics);
}