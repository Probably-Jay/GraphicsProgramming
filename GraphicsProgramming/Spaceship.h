#pragma once
#include "Object.h"

#include "Model.h"

class Spaceship :
	public Object
{
public:
	Spaceship();
	~Spaceship();

	void initialise(ModelManager& modelManager);

	ObjectInfo info = ObjectInfo(ModelManager::ModelEnum::ufo);

};

