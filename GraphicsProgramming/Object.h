#pragma once
#include "Model.h"
#include "Vector3.h"
#include "ObjectInfo.h"
#include "Transform.h"
class Object
{
public:
	Object();
	~Object();

	
	bool initialise(ObjectInfo myInfo, map<ObjectChildrenEnum, vector<ObjectInfo>> * objectInfos, int parentDepth= 0);
	void render();

	Transform transform;

	void applyTransformToAllChildren(Transform t);

private:
	//Vector3 positon;
	Model model;

	

	int depthOfParents;
	vector<Object*> childObjects;


};

