#include "Bar.h"

Bar::Bar(Game* game, Graphics* graphics) :
	boundaryColor(barNS::BOUNDARY_COLOR), boundaryMargin(barNS::BOUNDARY_MARGIN), 
	boundaryMode(barNS::BOUNDARY_MODE), color(barNS::DEFAULT_COLOR), fill(barNS::FILL),
	height(barNS::HEIGHT), game(game), graphics(graphics),percent(barNS::DEFAULT_PERCENT),
	width(barNS::WIDTH), x(0.0f), xShould(0.0f), y(0.0f) {

}

Bar::~Bar() {

}

DWORD Bar::getBoundaryColor() {
	return boundaryColor;
}

int Bar::getBoundaryMargin() {
	return boundaryMargin;
}

Mode Bar::getBoundaryMode() {
	return boundaryMode;
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
	if (!bar.initialize(graphics, width, height, 1, &tmBar)) {
		throw GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize the bar image");
	}

//Initialize the bar boundary(s)?
	if (boundaryMode == BKG_COLOR) {
		if (!indicator1.initialize(graphics, width + 2 * boundaryMargin, height + 2 * boundaryMargin, 1, &tmBar)) {
			throw GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize the bar boundary image");
		}
	} else if (boundaryMode == EDGE_BOUNDS) {
		if (!indicator1.initialize(graphics, boundaryMargin, height + 2 * boundaryMargin, 1, &tmBar) || 
			!indicator2.initialize(graphics, boundaryMargin, height + 2 * boundaryMargin, 1, &tmBar)) {
			throw GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize the bar boundary image");
		}
	}
}

void Bar::setBoundaryColor(DWORD color) {
	boundaryColor = color;
}

void Bar::setBoundaryMargin(int margin) {
	this->boundaryMargin = margin;
}

void Bar::setBoundaryMode(Mode mode) {
	boundaryMode = mode;
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
			indicator1.setX(x - boundaryMargin);
		} else {
			indicator1.setX(xShould - boundaryMargin);
		}

		indicator1.setY(y - boundaryMargin);
		indicator1.update(frameTime);
	} else if (boundaryMode == EDGE_BOUNDS) {
		if (this->fill == FILL_LR) {
			indicator1.setX(x - 2 * boundaryMargin);
			indicator2.setX(x + width + boundaryMargin);
		} else {
			indicator1.setX(xShould - 2 * boundaryMargin);
			indicator2.setX(xShould + width + boundaryMargin);
		}

		indicator1.setY(y - boundaryMargin);
		indicator2.setY(y - boundaryMargin);
		indicator1.update(frameTime);
		indicator2.update(frameTime);
	}
}