#include "TimerBar.h"

TimerBar::TimerBar(Game* game, Graphics* graphics) : Bar(game, graphics) {

}

TimerBar::~TimerBar() {

}

void TimerBar::draw() {
	Bar::draw();
	DWORD color;

//Determine the timer bar color
	if (percent >= timerBarNS::TIMER_FAIR_VALUE) {
		color = timerBarNS::TIMER_GOOD_COLOR;
	} else if (percent >= timerBarNS::TIMER_BAD_VALUE && percent < timerBarNS::TIMER_FAIR_VALUE) {
		color = timerBarNS::TIMER_FAIR_COLOR;
	} else {
		color = timerBarNS::TIMER_BAD_COLOR;
	}

	bar.draw(color);
}