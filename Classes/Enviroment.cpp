#include "Enviroment.h"

Enviroment* Enviroment::enviroment{ nullptr };

Scene* Enviroment::getScene() {
	return scene;
}

void Enviroment::setGroundSpr(const std::string fileName) {
	groundSpr = Sprite::create(fileName);
	groundSpr->setAnchorPoint(Vec2(0, 0));
	scene->addChild(groundSpr, PLAYER_Z_ORDER);
}

void Enviroment::setScene(Scene* scene) {
	this->scene = scene;
	addComponents();
}

Enviroment* Enviroment::getInstance() {
	if (enviroment)
		return enviroment;
	enviroment = new Enviroment();
	return enviroment;
}

void Enviroment::addComponents() {
	setGroundSpr(GROUND);
	Player::getInstance();
}