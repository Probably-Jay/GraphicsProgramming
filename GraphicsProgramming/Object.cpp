#include "Object.h"



Object::Object()
{
}


Object::~Object()
{
	for (auto child : childObjects) {
		delete child;
	}
}

bool Object::initialise(ObjectInfo myInfo, map<ObjectChildrenEnum, vector<ObjectInfo>> * objectInfos)
{
	positon = myInfo.position;
	bool loaded = model.load(myInfo.objFileName, myInfo.texFileName);
	if (positon.y < 1000) {
		return true;
	}
	for (auto childObjInfo : objectInfos->at(myInfo.childrenEnum)) {
		Object * child = new Object();
		loaded = loaded && child->initialise(childObjInfo, objectInfos);
		childObjects.push_back(child);
	}
	return loaded;
}

void Object::render()
{
	glPushMatrix();
		glTranslatef(positon.x, positon.y, positon.z);
		model.render();
		for (auto child : childObjects) {
			child->render();
		}
	glPopMatrix();
}
