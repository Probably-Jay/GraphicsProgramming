#pragma once
#include "Object.h"

#include "Model.h"

#include "LightHalo.h"
#include <vector>

class Spaceship :
	public Object
{
public:
	Spaceship();
	~Spaceship();

	
	//void initialise(ModelManager& modelManager, LightManager* lightmanager);
	bool initialise( ModelManager& modelManager,LightManager * lightManager);
	void update(float dt);
	void doLighting();
	 
private:

	

	LightManager* lightManager = nullptr;

	ObjectInfo info = ObjectInfo(ModelManager::ModelEnum::ufo);

	ObjectInfo beamInfo = ObjectInfo(ModelManager::ModelEnum::beam,Transform(Vector3(0,0,0),Vector3(1,2,1)),Vector3(1,1,1),0.3f);
	Object beam;
	Light * lightBeam;
	LightHalo halo;



};

