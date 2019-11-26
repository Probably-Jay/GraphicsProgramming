#pragma once
#include "Vector3.h"
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
class Camera
{
public:
	Camera();
	~Camera();

	Vector3 getPosition() { return position; };
	Vector3 getRotation() { return rotation; };
	Vector3 getLookAt() { return lookAt; };
	Vector3 getUpDirection() { return upDirection; };

	void updateLookAt();

	void handleInput(Input * input, float windowWidth, float windowHeight, float dt);
	void update( float dt);
	void drawSkybox();

private:

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
	float lookSpeed = 100;
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
	};

	bool initialResetLook = true;

};

