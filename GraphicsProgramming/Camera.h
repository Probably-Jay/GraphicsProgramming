#pragma once
#include "Vector3.h"
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
#include "Globals.h"
#include "SOIL.h"

#include"Model.h"
#include"ModelManager.h"

#include "Spaceship.h"


using namespace std;
class Camera
{
public:
	Camera();
	~Camera();

	Vector3 getPosition() { return position; };
	Vector3 getRotation() { return rotation; };
	Vector3 getLookAt() { return lookAt; };
	Vector3 getUpDirection() { return upDirection; };
	Vector3 getForwardDirection() { return forwardDirection; };

	void updateLookAt();

	void handleInput(Input * input, float windowWidth, float windowHeight, float dt);
	void update( float dt);
	void loadSkybox(ModelManager & modelManager);
	void passSpaceship(Spaceship & s) { spaceship = &s; };
	void drawSkybox();

	bool isFollowingSpaceship() { return followSpaceship; };

private:

	void boundPosition();

	Vector3 position;
	Vector3 lookAt;

	Vector3 upDirection;
	Vector3 forwardDirection;
	Vector3 rightDirection;

	Vector3 direction;
	Vector3 rotation;

	int xMouseDelta;
	int yMouseDelta;

	float speed;
	float walkingSpeed = 20;
	float runningSpeed = 40;
	float ylookSpeed = 15;
	float xlookSpeed = 5;
	bool running;

	enum Keys // make input handling more readable
	{
		forward = 119,
		backwards = 115,
		left = 97,
		right = 100,
		up = 101,
		down = 113,
		run = 92,
		free = 118,
		follow = 99,
	};

	bool initialResetLook = true;

	GLuint skyTexture;

	bool followSpaceship = true;

	Spaceship * spaceship;

	Model * skybox;


};

