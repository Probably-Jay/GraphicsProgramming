#include "Object.h"



Object::Object()
{
}


Object::~Object()
{
	for (auto child : childObjects) { // delete children
		delete child;
	}
}

bool Object::initialise(ObjectInfo myInfo, ModelManager & modelManager, LightManager * lightManager, map<ObjectChildrenEnum, vector<ObjectInfo>> * objectInfos , int parentDepth )
{
	info = myInfo;
	transform = (Transform)myInfo; // upcast to transform
	alpha = myInfo.alpha; // quick acess for alpha (used to test if object should be drawn at transparency rendering step)
	model = modelManager.getModel(myInfo.modelName); // assigning pointer to loaded model

	bool transparent = (alpha < 1.f); // transparent objects must be drawn last for them to both depth sort and alpha blend correctly

	// initialising child objects, if not reached maximum recursion depth (and null pointer check just to be safe)
	if (parentDepth < MAX_CHILD_DEPTH && objectInfos!= nullptr) {
		for (auto childObjInfo : objectInfos->at(myInfo.childrenEnum)) { // for each objectInfo at the index of our children
			Object * child = new Object(); // create a new object
			transparent |= child->initialise(childObjInfo, modelManager, lightManager, objectInfos,  parentDepth+1); // recursively initilase it
			child->depthOfParents++;
			childObjects.push_back(child); // store object
		}
	}
	isOrContainsTransparentObject = transparent; // transparent object must be drawn last
	return transparent;

}

void Object::update(float dt)
{
	// virtual function
}

void Object::update(float dt, Vector3 spaceshipPos)
{
	// virtual function
}



void Object::render()
{
	glPushMatrix(); // apply parent transform
		glTranslatef(transform.position.x, transform.position.y, transform.position.z);
		glRotatef(transform.rotationScalar, transform.rotationVector.x, transform.rotationVector.y, transform.rotationVector.z);
		glScalef(transform.scale.x,transform.scale.y,transform.scale.z);
		model->render(alpha); // render model
		for (auto child : childObjects) { // apply child transforms before poping matrix
			child->render(); // recursively apply render to children
		}
	glPopMatrix(); // pop where we are
}

void Object::doLighting() // do lighting fo any lights we might contain
{
	for (auto l : lights) {
		l->doLighting();
	}
	for (auto child : childObjects) { // recursively do this for our children
		child->doLighting();
	}
}

void Object::applyTransformToAllChildren(Transform t) // applies a transform to all children objects
{
	if (depthOfParents > 0) { // dont apply it to prime parent
		transform = t;
	}
	if (childObjects.size() > 0) { 
		for (auto c : childObjects) {
			c->applyTransformToAllChildren(t); // apply it to all children
		}
	}
	
}

void Object::renderShadow() // this is called after shadow matrix transfrom has been applied
{
	glPushMatrix(); // render shadow for transform of parent object
	glTranslatef(transform.position.x, transform.position.y, transform.position.z);
	glRotatef(transform.rotationScalar, transform.rotationVector.x, transform.rotationVector.y, transform.rotationVector.z);
	glScalef(transform.scale.x, transform.scale.y, transform.scale.z);
	model->renderShadow(); // render us as a shadow
	for (auto child : childObjects) { 
		if(child->alpha >0.99f) // dont make shadows for transparent objects
			child->renderShadow(); 
	}
	glPopMatrix();
}

bool Object::initialise(ModelManager& modelManager, LightManager* lightmanager)
{
	// virtual function
	return isOrContainsTransparentObject;
}

void Object::handleInput(Input* input)
{
}

