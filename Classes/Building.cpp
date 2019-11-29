#include "Building.h"
#include "Tower.h"
#include "Wall.h"
#include "Castle.h"
#include "Mine.h"
#include "Data.h"
#include "Enviroment.h"
/*
=====================================================================================================
CONSTRUCTORS
=====================================================================================================
*/


Building::Building(const vector<std::string>* images) {

	nextUpgradeDuration = 10;
	setBuildingStatus(false);

	levelsImages = images;
	
	spr = Sprite::create(levelsImages->at(level));
	spr->getTexture()->setAliasTexParameters();
	spr->setAnchorPoint(Vec2(0.5, 0));
	spr->addComponent(createPhysBody());
		
	Enviroment::getInstance()->getScene()->addChild(spr, BUILDING_Z_ORDER);
}

/*
=====================================================================================================
INTERACTION
=====================================================================================================
*/

PhysicsBody* Building::createPhysBody() {
	PhysicsBody* pb = PhysicsBody::createBox(spr->getBoundingBox().size);
	pb->setDynamic(false);
	pb->setContactTestBitmask(BUILDING_COLLIDE_BM);
	pb->setCategoryBitmask(BUILDING_CATEGORY_BM);
	pb->setCollisionBitmask(BUILDING_COLLIDE_BM);
	return pb;
}

void Building::updateEnviromentData()
{
	Enviroment::getInstance()->setBorders(BuildingController::getInstance()->getKingdomBorders());
	Enviroment::getInstance()->updateTrees();
}


void Building::upgrade() {
		
	if(!isBuilding && BuilderController::getInstance()->setPositionToBuild(this->getPosition()))
		GameTime::addTimeDependedObject(-1, this);
}

void Building::timeDependedAction()
{
	if (currentState > nextUpgradeDuration)
	{
		GameTime::removeTimeDependedObject(this);

		level++;

		BuilderController::getInstance()->findByDestinationPoint(getPosition())->setBuild(false);
		BuilderController::getInstance()->findByDestinationPoint(getPosition())->moveRandStart();

		spr->setTexture(levelsImages->at(level));
		spr->getTexture()->setAliasTexParameters();
		spr->removeAllComponents();
		spr->addComponent(createPhysBody());

		if (spr->getTag() == SprTag::WALL) {
			BuildingController::getInstance()->findWallByPos(spr->getPosition())->setHP(WALL_HP.at(level));
		}
		
		isBuilding = false;
		currentState = 0;
	}

	if(isBuilding == true)
		currentState++;

	log("%d", currentState);
}

int Building::getLevel() {
	return level;
}

void Building::setBuildingStatus(bool status) {
	isBuilding = status;
}


Vec2 Building::getPosition() {
	return spr->getPosition();
}

Sprite* Building::getSprite() {
	return spr;
}