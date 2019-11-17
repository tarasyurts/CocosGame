#pragma once

#include <vector>
#include <map>
#include "cocos2d.h"
#include "IMoveable.h"
#include "ITimeDepended.h"

using namespace std;

class GameTime {
	using TimeAction = pair<int, ITimeDepended*>;
private:

	static int currentTime;
	static int frameCount;

	static vector<IMoveable*>* moveableObjects;
	static map<int, ITimeDepended*>* timeDependedObjects;

	static void updateByTime();

public:


	static void addTimeDependedObject(int, ITimeDepended*);
	static void addMoveableObject(IMoveable*);
	
	static void removeTimeDependedObject(int);
	static void removeMoveableObject(IMoveable*);

	static void updateFrame();

	const static int getCurrentTime();
	
	
};


