#include "ObjectManager.h"



ObjectManager::ObjectManager()
{
	modelManager.loadModels();
}


ObjectManager::~ObjectManager()
{
	for (auto obj : objects) {
		delete obj;
	}
}

void ObjectManager::loadObjects()
{
	for (auto obj : objects) {
		obj->initialise(modelManager);
	
	}

	for (auto objInfo : objectInfos.at(ObjectChildrenEnum::parents)) {
		Object *obj = new Object();
		objects.push_back(obj);
		obj->initialise(objInfo, modelManager,  &objectInfos);
	}
	
}

void ObjectManager::drawObjects()
{
	for (auto obj : objects) {
		obj->render();
	}
}
