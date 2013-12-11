#ifndef HEALTH_BAR_H
#define HEALTH_BAR_H

#include "Bar.h"

namespace healthBarNS {
	const DWORD HEALTH_BAD_COLOR  = SETCOLOR_ARGB(255, 255, 0, 0);
	const DWORD HEALTH_FAIR_COLOR = SETCOLOR_ARGB(255, 255, 255, 0);
	const DWORD HEALTH_GOOD_COLOR = SETCOLOR_ARGB(255, 0, 255, 0);

	const float HEALTH_BAD_VALUE  = 0.2f;
	const float HEALTH_FAIR_VALUE = 0.4f;
}

class HealthBar : public Bar {
public : 
	HealthBar(Game* game, Graphics* graphics);
	~HealthBar();

	void draw();
};

#endif