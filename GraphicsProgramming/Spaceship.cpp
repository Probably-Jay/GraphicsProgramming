#include "Spaceship.h"

Spaceship::Spaceship() {
	childObjects.push_back(&beam);
	
}


Spaceship::~Spaceship() {


}

bool Spaceship::initialise(ModelManager& modelManager,LightManager * lightManager) 
{
	bool isTransparent = false;

	this->lightManager = lightManager;
	isTransparent |= beam.initialise(beamInfo, modelManager,lightManager);

	lightBeam = this->lightManager->newSpotLight(Vector3(0, 0, 0), Vector3(0, 1, 0), 5, 30);
	lights.push_back(lightBeam);

	isTransparent |= halo.initialise(halo.info, modelManager, lightManager);
	lights.push_back(halo.light);
	childObjects.push_back(&halo);
	//transform.rotationVector()
	return Object::initialise(info, modelManager,lightManager) || isTransparent;
}

void Spaceship::update(float dt)
{
	
	lightBeam->updatePosition(transform.position);
	halo.update(dt, transform.position);
	Object::update(dt);
	//halo.updateLightPosition(transform.position + Vector3(0,0,0));
}



void Spaceship::doLighting()
{

	lightBeam->doLighting();
	//halo.doLighting();
	Object::doLighting();
}
