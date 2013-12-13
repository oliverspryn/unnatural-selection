#ifndef SLIDES_H
#define SLIDES_H

#include <string>
#include <vector>

#include "game.h"
#include "gameError.h"
#include "graphics.h"
#include "image.h"
#include "textureManager.h"

using std::string;
using std::vector;

namespace slidesNS {
	const float ALPHA_DELTA  = 0.001f;
	const float FADE_DEFAULT = true;
	const int   HEIGHT       = GAME_HEIGHT;
	const int   WIDTH        = GAME_WIDTH;
}

class Slides {
private : 
public : 
	Game* game;
	Graphics* graphics;

	bool fade;
	bool show;
	int slide;
	vector<Image*> slides; // Shhh...
	vector<TextureManager*> tmSlides; // Shhh...


	Slides(Game* game, Graphics* graphics);
	~Slides();

	int getSlide();
	void setFade(bool fade);
	void setSlide(int slide, bool fade = slidesNS::FADE_DEFAULT);

	void addImage(char* image);
	void disable(bool fade = slidesNS::FADE_DEFAULT);
	void enable(bool fade = slidesNS::FADE_DEFAULT);
	void next();
	void previous();

	void draw();
	void initialize();
	void update(float frameTime);
};

#endif