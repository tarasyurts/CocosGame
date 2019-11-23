#include "FriendlyNPC.h"
#include"Enviroment.h"

/*
=====================================================================================================
Init
=====================================================================================================
*/

FriendlyNPC::FriendlyNPC(Vec2 pos, std::string sprName) {
	
	setActive();
	isMoving = false;

	spr = Sprite::create(sprName);
	spr->setPosition(pos);
	spr->setAnchorPoint(Vec2(0.5, 0));
	spr->addComponent(createPhysBody());

	moveStart();
	Enviroment::getInstance()->getScene()->addChild(spr, NPC_Z_ORDER);
}


PhysicsBody* FriendlyNPC::createPhysBody() {
	PhysicsBody* pb = PhysicsBody::createBox(spr->getBoundingBox().size);
	pb->setContactTestBitmask(true);
	pb->setDynamic(false);
	return pb;
}

/*
=====================================================================================================
move and position
=====================================================================================================
*/

Vec2 FriendlyNPC::getPosition() {
	return spr->getPosition();
}

void FriendlyNPC::moveStart() {
	GameTime::addMoveableObject(this);
	//isMoving = true;
}


void FriendlyNPC::moveTo(Vec2 destination) {
	int direction;
	int delta = destination.x - spr->getPosition().x;

	if (delta >= 0)
		direction = 1;
	else
		direction = -1;

	spr->setPosition(spr->getPosition().x + direction * FRIENDLY_NPC_MOVE_SPEED, spr->getPosition().y);

	if (spr->getPosition().x - FRIENDLY_NPC_MOVE_SPEED / 2 <= destination.x &&
		spr->getPosition().x + FRIENDLY_NPC_MOVE_SPEED / 2 >= destination.x)
	{
		isMoving = false;
	}
}

void FriendlyNPC::move() {

	if (!isMoving) {
		//SET KINGDOM BORDER
		currentPointToMove = randPoint(0, 3000);
		isMoving = true;
	}
	moveTo(currentPointToMove);

}

Vec2 FriendlyNPC::randPoint(int fromX, int toX) {
	Vec2 point(0, GENERAL_Y);
	point.x = fromX + ((rand() * std::time(0)) % (fromX - toX));
	return point;
}

void FriendlyNPC::stopMoving() {
	GameTime::removeMoveableObject(this);
	//isMoving = false;
}

/*
=====================================================================================================
active/unactive
=====================================================================================================
*/


void FriendlyNPC::setUnactive() {
	isActive = false;
}

void FriendlyNPC::setActive() {
	isActive = true;
}


/*
=====================================================================================================
get set
=====================================================================================================
*/

Sprite* FriendlyNPC::getSpr() {
	return spr;
}