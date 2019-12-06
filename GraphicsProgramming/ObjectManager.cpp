#include "ObjectManager.h"



ObjectManager::ObjectManager()
{
	modelManager.loadModels();
	objects.push_back(&spaceship);
}


ObjectManager::~ObjectManager()
{
	for (auto obj : objects) {
		delete obj;
	}
}

void ObjectManager::loadObjects(LightManager * _lightManager)
{
	lightManager = _lightManager;
	for (auto objInfo : objectInfos.at(ObjectChildrenEnum::parents)) {
		Object *obj = new Object();
		objects.push_back(obj);
		obj->initialise(objInfo, modelManager, lightManager, &objectInfos);
	}


	for (auto obj : objects) {
		obj->initialise(modelManager,lightManager);
	}

	
}

void ObjectManager::updateObjects(float dt)
{
	for (auto obj : objects) {
		obj->update(dt);
	}
}

void ObjectManager::drawObjects()
{
	for (auto obj : objects) {
		obj->render();
	}
}

void ObjectManager::moveSpaceship(Vector3 vec, bool addToCurrentPosition )
{
	if (addToCurrentPosition) {
		spaceship.transform.position += vec;
	}
	else {
		spaceship.transform.position = vec;
	}
}
