#include "LightManager.h"

LightManager::LightManager()
{
}

LightManager::~LightManager()
{
}

void LightManager::initialise(Vector3 floorNormal, Vector3 floorPoint)
{
	lights = {};

	GLlights.push_back(GL_LIGHT0);
	GLlights.push_back(GL_LIGHT1);
	GLlights.push_back(GL_LIGHT2);
	GLlights.push_back(GL_LIGHT3);
	GLlights.push_back(GL_LIGHT4);
	GLlights.push_back(GL_LIGHT5);
	GLlights.push_back(GL_LIGHT6);
	GLlights.push_back(GL_LIGHT7);


	sun = newDirectionalLight(Vector3(0, tan(0.523599), 1).normalised() , Vector3(0, 0, 1), Vector3(0.2, 0.2, 0.4),0.5, 0.05);
	sunShadow.initialiseShadow(floorNormal, floorPoint);
	

}

Light* LightManager::newPointLight(Vector3 position, Vector3 diffuse, float intensity)
{
	if (lights.size() < 8) {
		Light* l = new Light();
		l->initialise(Light::LightType::point, GLlights[lights.size()], position, diffuse, intensity);
		lights.push_back(l);
		return l;
	}
	else {
		return nullptr;
	}
}

Light* LightManager::newDirectionalLight(Vector3 direction, Vector3 diffuse, Vector3 ambient, float intensity, float ambiendIntensity)
{
	if (lights.size() < 8) {
		Light* l = new Light();
		l->initialise(Light::LightType::directional, GLlights[lights.size()], direction, diffuse, intensity, Vector3(),ambient,0.f);
		lights.push_back(l);
		return l;
	}
	else {
		return nullptr;
	}
}

Light* LightManager::newSpotLight(Vector3 position, Vector3 diffuse, Vector3 direction, float intensity, float angle)
{
	if (lights.size() < 8) {
		Light * l = new Light();
		l->initialise(Light::LightType::spot, GLlights[lights.size()], position,diffuse,intensity,direction,Vector3(),angle);
		lights.push_back(l);
		return l;
	}
	else {
		return nullptr;
	}

}

float* LightManager::getSunShadow()
{
	return sunShadow.getShadowMatrix(Vector3(),sun->directionVector);
}

void LightManager::doAllLighting()
{
	glEnable(GL_LIGHTING);
	for (int i = 0; i < lights.size(); i ++) {
		Light* light = lights[i];

		glLightfv(GLlights[i], GL_POSITION, light->lightPosition);
		glLightfv(GLlights[i], GL_DIFFUSE, light->diffuse);

		switch (light->type)
		{
		case Light::point:
			break;
		case Light::directional:
			glLightfv(GLlights[i], GL_AMBIENT, light->ambient);
			break;
		case Light::spot:
			glLightfv(GLlights[i], GL_SPOT_DIRECTION, light->direction);
			glLightf(GLlights[i], GL_SPOT_CUTOFF,  light->spotAngle);
			glLightf(GLlights[i], GL_SPOT_EXPONENT, light->intensity);
			break;
		default:
			break;
		}
		glEnable(GLlights[i]);
	}
}

void LightManager::doSpecificLighting(Light* light)
{
	glEnable(GL_LIGHTING);
	
	glLightfv(light->GLlight, GL_POSITION, light->lightPosition);
	glLightfv(light->GLlight, GL_DIFFUSE, light->diffuse);

	switch (light->type)
	{
	case Light::point:
		break;
	case Light::directional:
		glLightfv(light->GLlight, GL_AMBIENT, light->ambient);
		break;
	case Light::spot:
		glLightfv(light->GLlight, GL_SPOT_DIRECTION, light->direction);
		glLightf(light->GLlight, GL_SPOT_CUTOFF, light->spotAngle);
		glLightf(light->GLlight, GL_SPOT_EXPONENT, light->intensity);
		break;
	default:
		break;
	}
	glEnable(light->GLlight);
}

void LightManager::doGlobalLighting()
{
	sun->doLighting();
}

