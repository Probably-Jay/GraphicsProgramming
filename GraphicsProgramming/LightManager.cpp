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
	// the gl lights, each Light object is assigned one of these
	GLlights.push_back(GL_LIGHT0);
	GLlights.push_back(GL_LIGHT1);
	GLlights.push_back(GL_LIGHT2);
	GLlights.push_back(GL_LIGHT3);
	GLlights.push_back(GL_LIGHT4);
	GLlights.push_back(GL_LIGHT5);
	GLlights.push_back(GL_LIGHT6);
	GLlights.push_back(GL_LIGHT7);

	// main directional light of the scene
	sun = newDirectionalLight(Vector3(0, 0.5f, 1.f).normalised() , Vector3(0, 0, 1), Vector3(0.2, 0.2, 0.4), 0.5, 0.05);
	sunShadow.initialiseShadow(floorNormal, floorPoint); // set up information used to generate shadow transformation matrix
	

}

Light* LightManager::newPointLight(Vector3 position, Vector3 diffuse, float intensity)
{
	if (lights.size() < 8) { // there are only 8 lights available in our scene
		Light* l = new Light();
		l->initialise(Light::LightType::point, GLlights[lights.size()], position, diffuse, intensity); // intialise the light
		lights.push_back(l);
		return l;
	}
	else {
		return nullptr;
	}
}

Light* LightManager::newDirectionalLight(Vector3 direction, Vector3 diffuse, Vector3 ambient, float intensity, float ambiendIntensity)
{
	if (lights.size() < 8) { // there are only 8 lights available in our scene
		Light* l = new Light();
		l->initialise(Light::LightType::directional, GLlights[lights.size()], direction, diffuse, intensity, Vector3(),ambient,0.f); // intialise the light
		lights.push_back(l);
		return l;
	}
	else {
		return nullptr;
	}
}

Light* LightManager::newSpotLight(Vector3 position, Vector3 diffuse, Vector3 direction, float intensity, float angle)
{
	if (lights.size() < 8) { // there are only 8 lights available in our scene
		Light * l = new Light();
		l->initialise(Light::LightType::spot, GLlights[lights.size()], position,diffuse,intensity,direction,Vector3(),angle); // intialise the light
		lights.push_back(l);
		return l;
	}
	else {
		return nullptr;
	}

}

float* LightManager::getSunShadow() // return the shadow matrix
{
	return sunShadow.getShadowMatrix(Vector3(),sun->directionVector);
}

void LightManager::doGlobalLighting() // apply lighting 
{
	sun->doLighting(); // main directional lighting
}

