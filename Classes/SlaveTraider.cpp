#include "SlaveTraider.h"


/*
=====================================================================================================
init
=====================================================================================================
*/


SlaveTraider* SlaveTraider::slaveTraider{ nullptr };

SlaveTraider::SlaveTraider() : saledSlaves(0)
{
	spr = Sprite::create(SLAVE_TRAIDER_SPR);
	spr->setAnchorPoint(Vec2(0, 0));
	spr->setPosition(Vec2(SLAVE_TRAIDER_START_X, GENERAL_Y));
	spr->setTag(SprTag::SLAVE_TRAIDER);
	spr->getTexture()->setAliasTexParameters();
	spr->addComponent(createPhysBody());
	
	GameTime::addTimeDependedObject(SLAVE_TRAIDER_APPERANCE, this);
	GameTime::addTimeDependedObject(SLAVE_TRAIDER_DISAPPERANCE, this);
	
	Enviroment::getInstance()->getScene()->addChild(spr, NPC_Z_ORDER);

	spr->setVisible(false);
	spr->pause();
}

SlaveTraider* SlaveTraider::getInstance() {
	if (slaveTraider)
		return slaveTraider;
	slaveTraider = new SlaveTraider();
	return slaveTraider;
}

PhysicsBody* SlaveTraider::createPhysBody() {
	PhysicsBody* pb = PhysicsBody::createBox(spr->getBoundingBox().size);
	pb->setDynamic(false);
	pb->setCategoryBitmask(SLAVE_TRAIDER_CATEGORY_BM);
	pb->setCollisionBitmask(SLAVE_TRAIDER_COLLIDE_BM);
	pb->setContactTestBitmask(SLAVE_TRAIDER_COLLIDE_BM);
	return pb;
}


/*
=====================================================================================================
createCitizen and pay
=====================================================================================================
*/


void SlaveTraider::pay(int &money) {
	if (money >= SLAVE_PRICE && saledSlaves < SLAVE_AMMOUNT_PER_DAY) {
		money -= SLAVE_PRICE;
		saledSlaves++;
		createCitizen();
	}
}


void SlaveTraider::createCitizen() 
{
	CitizenController::getInstance()->create(slaveTraider->spr->getPosition());
}

void SlaveTraider::setSelector()
{
	setSelectorSpr(spr);
}



void SlaveTraider::timeDependedAction() {
	if (!spr->isVisible()) {
		spr->setVisible(true);
		spr->resume(); 
	}
	else {
		spr->setVisible(false);
		spr->pause();
		saledSlaves = 0;
	}
}

