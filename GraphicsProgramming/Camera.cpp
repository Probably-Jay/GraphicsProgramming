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

	

	// from lecture slides, parametric formula of sphere
	float cosR, cosP, cosY;
	float sinR, sinP, sinY;
	cosY= cosf(rotation.y*3.1415/180.f);
	cosP= cosf(rotation.x*3.1415/180.f);
	cosR= 1;						
	sinY= sinf(rotation.y*3.1415/180.f);
	sinP= sinf(rotation.x*3.1415/180.f);
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

	direction = Vector3(0.f, 0.f, 0.f);
	
	running = input->isKeyDown(run);
	
	// movement
	if (input->isKeyDown(forward)) {
		direction.z += 1.f; 
	}if (input->isKeyDown(backwards)) {
		direction.z -= 1.f; 
	}if (input->isKeyDown(right)) {
		direction.x += 1.f; 
	}if (input->isKeyDown(left)) {
		direction.x -= 1.f; 
	}if (input->isKeyDown(up)) {
		direction.y += 1.f; 
	}if (input->isKeyDown(down)) {
		direction.y -= 1.f;
	}
	direction.normalise();

	//mouse look
	xMouseDelta = input->getMouseX() - windowWidth / 2.f;
	yMouseDelta = input->getMouseY() - windowHeight / 2.f;
	input->setMousePos(windowWidth / 2.f, windowHeight / 2.f);

	if (input->isKeyDown(follow)) {
		position.y = 0;
		followSpaceship = true;
		
	}if (input->isKeyDown(free)) {
		followSpaceship = false;

	}

	

	//if the mouse has moved
	if (abs(xMouseDelta) + abs(yMouseDelta > 1.f)) {
		rotation.y += xMouseDelta*ylookSpeed*dt;
		rotation.x -= yMouseDelta*xlookSpeed*dt;
		
		if (rotation.y > 180.f) {
			rotation.y-= 360.f;
		}if (rotation.y < -180.f) {
			rotation.y += 360.f;
		}
		if (followSpaceship) {
			if (rotation.x < -20.f) {
				rotation.x = -20.f;
			}if (rotation.x > 30.f) {
				rotation.x = 30.f;
			}
		}
		else {

			if (rotation.x < -80.f) {
				rotation.x = -80.f;
			}if (rotation.x > 80.f) {
				rotation.x = 80.f;
			}
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
		speed = running ? runningSpeed : walkingSpeed;
		Vector3 toMove = Vector3();
		toMove.y += direction.y*speed*dt; // up is always world alligned
		toMove += forwardDirection.multiply(direction.z*speed*dt); // forward component, split because up is different alligend to forward/right 
		toMove += rightDirection.multiply(direction.x*speed*dt);  // right component
		if (followSpaceship)
			toMove.y = 0;
		position += toMove;
		if (followSpaceship)
			 
			boundPosition();
		updateLookAt();
	}
}

void Camera::loadSkybox(ModelManager& modelManager)
{
	
	skybox = modelManager.getModel(ModelManager::ModelEnum::skybox);

	
}


void Camera::drawSkybox() {
	//disable the depth test to draw skybox
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
		glColor4f(1, 1, 1, 1);
		glTranslatef(position.x, position.y, position.z);
		skybox->render(1,false); // render skybox with no transparency or lighting
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void Camera::boundPosition()
{
	// dont let the spaceship leave the map
	if (position.x < -1.2*MAP_SIZE) {
		position.x = -1.2 * MAP_SIZE;
	}if (position.x > 1.2 * MAP_SIZE) {
		position.x = 1.2 * MAP_SIZE;
	}
	
	if (position.z < -1.2 * MAP_SIZE) {
		position.z = -1.2 * MAP_SIZE;
	}if (position.z > 1.2 * MAP_SIZE) {
		position.z = 1.2 * MAP_SIZE;
	}
}

