#pragma once
#include "Object.h"
#include "Input.h"
class Cow :
	public Object
{
	//bool initialise(ObjectInfo myInfo, ModelManager& modelManager, LightManager* lightmanager, map<ObjectChildrenEnum, vector<ObjectInfo>>* objectInfos = nullptr, int parentDepth = 0);
	void handleInput(Input* input);
	void update(float dt, Vector3 spacePos);


	bool beingSucked = false;
	bool spaceKeyPressed = false;
	Vector3 initialPos;
};

