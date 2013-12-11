#include "Bar.h"

Bar::Bar(Game* game, Graphics* graphics) : color(barNS::DEFAULT_COLOR), game(game), graphics(graphics), percent(0.0f), x(0.0f), y(0.0f) {

}

Bar::~Bar() {

}

void Bar::draw() {
	bar.draw(color);
}

float Bar::getPercent() {
	return percent;
}

float Bar::getX() {
	return x;
}

float Bar::getY() {
	return y;
}

void Bar::initialize(float health) {
//Initialize the health bar texture manager
	if (!tmBar.initialize(graphics, barNS::BACKGROUND)) {
		throw GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize the health bar texture");
	}

//Initialize the health bar image
	if (!bar.initialize(graphics, barNS::WIDTH, barNS::HEIGHT, 1, &tmBar)) {
		throw GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize the health bar image");
	}

	bar.setX(0.0f);
	bar.setY(0.0f);
}

void Bar::setColor(DWORD color) {
	this->color = color;
}

void Bar::setPercent(float percent) {
	this->percent = percent;
}

void Bar::setX(float x) {
	this->x = x;
}

void Bar::setY(float y) {
	this->y = y;
}

void Bar::update(float frameTime) {
	bar.setX(x);
	bar.setY(y);
	bar.update(frameTime);
}