#pragma once
#include "IPayable.h"
#include "FriendlyNPC.h"

class Builder : public FriendlyNPC 
{
private:
	bool isFree;

public:
	Builder(Vec2);
};
