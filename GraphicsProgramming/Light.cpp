#include "Light.h"



Light::Light()
{
}


Light::~Light()
{
}

void Light::updatePosition(Vector3 _position)
{
	position = _position;
	lightPosition[0] = _position.x;
	lightPosition[1] = _position.y;
	lightPosition[2] = _position.z;

}

void Light::initialise(LightType type, GLint _GLlight, Vector3 _position, Vector3 _diffuse, float _intensityExponent, Vector3 _direction, Vector3 _ambient,  float _spotAngle )
{
	position = _position;
	directionVector = _direction;
	if (type == Light::LightType::directional) {
		directionVector = _position;
	}

	GLlight = _GLlight;
	lightPosition[0] = _position.x;
	lightPosition[1] = _position.y;
	lightPosition[2] = _position.z;

	diffuse[0] = _diffuse.x;
	diffuse[1] = _diffuse.y;
	diffuse[2] = _diffuse.z;
	diffuse[3] = 1;

	switch (type)
	{
	case Light::point:
	{
		lightPosition[3] = 1;

	}
		break;
	case Light::directional:
		{
		lightPosition[3] = 0; // directional lights have 0 in w component
		ambient[0] = _ambient.x; // directinal deals with ambient
		ambient[1] = _ambient.y;
		ambient[2] = _ambient.z;
		ambient[3] = 0;
		}
		break;
	case Light::spot:
		{
		lightPosition[3] = 1; // spot lights have 1 in w component
		direction[0] = _direction.x; // spot has position and direction
		direction[1] = _direction.y;
		direction[2] = _direction.z;
		spotAngle = _spotAngle;
		intensity = _intensityExponent;
		}
		break;
	default:
		break;
	}

}

void Light::doLighting()
{
	glEnable(GL_LIGHTING);

	glLightfv(GLlight, GL_POSITION, lightPosition); // assign light position
	glLightfv(GLlight, GL_DIFFUSE, diffuse); // assign light diffuse colour

	switch (type)
	{
	case Light::point:
		break;
	case Light::directional:
		glLightfv(GLlight, GL_AMBIENT, ambient); // if light is directional assign ambient component
		break;
	case Light::spot:
		glLightfv(GLlight, GL_SPOT_DIRECTION, direction);  // assign direction, angle and intsnsity of direction light
		glLightf(GLlight, GL_SPOT_CUTOFF,spotAngle);
		glLightf(GLlight, GL_SPOT_EXPONENT, intensity);
		break;
	default:
		break;
	}
	glEnable(GLlight); // enable the light
}
