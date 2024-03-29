#pragma once
#include"Payable.h"
#include "NPC.h"

USING_NS_CC;

class FriendlyNPC : public NPC , public Payable 
{

protected:


	bool isActive;
	bool isMovingRand;
	FriendlyNPC(Vec2);

	//Animation
	Animate* idle;
	Animate* run;

	Sprite* selectorSpr;

public:

	void setUnactive();
	void setActive();

	void moveRandStart();

	Vec2 getCurrentPointMoveTo();
	void stopMoving();

	
	virtual void move() override;
	virtual void setSelector() override;

	virtual void pay(int&) override;

	virtual bool canBeAttacked() override;
	virtual void hit(int) override;
};
