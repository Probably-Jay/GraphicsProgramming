#pragma once
#include "Model.h"
#include "Vector3.h"
#include "ObjectInfo.h"
#include "Transform.h"
#include "ModelManager.h"
#include "LightManager.h"

#define MAX_CHILD_DEPTH 20

class Object
{
public:
	Object();
	~Object();

	
	void initialise(ObjectInfo myInfo, ModelManager& modelManager, LightManager * lightmanager, map<ObjectChildrenEnum, vector<ObjectInfo>> * objectInfos = nullptr, int parentDepth= 0);
	void update(float dt);
	virtual void spaceshipUpdate(float dt);
	void render();

	Transform transform;

	void applyTransformToAllChildren(Transform t);

	virtual void initialise(ModelManager& modelManager, LightManager * lightmanager);

	
	float alpha;

protected:
	//Vector3 positon;
	Model * model = nullptr;

	//void renderJustMe();

	int depthOfParents = 0;
	vector<Object*> childObjects;



};

