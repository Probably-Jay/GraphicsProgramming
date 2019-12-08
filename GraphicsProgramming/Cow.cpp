#include "Cow.h"

//bool Cow::initialise(ObjectInfo myInfo, ModelManager& modelManager, LightManager* lightmanager, map<ObjectChildrenEnum, vector<ObjectInfo>>* objectInfos, int parentDepth)
//{
//	initialPos = myInfo.position;
//	return Object::initialise(myInfo, modelManager, lightmanager,  objectInfos, parentDepth);
//}

void Cow::handleInput(Input* input)
{
	if (input->isKeyDown(32)) {
		spaceKeyPressed = true;
	}
	else {
		spaceKeyPressed = false;
	}
}

void Cow::update(float dt, Vector3 spacePos)
{
	if (spaceKeyPressed) {
		if (Vector3(transform.position.x - spacePos.x, 0, transform.position.z - spacePos.z).lengthSquared() <4) {
			beingSucked = true;
		}
	}
	if (beingSucked) {
		Vector3 meToTarget = (spacePos - transform.position);
		Vector3 initialToTarget = (spacePos - initialPos);
		transform.position.x = spacePos.x;
		transform.position.z = spacePos.z;
		transform.position.y += meToTarget.multiply(dt).y;
		transform.scale -= transform.scale.multiply(0.7*dt);
		if (transform.position.y > spacePos.y) {
			transform.position.y = spacePos.y;
		}
		transform.rotationVector = Vector3(info.randomSeed+GLUT_ELAPSED_TIME, info.randomSeed- GLUT_ELAPSED_TIME, info.randomSeed+GLUT_ELAPSED_TIME/2).normalised();
		transform.rotationScalar += 120.0*dt;
		if (transform.scale.containsValueLessThan(0.01f)) {
			markedForDeletion = true;
		}
	}
	Object::update(dt);
}
