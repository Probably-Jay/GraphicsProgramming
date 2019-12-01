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

bool Object::initialise(ObjectInfo myInfo, map<ObjectChildrenEnum, vector<ObjectInfo>> * objectInfos, int parentDepth )
{
	transform = (Transform)myInfo; // upcast to transform

	bool loaded = model.load(myInfo.objFileName, myInfo.texFileName);
	if (parentDepth < 20) {
		for (auto childObjInfo : objectInfos->at(myInfo.childrenEnum)) {
			Object * child = new Object();
			loaded = loaded && child->initialise(childObjInfo, objectInfos, parentDepth+1);
			child->depthOfParents++;
			childObjects.push_back(child);
		}
	}
	return loaded;

}

void Object::render()
{
	glPushMatrix();
		glTranslatef(transform.position.x, transform.position.y, transform.position.z);
		glRotatef(transform.rotationScalar, transform.rotationVector.x, transform.rotationVector.y, transform.rotationVector.z);
		glScalef(transform.scale.x,transform.scale.y,transform.scale.z);
		model.render();
		for (auto child : childObjects) {
			child->render();
		}
	glPopMatrix();
}

void Object::applyTransformToAllChildren(Transform t)
{
	transform = t;
	if (childObjects.size() > 0) {
		for (auto c : childObjects) {
			c->applyTransformToAllChildren(t);
		}
	}
}
