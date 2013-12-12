#include "Hud.h"

Hud::Hud(Game* game, Graphics* graphics) : game(game), graphics(graphics) {

}

Hud::~Hud() {

}

void Hud::draw() {
	hb->draw();
	rb->draw();
	tb->draw();
}