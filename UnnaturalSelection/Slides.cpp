#include "Slides.h"

Slides::Slides(Game* game, Graphics* graphics) :
	fade(slidesNS::FADE_DEFAULT), game(game), graphics(graphics), show(false), slide(0) {

}

Slides::~Slides() {
	for (int i = 0; i < slides.size(); ++i) {
		delete slides[i];
		delete tmSlides[i];
	}
}

void Slides::addImage(char* image) {
//Create the texture
	TextureManager* tm = new TextureManager();
	
	if (!tm->initialize(graphics, image)) {
		throw GameError(gameErrorNS::FATAL_ERROR, "Could not initialize a slide texture");
	}

	tmSlides.push_back(tm);

//Create the image
	Image* i = new Image();

	if (!i->initialize(graphics, slidesNS::WIDTH, slidesNS::HEIGHT, 1, tm)) {
		throw GameError(gameErrorNS::FATAL_ERROR, "Could not initialize a slide image");
	}

	slides.push_back(i);
}

void Slides::disable(bool fade) {
	this->fade = fade;
	show = false;
}

void Slides::draw() {
	if (show) {
		slides[slide]->draw();
	}
}

void Slides::enable(bool fade) {
	this->fade = fade;
	show = true;
}

int Slides::getSlide() {
	return slide;
}

void Slides::initialize() {
	// Herpty derp
}

void Slides::next() {
	if (slide + 1 < slides.size()) {
		++slide;
	}
}

void Slides::previous() {
	if (slide - 1 >= 0) {
		--slide;
	}
}

void Slides::setFade(bool fade) {
	this->fade = fade;
}

void Slides::setSlide(int slide, bool fade) {
	this->fade = fade;
	this->slide = slide;
}

void Slides::update(float frameTime) {
	if (show) {
		slides[slide]->update(frameTime);
	}
}