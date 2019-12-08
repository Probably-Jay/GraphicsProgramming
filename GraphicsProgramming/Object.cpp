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

bool Object::initialise(ObjectInfo myInfo, ModelManager & modelManager, LightManager * lightManager, map<ObjectChildrenEnum, vector<ObjectInfo>> * objectInfos , int parentDepth )
{
	
	info = myInfo;
	transform = (Transform)myInfo; // upcast to transform
	alpha = myInfo.alpha;
	model = modelManager.getModel(myInfo.modelName);

	bool transparent = (alpha < 1.f); // transparent objects must be drawn last for them to both depth sort and alpha blend correctly

	if (parentDepth < MAX_CHILD_DEPTH && objectInfos!= nullptr) {
		for (auto childObjInfo : objectInfos->at(myInfo.childrenEnum)) {
			Object * child = new Object();
			transparent |= child->initialise(childObjInfo, modelManager, lightManager, objectInfos,  parentDepth+1);
			child->depthOfParents++;
			childObjects.push_back(child);
		}
	}
	isOrContainsTransparentObject = transparent;
	return transparent;

}

void Object::update(float dt)
{
	for (auto child : childObjects) {
		child->update(dt);
	}
}

//void Object::spaceshipUpdate(float dt)
//{
//}
//
//void Object::spaceshipdoLighting()
//{
//}

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

void Object::doLighting()
{
	for (auto l : lights) {
		l->doLighting();
	}
	for (auto child : childObjects) {
		child->doLighting();
	}
}

void Object::applyTransformToAllChildren(Transform t)
{
	if (depthOfParents > 0) {
		transform = t;
	}
		if (childObjects.size() > 0) {
			for (auto c : childObjects) {
				c->applyTransformToAllChildren(t);
			}
		}
	
}

void Object::renderShadow()
{
	glPushMatrix();
	//glTranslatef(transform.position.x, transform.position.y, transform.position.z);
	//glRotatef(transform.rotationScalar, transform.rotationVector.x, transform.rotationVector.y, transform.rotationVector.z);
	//glScalef(transform.scale.x, transform.scale.y, transform.scale.z);
	model->renderShadow();
	for (auto child : childObjects) {
		child->renderShadow();
	}
	glPopMatrix();
}

bool Object::initialise(ModelManager& modelManager, LightManager* lightmanager)
{
	// virtual function
	return isOrContainsTransparentObject;
}

//void Object::renderJustMe()
//{
//}
