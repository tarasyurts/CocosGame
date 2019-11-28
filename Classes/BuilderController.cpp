#include "BuilderController.h"


BuilderController* BuilderController::builderController{ nullptr };

BuilderController::BuilderController() {
	
}

BuilderController* BuilderController::getInstance() {
	if (builderController)
		return builderController;

	builderController = new BuilderController();
	return builderController;

}

void BuilderController::create(Vec2 pos) {
	controller.create(pos);
}

void BuilderController::allMoveRand() {
	controller.allMoveRand();
}

void BuilderController::deleteByPos(Vec2 pos) {
	Enviroment::getInstance()->getScene()->removeChild(controller.deleteByPos(pos)->getSpr(), true);
}

Builder* BuilderController::findByPosition(Vec2 pos) {
	return controller.findByPosition(pos);
}

bool BuilderController::setPositionToBuild(Vec2 pos)
{
	Builder* builder = findCosestFree(pos);
	
	if (builder) {
		builder->stopMoving();
		builder->setBuild(true);
		builder->moveStart(pos);
		return true;
	}

	return false;
}

Builder* BuilderController::findCosestFree(Vec2 pos) {
	
	vector<Builder*>* builders = controller.getElems();
	
	Vec2 closest = Vec2(INT32_MAX, INT32_MAX);
	
	for (Builder* tmp : *builders) {
		if (abs(pos.x - closest.x) > abs(pos.x - tmp->getPosition().x) && !(tmp->isBuilding()))
			closest = tmp->getPosition();
	}

	return findByPosition(closest);

}

Builder* BuilderController::findByDestinationPoint(Vec2 pos) {
	vector<Builder*>* builders = controller.getElems();

	for (Builder* tmp : *builders) {
		if (tmp->getCurrentPointMoveTo() == pos) {
			return tmp;
		}
	}

	return nullptr;
}