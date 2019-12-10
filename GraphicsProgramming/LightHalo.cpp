#include "LightHalo.h"
#include "ModelManager.h"
bool LightHalo::initialise(ObjectInfo myinfo, ModelManager& modelManager, LightManager* lightManager)
{
	light = lightManager->newPointLight(myinfo.position, Vector3(1, 0, 0), 1); // create light 
	lights.push_back(light);
	return Object::initialise(myinfo, modelManager, lightManager); // parent functiion complete initialisation
}
void LightHalo::update(float dt, Vector3 pos)
{
	time += 3*dt; // timer for light blinking
	float offset = std::floorf(std::fmod(time, 6.f)); // light rotates around ship at interval
	transform.position = (Vector3(2 * cos(offset), 0.3, 2 * sin(offset))); // parametric equation for a circle
	updateLightPosition(pos + transform.position); // update the positon of the GL light
	Object::update(dt); // call polymorphed original function
}
void LightHalo::updateLightPosition(Vector3 position)
{
	light->updatePosition(position);
}
