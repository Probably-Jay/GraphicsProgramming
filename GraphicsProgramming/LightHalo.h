#pragma once
#include "Object.h"
#include "ObjectInfo.h"
#include "Light.h"
class LightHalo :
	public Object
{
public:
	Light* light;
	ObjectInfo info = ObjectInfo(ModelManager::ModelEnum::ball, Transform(Vector3(),Vector3(0.2,0.2,0.2)), Vector3(1, 0, 0), 0.4f);
	bool initialise(ObjectInfo myinfo, ModelManager& modelManager, LightManager* lightManager);
	void update(float dt, Vector3 position);
	//void render();
private:
	void updateLightPosition(Vector3 position);
	float time = 0;
	//void renderModel();
};

