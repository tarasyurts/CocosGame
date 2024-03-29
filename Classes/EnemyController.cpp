#include "EnemyController.h"
#include "BuildingController.h"
#include "EnvironmentUI.h"

int EnemyController::enemNum = 0;

EnemyController* EnemyController::enemyController{ nullptr };

EnemyController::EnemyController() : isInfinityWave(false), difficulty(1) {
	GameTime::addTimeDependedObject(DAY_DURATION / 2, this);
}

EnemyController* EnemyController::getInstance() {
	if (enemyController)
		return enemyController;

	enemyController = new EnemyController();
	return enemyController;

}

void EnemyController::create(Vec2 pos) {
	controller.create(pos);
}

void EnemyController::findAndMoveTo(Vec2 pos) {
	findByPosition(pos)->moveStart(BuildingController::getInstance()->getCastlePos());
}

void EnemyController::deleteByPos(Vec2 pos) {
	//findByPosition(pos)->stopMoving();
	controller.deleteByPos(pos);
}

Enemy* EnemyController::findByPosition(Vec2 pos) {
	return controller.findByPosition(pos);
}

void EnemyController::allMoveTo(Vec2 pos) {
	for (Enemy* tmp : *controller.getElems()) {
		tmp->moveStart(pos);
	}
}

void EnemyController::startSpawn(int numOfEnemys, Vec2 posToSpawn) {
	for (int i = 0; i < numOfEnemys; i++) {
		create(posToSpawn);
	}
	allMoveTo(BuildingController::getInstance()->getCastlePos());
}

void EnemyController::timeDependedAction() {
	
	EnvironmentUI::getInstance()->setDarkness();

	startSpawn(enemNum, Vec2(0, GENERAL_Y));
	startSpawn(enemNum, Vec2(Enviroment::getInstance()->getGroundWidth(), GENERAL_Y));
	
	if (WarriorController::getInstance()->areFree()) 
	{
		GameTime::addTimeDependedObject(-1, WarriorController::getInstance());
	}
	
	if(!isInfinityWave)
		enemNum += difficulty;
}

void EnemyController::allStopMove() {
	GameTime::removeTimeDependedObject(this);
	controller.allStopMove();
}

bool EnemyController::enemiesAreAlive() {
	if (controller.getElems()->size() > 0) {
		return true;
	}
	return false;
}

void EnemyController::startInfinitySpawn() {
	isInfinityWave = true;
	
	enemNum = ENEMY_LAST_WAVE_QUANTITY_PER_SEC;

	GameTime::removeTimeDependedObject(this);
	GameTime::addTimeDependedObject(-1, this);

}



