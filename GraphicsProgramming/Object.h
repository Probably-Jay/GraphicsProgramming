#pragma once
#include "Model.h"
#include "Vector3.h"
#include "ObjectInfo.h"
#include "Transform.h"
#include "ModelManager.h"
class Object
{
public:
	Object();
	~Object();

	
	void initialise(ObjectInfo myInfo, ModelManager& modelManager, map<ObjectChildrenEnum, vector<ObjectInfo>> * objectInfos, int parentDepth= 0);
	void render();

	Transform transform;

	void applyTransformToAllChildren(Transform t);

	


private:
	//Vector3 positon;
	Model * model = nullptr;

	

	int depthOfParents = 0;
	vector<Object*> childObjects;


};

