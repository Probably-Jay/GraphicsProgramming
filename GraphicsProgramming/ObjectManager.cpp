#include "ObjectManager.h"



ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
	for (auto obj : objects) {
		delete obj;
	}
}

bool ObjectManager::loadObjects()
{
	for (auto objInfo : objectInfos.at(parents)) {
		Object *obj = new Object();
		objects.push_back(obj);
		if (!obj->initialise(objInfo, &objectInfos)) {
			MessageBox(NULL, "Filepath error", "Error", MB_OK);
			return false;
		}
		
	}
	return true;
}

void ObjectManager::drawObjects()
{
	for (auto obj : objects) {
		obj->render();
	}
}
