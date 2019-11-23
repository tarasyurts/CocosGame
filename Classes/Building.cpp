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

Building::Building(std::string fileName,const int width, const int height)
{
	this->filename = fileName;
	buildingWigth = width;
	buildingHeight = height;
	level = 0;

	spr = Sprite::create(fileName);
	spr->getTexture()->setAliasTexParameters();
	spr->setAnchorPoint(Vec2(0.5, 0));

	Enviroment::getInstance()->getScene()->addChild(spr, BUILDING_Z_ORDER);
}

Building::Building(vector<std::string> images) {

	nextUpgradeDuration = 10;

	levelsImages = images;
	
	spr = Sprite::create(levelsImages.at(level));
	spr->getTexture()->setAliasTexParameters();
	spr->setAnchorPoint(Vec2(0.5, 0));

	Enviroment::getInstance()->getScene()->addChild(spr, BUILDING_Z_ORDER);
}

/*
=====================================================================================================
INTERACTION
=====================================================================================================
*/

void Building::pay(int& sum) {
	int price{0};


	if (Tower* t = dynamic_cast<Tower*>(this))			//���� �� ��'��� � ������
	{
		if (towerLevelsPrices.size() > level) {
			price = towerLevelsPrices[level + 1];
			nextUpgradeDuration = towerTimeBuilding[level + 1];
		}
	}
	else if (Wall* w = dynamic_cast<Wall*>(this))		//���� �� ��'��� � �����
	{
		if (wallLevelsPrices.size() > level) {
			price = wallLevelsPrices[level + 1];
			nextUpgradeDuration = wallTimeBuilding[level + 1];
		}
	}
	else if (Castle* c = dynamic_cast<Castle*>(this))	//���� �� ��'��� � ������
	{
		if (castleLevelsPrices.size() > level) {
			price = castleLevelsPrices[level + 1];
			nextUpgradeDuration = castleTimeBuilding[level + 1];
		}
	}
	else if (Mine* m = dynamic_cast<Mine*>(this))		//���� �� ��'��� � ������
	{
		if (mineLevelsPrices.size() > level) {
			price = mineLevelsPrices[level + 1];
			nextUpgradeDuration = mineTimeBuilding[level + 1];
		}
	}

	if (price < sum && price!=0) {
		sum -= price;
		upgrade();
	}
}


void Building::upgrade() {
	isBuilding = true;
	level++;
	GameTime::addTimeDependedObject(-1, this);

	spr->setTexture(levelsImages.at(level));
	spr->getTexture()->setAliasTexParameters();
}

int Building::getLevel() {
	return level;
}

void Building::timeDependedAction()
{
	if(currentState>nextUpgradeDuration)
	{
		GameTime::removeTimeDependedObject(this);
	}

	currentState++;
	log("%d", currentState);
}


Sprite* Building::getSprite() {
	return spr;
}