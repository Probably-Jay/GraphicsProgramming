#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <vector>
#include "Vector3.h"

class Shadow
{
public:
	void initialiseShadow(GLfloat floor[12]);
	void initialiseShadow(Vector3 planeNormal, Vector3 point);

	float* getShadowMatrix(Vector3 lightPos, Vector3 lightDirection);

private:
	void generateShadowMatrix(Vector3 lightPos, Vector3 direction, Vector3 planeNormal, Vector3 point);
	float shadowMatrix[16] = {};
	GLfloat floor[12];
	Vector3 floorNormal;
	Vector3 floorPoint;

};

