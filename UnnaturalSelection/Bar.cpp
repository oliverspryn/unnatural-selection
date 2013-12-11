#include "Bar.h"

Bar::Bar(Game* game, Graphics* graphics) :
	boundaryMode(barNS::BOUNDARY_MODE), boundaryColor(barNS::BOUNDARY_COLOR), color(barNS::DEFAULT_COLOR),
	fill(barNS::FILL), height(barNS::HEIGHT), game(game), graphics(graphics), percent(barNS::DEFAULT_PERCENT),
	width(barNS::WIDTH), x(0.0f), xShould(0.0f), y(0.0f) {

}

Bar::~Bar() {

}

void Bar::draw() {
	bar.draw(color);

//Draw the bar boundary(s)?
	if (boundaryMode == BKG_COLOR) {
		indicator1.draw(boundaryColor);
	} else if (boundaryMode == EDGE_BOUNDS) {
		indicator1.draw(boundaryColor);
		indicator2.draw(boundaryColor);
	}
}

int Bar::getHeight() {
	return height;
}

float Bar::getPercent() {
	return percent;
}

int Bar::getWidth() {
	return width;
}

float Bar::getX() {
	return x;
}

float Bar::getY() {
	return y;
}

void Bar::initialize(float health) {
//Initialize the bar texture manager
	if (!tmBar.initialize(graphics, barNS::BACKGROUND)) {
		throw GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize the bar texture");
	}

//Initialize the bar images
	if (!bar.initialize(graphics, barNS::WIDTH, barNS::HEIGHT, 1, &tmBar)) {
		throw GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize the bar image");
	}

//Initialize the bar boundary(s)?
	if (boundaryMode == BKG_COLOR) {
		if (!indicator1.initialize(graphics, barNS::WIDTH + 2 * barNS::BOUNDARY_MARGIN, barNS::HEIGHT + 2 * barNS::BOUNDARY_MARGIN, 1, &tmBar)) {
			throw GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize the bar boundary image");
		}
	} else if (boundaryMode == EDGE_BOUNDS) {
		if (!indicator1.initialize(graphics, barNS::BOUNDARY_MARGIN, barNS::HEIGHT + 2 * barNS::BOUNDARY_MARGIN, 1, &tmBar) || 
			!indicator2.initialize(graphics, barNS::BOUNDARY_MARGIN, barNS::HEIGHT + 2 * barNS::BOUNDARY_MARGIN, 1, &tmBar)) {
			throw GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize the bar boundary image");
		}
	}
}

void Bar::setCenterX(float x) {
	this->fill = FILL_CENTER;
	this->x = 0.0f;
	this->xShould = x;
}

void Bar::setColor(DWORD color) {
	this->color = color;
}

void Bar::setHeight(int height) {
	this->height = height;
}

void Bar::setPercent(float percent) {
	this->percent = percent;
}

void Bar::setWidth(int width) {
	this->width = width;
}

void Bar::setX(float x) {
	this->fill = FILL_LR;
	this->x = x;
	this->xShould = 0.0f;
}

void Bar::setY(float y) {
	this->y = y;
}

void Bar::update(float frameTime) {
//Calculate the position and scale
	float x, y = this->y;

	if (this->fill == FILL_LR) {
		x = this->x;
	} else {
		x = xShould + width * ((1.0f - percent) / 2);
	}

//Don't allow the percentage to fall below 0
	if (percent < 0.0f) {
		percent = 0.0f;
	}

//Set the calculated values and update the bar
	bar.setScaleX(percent);
	bar.setX(x);
	bar.setY(y);
	bar.update(frameTime);

//Update the bar boundary(s)?
	if (boundaryMode == BKG_COLOR) {
		if (this->fill == FILL_LR) {
			indicator1.setX(x - barNS::BOUNDARY_MARGIN);
		} else {
			indicator1.setX(xShould - barNS::BOUNDARY_MARGIN);
		}

		indicator1.setY(y - barNS::BOUNDARY_MARGIN);
		indicator1.update(frameTime);
	} else if (boundaryMode == EDGE_BOUNDS) {
		if (this->fill == FILL_LR) {
			indicator1.setX(x - 2 * barNS::BOUNDARY_MARGIN);
			indicator2.setX(x + width + barNS::BOUNDARY_MARGIN);
		} else {
			indicator1.setX(xShould - 2 * barNS::BOUNDARY_MARGIN);
			indicator2.setX(xShould + width + barNS::BOUNDARY_MARGIN);
		}

		indicator1.setY(y - barNS::BOUNDARY_MARGIN);
		indicator2.setY(y - barNS::BOUNDARY_MARGIN);
		indicator1.update(frameTime);
		indicator2.update(frameTime);
	}
}