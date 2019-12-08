#pragma once
#include "Model.h"
#include "Vector3.h"
#include "ObjectInfo.h"
#include "Transform.h"
#include "ModelManager.h"
#include "LightManager.h"
#include "Input.h"

#define MAX_CHILD_DEPTH 20

class Object
{
	friend class ObjectManager;
public:
	Object();
	~Object();

	
	virtual bool initialise(ObjectInfo myInfo, ModelManager& modelManager, LightManager * lightmanager, map<ObjectChildrenEnum, vector<ObjectInfo>> * objectInfos = nullptr, int parentDepth= 0);
	virtual bool initialise(ModelManager& modelManager, LightManager * lightmanager);
	virtual void handleInput(Input* input);
	virtual void update(float dt);
	virtual void update(float dt, Vector3 spaceshipPos);
	virtual void render();
	virtual void doLighting();
	

	Transform transform;

	void applyTransformToAllChildren(Transform t);


	Vector3 colour;
	float alpha;

	bool markedForDeletion = false;
protected:

	bool isOrContainsTransparentObject;
	void renderShadow();


	//Vector3 positon;
	Model * model = nullptr;

	//void renderJustMe();

	int depthOfParents = 0;
	vector<Object*> childObjects;
	vector<Light*> lights;

	ObjectInfo info;

};

