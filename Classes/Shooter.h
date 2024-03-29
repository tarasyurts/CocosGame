#pragma once
#include "cocos2d.h"
#include "Data.h"
#include "EnemyController.h"
#include "ITimeDepended.h"

USING_NS_CC;

class Shooter 
{
protected:

	Node* targetEnemy = nullptr;
	Sprite* shooterSpr;
	Node* node;
	PhysicsBody* createPhysicsBodyShootDiapason();
	Sprite* createArrow();
	Spawn* createFlyAction(int, int);

public:

	Shooter(Sprite*);


	Node* getTarget();
	Node* getNode();

	virtual void setTarget(Node*) = 0;
	virtual void removeTarget() = 0;
	void shoot(Vec2);
};

class ArrowEraser : ITimeDepended {
private:

	Sprite* arrow;

public:

	ArrowEraser(Sprite* );
	void setTimeDependedAction();
	virtual void timeDependedAction() override;
	virtual ~ArrowEraser() {};

};
