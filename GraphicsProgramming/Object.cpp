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

void Object::initialise(ObjectInfo myInfo, ModelManager & modelManager, LightManager * lightManager, map<ObjectChildrenEnum, vector<ObjectInfo>> * objectInfos , int parentDepth )
{
	transform = (Transform)myInfo; // upcast to transform
	alpha = myInfo.alpha;
	model = modelManager.getModel(myInfo.modelName);

	if (parentDepth < MAX_CHILD_DEPTH && objectInfos!= nullptr) {
		for (auto childObjInfo : objectInfos->at(myInfo.childrenEnum)) {
			Object * child = new Object();
			child->initialise(childObjInfo, modelManager, lightManager, objectInfos,  parentDepth+1);
			child->depthOfParents++;
			childObjects.push_back(child);
		}
	}
	//return loaded;

}

void Object::update(float dt)
{
	spaceshipUpdate(dt);
}

void Object::spaceshipUpdate(float dt)
{
}

void Object::render()
{
	glPushMatrix();
		glTranslatef(transform.position.x, transform.position.y, transform.position.z);
		glRotatef(transform.rotationScalar, transform.rotationVector.x, transform.rotationVector.y, transform.rotationVector.z);
		glScalef(transform.scale.x,transform.scale.y,transform.scale.z);
		model->render(alpha);
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

void Object::initialise(ModelManager& modelManager, LightManager* lightmanager)
{
	// virtual function
}

//void Object::renderJustMe()
//{
//}
