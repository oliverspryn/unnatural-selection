#ifndef TIMER_BAR_H
#define TIMER_BAR_H

#include "Bar.h"

namespace timerBarNS {
	const DWORD TIMER_BAD_COLOR  = SETCOLOR_ARGB(255, 1, 111, 110);
	const DWORD TIMER_FAIR_COLOR = SETCOLOR_ARGB(255, 55, 155, 253);
	const DWORD TIMER_GOOD_COLOR = SETCOLOR_ARGB(255, 55, 253, 252);

	const float TIMER_BAD_VALUE  = 0.2f;
	const float TIMER_FAIR_VALUE = 0.4f;
}

class TimerBar : public Bar {
public : 
	TimerBar(Game* game, Graphics* graphics);
	~TimerBar();

	void draw();
};

#endif