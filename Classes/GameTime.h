#pragma once

#include <vector>
#include <map>
#include "cocos2d.h"
#include "IMoveable.h"
#include "ITimeDepended.h"
#include "Data.h"
#include <stack>


using namespace std;

class GameTime {
private:

	using TimeAction = pair<ITimeDepended*, int>;

	static int currentTime;
	static int frameCount;

	static stack<ITimeDepended*> *deleteTimeDependedStack;
	static stack<IMoveable*> *deleteMoveableStack;
	//collection for refreshing objects per frame
	static vector<IMoveable*> *moveableObjects;
	//collection for refreshing objects per pointed second
	static map<ITimeDepended*,int> *timeDependedObjects;

	static void updateByTime();

public:


	static void addTimeDependedObject(int, ITimeDepended*);
	static void addMoveableObject(IMoveable*);
	
	static void removeTimeDependedObject(ITimeDepended*);
	static void removeMoveableObject(IMoveable*);

	static void updateFrame();

	const static int getCurrentTime();
	
	
};

