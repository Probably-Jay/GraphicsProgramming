#pragma once
#include "Model.h"
#include "Vector3.h"
#include "ObjectInfo.h"
class Object
{
public:
	Object();
	~Object();

	
	bool initialise(ObjectInfo myInfo, map<ObjectChildrenEnum, vector<ObjectInfo>> * objectInfos);
	void render();

private:
	Vector3 positon;
	Model model;

	vector<Object*> childObjects;

};

