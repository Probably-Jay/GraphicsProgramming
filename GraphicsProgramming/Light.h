#pragma once
#include "Vector3.h"
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <stdio.h>


class Light
{
	friend class LightManager;
public:
	Light();
	~Light();

	void updatePosition(Vector3 position);

	void doLighting();
		
private:

	enum LightType
	{
		point,
		directional,
		spot,

	};

	void initialise(LightType type, GLint GLlight, Vector3 position, Vector3 diffuse = Vector3(), float _intensityExponent =1, Vector3 direction = Vector3(), Vector3 ambient = Vector3(), float spotAngle = 30);

	
	GLint GLlight;

	LightType type;



	Vector3 position;
	Vector3 directionVector;

	//void setUpPointLight();
	//void setUpDirectionalLight();
	//void setUpSpotLight();
	//  

	GLfloat ambient[4];
	GLfloat direction[3] ;
							 
	GLfloat lightPosition[4];
	GLfloat diffuse[4];

	float intensity;
	float spotAngle;
							 
	 

};

