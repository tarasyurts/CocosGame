#include "EnvironmentUI.h"

EnvironmentUI* EnvironmentUI::environmentUI{ nullptr };

EnvironmentUI* EnvironmentUI::getInstance()
{
	if (environmentUI)
		return environmentUI;
	environmentUI = new EnvironmentUI();
	return environmentUI;
}

void EnvironmentUI::generateTrees()
{

	for (int i = 0; i < TREES_AMOUNT; i++) {
		int randTreeIndex = 0 + rand() % TREES.size();
		double f = (double)rand() / RAND_MAX;
		double scaleFactor = 1.7 + f * (2.4 - 1.7);
		int color = 0 + rand() % 4;

		int randXPosition;
		do {
			randXPosition = 0 + rand() % static_cast<int>(Enviroment::getInstance()->getGroundWidth());

		} while (pointIntersectsTree(randXPosition) || Enviroment::getInstance()->getBorders()->isInKingdom(randXPosition));

		trees.push_back(Sprite::create(TREES.at(randTreeIndex)));
		trees.at(i)->setAnchorPoint(Vec2(0.5, 0));
		trees.at(i)->setPosition(randXPosition, GENERAL_Y);
		trees.at(i)->setScale(scaleFactor);
		if (color == 0) {
			trees.at(i)->setColor(Color3B(222, 198, 172));
		}
		else if (color == 1) {
			trees.at(i)->setColor(Color3B(199, 119, 119));
		}
		if (0 + rand() % 2) {
			trees.at(i)->setFlipX(true);
		}
		trees.at(i)->getTexture()->setAliasTexParameters();
		Enviroment::getInstance()->getScene()->addChild(trees.at(i), TREE_Z_ORDER);

	}

}

void EnvironmentUI::updateTrees()
{
	static stack<Sprite*>* deleteTreesStack = new stack<Sprite*>();
	for each (Sprite * sp in trees)
	{
		if (Enviroment::getInstance()->getBorders()->isInKingdom(sp->getPositionX()))
		{
			deleteTreesStack->push(sp);
			Enviroment::getInstance()->getScene()->removeChild(sp);
		}
	}

	while (deleteTreesStack->size() > 0) {
		for (int i = 0; i < trees.size(); i++) {
			if (trees.at(i) == deleteTreesStack->top()) {
				trees.erase(trees.begin() + i);

				deleteTreesStack->pop();
				if (deleteTreesStack->size() == 0)
					break;
			}
		}
	}
}

void EnvironmentUI::createFence(KingdomBorders* borders)
{

	static vector<Sprite*> fence;

	for each (Sprite* sprite in fence)
	{
		Enviroment::getInstance()->getScene()->removeChild(sprite);
	}


	float tempX = borders->leftX;
	while (tempX < borders->rightX) {
		auto spr = Sprite::create(FENCE_SPR);
		spr->setAnchorPoint(Vec2(0, 0));
		spr->setPosition(tempX,GENERAL_Y);
		spr->getTexture()->setAliasTexParameters();
		fence.push_back(spr);
		Enviroment::getInstance()->getScene()->addChild(spr,FENCE_Z_ORDER);
		tempX += spr->getContentSize().width;
	}

}

bool EnvironmentUI::pointIntersectsTree(float xPos)
{
	for each (Sprite * tree in trees)
	{
		if (tree->getBoundingBox().containsPoint(Vec2(xPos, tree->getPositionY()))) {
			return true;
		}
	}

	return false;
}
