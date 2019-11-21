#pragma once
#include "cocos2d.h"
#include <vector>
#include "Data.h"
#include "Enviroment.h"
#include "FriendlyNPC.h"
//#include "Citizen.h"

USING_NS_CC;

class Citizen{// :public FriendlyNPC {
private:

	Sprite* spr;

public:
	Citizen(Vec2);
	Citizen();

};


class CitizenController 
{

private:
	vector<Citizen*>* citizens;
	CitizenController();
	static CitizenController* citizenController;
public:

	static CitizenController* getInstance();
	void create(Vec2);
};
