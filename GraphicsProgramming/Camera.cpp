#include "Camera.h"



Camera::Camera()
{
	position = Vector3(0, 0, 6);
	rotation = Vector3(0, 0, 0);
	updateLookAt();
}


Camera::~Camera()
{
}

void Camera::updateLookAt()
{

	/*if (initialResetLook) {
		initialResetLook = false;
		rotation.x = 0;
		rotation.y = 0;
	}*/

	// from lecture slides, parametric formula of sphere
	float cosR, cosP, cosY;
	float sinR, sinP, sinY;
	cosY= cosf(rotation.y*3.1415/180);
	cosP= cosf(rotation.x*3.1415/180);
	cosR= 1;
	sinY= sinf(rotation.y*3.1415/180);
	sinP= sinf(rotation.x*3.1415/180);
	sinR= 0;

	// calculate local forward direction
	forwardDirection.x = sinY * cosP; 
	forwardDirection.y = sinP; 
	forwardDirection.z = cosP * -cosY;

	lookAt = position + forwardDirection; // look forward

	// calulate local up direction
	upDirection.x = -cosY * sinR - sinY * sinP * cosR;
	upDirection.y = cosP * cosR;
	upDirection.z = -sinY * sinR - sinP * cosR * -cosY;

	//calculate local right direction
	rightDirection = forwardDirection.cross(upDirection);


	
}

void Camera::handleInput(Input *input, float windowWidth, float windowHeight, float dt)
{

	direction = Vector3(0, 0, 0);
	
	// movement
	if (input->isKeyDown(forward)) {
		direction.z += 1; 
	}if (input->isKeyDown(backwards)) {
		direction.z -= 1; 
	}if (input->isKeyDown(right)) {
		direction.x += 1; 
	}if (input->isKeyDown(left)) {
		direction.x -= 1; 
	}if (input->isKeyDown(up)) {
		direction.y += 1; 
	}if (input->isKeyDown(down)) {
		direction.y -= 1;
	}
	direction.normalise();

	//mouse look
	xMouseDelta = input->getMouseX() - windowWidth / 2;
	yMouseDelta = input->getMouseY() - windowHeight / 2;
	input->setMousePos(windowWidth / 2, windowHeight / 2);

	//if the mouse has moved
	if (abs(xMouseDelta) + abs(yMouseDelta > 1)) {
		rotation.y += xMouseDelta*lookSpeed*dt;
		rotation.x -= yMouseDelta*lookSpeed*dt;
		
		if (rotation.y > 180) {
			rotation.y-= 360;
		}if (rotation.y < -180) {
			rotation.y += 360;
		}

		if (rotation.x < -80) {
			rotation.x = -80;
		}if (rotation.x > 80) {
			rotation.x = 80;
		}
		updateLookAt();
	}

	if (initialResetLook) {
		initialResetLook = false;
		rotation.x = 0;
		rotation.y = 0;
	}

}



void Camera::update(float dt)
{
	//if there is input to move
	if (direction.length() > 0.01f); {
		position.y += direction.y*speed*dt; // up is always world alligned
		position += forwardDirection.multiply(direction.z*speed*dt); // forward component, split because up is different alligend to forward/right
		position += rightDirection.multiply(direction.x*speed*dt);  // right component
		updateLookAt();
	}
}
