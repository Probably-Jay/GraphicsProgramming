#include "Spaceship.h"

Spaceship::Spaceship() {
	childObjects.push_back(&beam);
	
}


Spaceship::~Spaceship() {


}

void Spaceship::initialise(ModelManager& modelManager,LightManager * lightManager) 
{
	this->lightManager = lightManager;
	Object::initialise(myInfo, modelManager,lightManager);
	beam.initialise(beamInfo, modelManager,lightManager);

	light = this->lightManager->newSpotLight(Vector3(0, 0, 0), Vector3(0, 1, 0), 50, 30);

	 
}

void Spaceship::spaceshipUpdate(float dt)
{
	light->updatePosition(transform.position);
}

void Spaceship::render()
{

}
