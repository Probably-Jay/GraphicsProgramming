#pragma once
#include "Object.h"

#include "Model.h"
#include <vector>

class Spaceship :
	public Object
{
public:
	Spaceship();
	~Spaceship();

	

	void initialise(ModelManager& modelManager,LightManager * lightManager);
	void spaceshipUpdate(float dt);
	void render();

private:

	LightManager* lightManager = nullptr;

	ObjectInfo myInfo = ObjectInfo(ModelManager::ModelEnum::ufo);

	ObjectInfo beamInfo = ObjectInfo(ModelManager::ModelEnum::beam,Transform(Vector3(0,-10,0),Vector3(1,2,1)),0.5f);
	Object beam;
	Light* light;



};

