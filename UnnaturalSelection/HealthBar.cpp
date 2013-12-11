#include "HealthBar.h"

HealthBar::HealthBar(Game* game, Graphics* graphics) : Bar(game, graphics) {

}

HealthBar::~HealthBar() {

}

void HealthBar::draw() {
	Bar::draw();
	DWORD color;

//Determine the health bar color
	if (percent >= healthBarNS::HEALTH_FAIR_VALUE) {
		color = healthBarNS::HEALTH_GOOD_COLOR;
	} else if (percent >= healthBarNS::HEALTH_BAD_VALUE && percent < healthBarNS::HEALTH_FAIR_VALUE) {
		color = healthBarNS::HEALTH_FAIR_COLOR;
	} else {
		color = healthBarNS::HEALTH_BAD_COLOR;
	}

	bar.draw(color);
}