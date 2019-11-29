#pragma once
#include "BaseController.h"
#include "Enemy.h"

class EnemyController : public ITimeDepended {
private:

	static int enemNum;

	BaseController<Enemy> controller;
	EnemyController();
	static EnemyController* enemyController;
public:

	static EnemyController* getInstance();
	void create(Vec2);
	void deleteByPos(Vec2);
	void findAndMoveTo(Vec2);
	void allMoveTo(Vec2);
	virtual void timeDependedAction() override;
	Enemy* findByPosition(Vec2);

	void startSpawn(int, Vec2);
};

