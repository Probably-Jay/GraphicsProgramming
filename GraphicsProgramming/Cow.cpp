#include "Cow.h"


void Cow::handleInput(Input* input)
{
	if (input->isKeyDown(32)) { // abduct cow
		spaceKeyPressed = true;
	}
	else {
		spaceKeyPressed = false;
	}
}

void Cow::update(float dt, Vector3 spacePos)
{
	if (spaceKeyPressed) { // if the abduct key is pressed and we are close enough to a cow
		if (Vector3(transform.position.x - spacePos.x, 0, transform.position.z - spacePos.z).lengthSquared() <4) { // length squared for efficiency
			beingSucked = true;
		}
	}
	if (beingSucked) { // fly into spaceship
		Vector3 meToTarget = (spacePos - transform.position);
		transform.position.x = spacePos.x; // lock x and z
		transform.position.z = spacePos.z;
		transform.position.y += meToTarget.multiply(dt).y; // slowly fly to ufo
		transform.scale -= transform.scale.multiply(0.7*dt); /// get smaller
		if (transform.position.y > spacePos.y) { // dont go through the top of spaceship (if ufo moves down)
			transform.position.y = spacePos.y;
		}
		transform.rotationVector = Vector3(info.randomSeed+GLUT_ELAPSED_TIME, info.randomSeed- GLUT_ELAPSED_TIME, info.randomSeed+GLUT_ELAPSED_TIME/2).normalised();
		transform.rotationScalar += 120.0*dt;
		if (transform.scale.containsValueLessThan(0.01f)) { // delete object when its fully sucked in
			markedForDeletion = true;
		}
	}
	Object::update(dt);
}
