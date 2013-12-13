#include "Hud.h"

Hud::Hud(Game* game, Graphics* graphics) :
	health(hudNS::DEFAULT_HEALTH), game(game), graphics(graphics),
	reload(hudNS::DEFAULT_RELOAD), time(hudNS::DEFAULT_TIME) {

}

Hud::~Hud() {

}

void Hud::draw() {
	bkg.draw(D3DCOLOR_ARGB(100, 255, 255, 255));
	hb->draw();
	rb->draw();
	tb->draw();
}

float Hud::getHealth() {
	return health;
}

float Hud::getReload() {
	return reload;
}

float Hud::getTime() {
	return time;
}

void Hud::initialize(float health, float reload, float time) {
	this->health = health;
	this->reload = reload;
	this->time = time;

//Initialize the background texture
	if (!tmBkg.initialize(graphics, hudNS::BKG)) {
		throw GameError(gameErrorNS::WARNING, "Failed to initialize the HUD texture");
	}

//Initialize the background image
	if (!bkg.initialize(graphics, hudNS::BKG_WIDTH, hudNS::BKG_HEIGHT, 1, &tmBkg)) {
		throw GameError(gameErrorNS::WARNING, "Failed to initialize the HUD image");
	}

	bkg.setX(hudNS::BKG_X);
	bkg.setY(hudNS::BKG_Y);

//Initialize the barz!
	hb = new HealthBar(game, graphics);
	rb = new HealthBar(game, graphics);
	tb = new HealthBar(game, graphics);

	hb->setBoundaryMargin(hudNS::HEALTH_BORDER_LB);
	hb->setBoundaryMode(hudNS::HEALTH_BORDER);
	hb->setCenterX(hudNS::HEALTH_X);
	hb->setHeight(hudNS::HEALTH_HEIGHT);
	hb->setWidth(hudNS::HEALTH_WIDTH);
	hb->setY(hudNS::HEALTH_Y);

	rb->setBoundaryMargin(hudNS::RELOAD_BORDER_LB);
	rb->setBoundaryMode(hudNS::RELOAD_BORDER);
	rb->setCenterX(hudNS::RELOAD_X);
	rb->setHeight(hudNS::RELOAD_HEIGHT);
	rb->setWidth(hudNS::RELOAD_WIDTH);
	rb->setY(hudNS::RELOAD_Y);

	tb->setBoundaryMargin(hudNS::TIME_BORDER_LB);
	tb->setBoundaryMode(hudNS::TIME_BORDER);
	tb->setCenterX(hudNS::TIME_X);
	tb->setHeight(hudNS::TIME_HEIGHT);
	tb->setWidth(hudNS::TIME_WIDTH);
	tb->setY(hudNS::TIME_Y);

	hb->initialize(health);
	rb->initialize(reload);
	tb->initialize(time);
}

void Hud::setHealth(float health) {
	this->health = health;
	hb->setPercent(health);
}

void Hud::setReload(float relaod) {
	this->reload = reload;
	rb->setPercent(reload);
}

void Hud::setTime(float time) {
	this->time = time;
	tb->setPercent(time);
}

void Hud::update(float frameTime) {
	hb->setPercent(health);
	rb->setPercent(reload);
	tb->setPercent(time);

	bkg.update(frameTime);
	hb->update(frameTime);
	rb->update(frameTime);
	tb->update(frameTime);
}