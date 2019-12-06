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

	//if the mouse has moved
	if (abs(xMouseDelta) + abs(yMouseDelta > 1.f)) {
		rotation.y += xMouseDelta*lookSpeed*dt;
		rotation.x -= yMouseDelta*lookSpeed*dt;
		
		if (rotation.y > 180.f) {
			rotation.y-= 360.f;
		}if (rotation.y < -180.f) {
			rotation.y += 360.f;
		}
		if (followSpaceship) {
			if (rotation.x < -25.f) {
				rotation.x = -25.f;
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
		updateLookAt();
	}
}

void Camera::loadSkybox(char * filename)
{
	bool result;


	result = skyTexture = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y 
	);


	if (!result)
	{
		MessageBox(NULL, "Skybox texture failed to load", "Error", MB_OK);
	}
}


void Camera::drawSkybox() {
	glDisable(GL_CULL_FACE);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
	glTranslatef(position.x,position.y,position.z);
	glBindTexture(GL_TEXTURE_2D, skyTexture);
	glBegin(GL_QUADS);
	// Top
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.5f, 0.25f);		  glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.5f, 0.f);		  glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.25f, 0.f);		  glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.25f, 0.25f);		  glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.5f, 0.75f);		glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.25f, 0.75f);		glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.25f, 0.5f);		glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.5f, 0.5f);		glVertex3f(1.0f, -1.0f, -1.0f);

	// Front 
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.75f, 0.25f);		glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.25f);		glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.5f);		glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.75f, 0.5f);		glVertex3f(1.0f, -1.0f, 1.0f);

	// Back
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.5f, 0.5f);  		glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.25f, 0.5f);		glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.25f, 0.25f);		glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.5f, 0.25f); 		glVertex3f(1.0f, 1.0f, -1.0f);



	// Left
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.25f, 0.25f);		glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.f, 0.25f);  		glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.f, 0.5f);   		glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.25f, 0.5f); 		glVertex3f(-1.0f, -1.0f, 1.0f);

	// Right
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.5f, 0.25f);		glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.75f, 0.25f);		glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.75f, 0.5f);		glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.5f, 0.5f);		glVertex3f(1.0f, -1.0f, -1.0f);


	glEnd();
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();
}
