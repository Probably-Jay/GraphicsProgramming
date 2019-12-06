#pragma once

#include "Object.h"
#include <vector>
#include <array>
#include <map>
#include "Transform.h"
#include "ModelManager.h"
#include "Spaceship.h"
#include "LightManager.h"

class Object;
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void loadObjects(LightManager * lightManager);
	void updateObjects(float dt);

	void addObject(Object*obj) { objects.push_back(obj); };

	void drawObjects();

	vector<Object *> objects;

	void moveSpaceship(Vector3 direction, bool addToCurrentPosition = true);

	
private:


	ModelManager modelManager;
	LightManager * lightManager;

	map<ObjectChildrenEnum, vector<ObjectInfo>> objectInfos = {

		{
			parents , { // objects that are not the children of any other objects - no not necessarily have any children of their own
				//ObjectInfo(ModelManager::ModelEnum::teapot,Transform(Vector3(10,0,0)),teapotKids),
				//ObjectInfo(ModelManager::ModelEnum::cow, Transform(Vector3(0,0,0),Vector3(0.2,0.2,0.2))),
				
				
				//ObjectInfo(Transform(Vector3(0,20,-30)),ModelManager::ModelEnum::ufo,none),
				//ObjectInfo(ModelManager::ModelEnum::garfield),
				
			}
		},
		{
			teapotKids , { // children of the teapot
				ObjectInfo(ModelManager::ModelEnum::teapot,Transform(Vector3(10,0,0),Vector3(0.8,0.8,0.8),20.f),teapotKids),

				
			}
		},
		{
			none , {}
		}
	};
	

	Spaceship spaceship;


	vector<Object *> transparentObjects;

};

