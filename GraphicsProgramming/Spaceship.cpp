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
	
	transform = (Transform)info; // upcast to transform
	alpha = info.alpha; // quick acess for alpha (used to test if object should be drawn at transparency rendering step)
	model = modelManager.getModel(info.modelName); // assigning pointer to loaded model

	return isTransparent;
}

void Spaceship::update(float dt)
{
	beam.transform.scale = Vector3(1, (20.f+transform.position.y)/10.f, 1);
	lightBeam->updatePosition(transform.position);
	halo.update(dt, transform.position);
	Object::update(dt);
}



void Spaceship::doLighting()
{

	lightBeam->doLighting();
	Object::doLighting();
}
