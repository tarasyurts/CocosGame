#pragma once

#include "cocos2d.h"
#include "IMoveable.h"
#include "Payable.h"
#include "ITimedepended.h"
#include "Enviroment.h"
#include "Data.h"
#include "CitizenController.h"
#include "GameOverScene.h"
#include "UI.h"

USING_NS_CC;

class Player :private IMoveable, public IAttackable {

private:

	int money;
	int m_HP;

	bool isFocused;
	bool isDisabledChoseRoleListener;

	MoveDirection direction;
	
	EventListenerKeyboard* moveListener;
	EventListenerKeyboard* buyListener;
	EventListenerKeyboard* choseRoleListener;
	
	Sprite* spr;

	//Animation
	Animate* idle;
	Animate* run;

	//
	
	Payable* objInFocus;
	//Direction direction;

	static Player* player;

	Player(const std::string);
	
	void setCamera();
	
	PhysicsBody* createPhysBody();

	void initMoveListener();
	void initBuyListener();
	void initChoseRoleListener();

	void changeMoveDirection(EventKeyboard::KeyCode, bool);
	
public:
	static Player* getInstance();
	Sprite* getSprite();

	void moveBackground(int);

	void addMoney(int);
	int& getMoney();

	void addHP(int);
	int& getHP();

	void addChild(Node*);
	void removeAllChildren();

	void move() override ;

	void disableFocusBuyListener();
	void disableBuyListener();
	
	void setPayable(Payable*);
	bool checkFocusedObj(Payable*);
	bool focused();

	void enableChoseRoleListener();
	
	virtual void hit(int) override;
	virtual bool canBeAttacked() override;

	void removeAllListeners();
};

	
