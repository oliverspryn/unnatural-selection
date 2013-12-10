#include "Background.h"

Background::Background(Game* game, Graphics* graphics) : fadeDuration(0.0), game(game), graphics(graphics), multiplier(0.0), timer(0.0) {

}


Background::~Background() {
	//Yeah... don't delete the Game pointer :D
}

void Background::draw() {
	if (multiplier < 1) {
		int earthTint = backgroundNS::EARTH_TINT_MIN + ((backgroundNS::EARTH_TINT_TARGET - backgroundNS::EARTH_TINT_MIN) * multiplier);
		int glowAlpha = backgroundNS::GLOW_ALPHA_MIN + ((backgroundNS::GLOW_ALPHA_TARGET - backgroundNS::GLOW_ALPHA_MIN) * multiplier);
		int sunAlpha = backgroundNS::SUN_ALPHA_MIN + ((backgroundNS::SUN_ALPHA_TARGET - backgroundNS::SUN_ALPHA_MIN) * multiplier);
		int sunY = backgroundNS::SUN_Y_START - ((backgroundNS::SUN_Y_START - backgroundNS::SUN_Y_TARGET) * multiplier);

		sun.setY(sunY);

		stars.draw();
		sun.draw(SETCOLOR_ARGB(sunAlpha, 255, 255, 255));
		glowEarth.draw(SETCOLOR_ARGB(glowAlpha, 255, 255, 255));
		earth.draw(SETCOLOR_ARGB(255, earthTint, earthTint, earthTint));
	} else {
		stars.draw();
		sun.draw(SETCOLOR_ARGB(backgroundNS::SUN_ALPHA_TARGET, 255, 255, 255));
		glowEarth.draw(SETCOLOR_ARGB(backgroundNS::GLOW_ALPHA_TARGET, 255, 255, 255));
		earth.draw(SETCOLOR_ARGB(255, backgroundNS::EARTH_TINT_TARGET, backgroundNS::EARTH_TINT_TARGET, backgroundNS::EARTH_TINT_TARGET));
	}
}

void Background::initialize(double fadeDuration) {
//Start the clock!
	start = clock();
	this->fadeDuration = fadeDuration;

//Initialize each of the textures
	if (!tmEarth.initialize(graphics, backgroundNS::EARTH) ||
		!tmGlowEarth.initialize(graphics, backgroundNS::GLOWING_EARTH) ||
		!tmStars.initialize(graphics, backgroundNS::STARS) ||
		!tmSun.initialize(graphics, backgroundNS::SUN)) {
			throw GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize at least one background component");
	}

//Initialize each of the images
	earth.initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 1, &tmEarth);
	glowEarth.initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 1, &tmGlowEarth);
	stars.initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 1, &tmStars);
	sun.initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 1, &tmSun);
}

void Background::update(float frameTime) {
//Update the clock
	timer = (std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC);

	if (multiplier >= 1.0) {
		multiplier = 1;
	} else {
		multiplier = timer / fadeDuration;
	}

//Draw all the sprites
	earth.draw(frameTime);
	glowEarth.draw(frameTime);
	stars.draw(frameTime);
	sun.draw(frameTime);
}