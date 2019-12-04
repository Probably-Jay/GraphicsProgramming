#pragma once

#include "Object.h"
#include <vector>
#include <array>
#include <map>
#include "Transform.h"
#include "ModelManager.h"


class Object;
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void loadObjects();

	void addObject(Object*obj) { objects.push_back(obj); };

	void drawObjects();

	vector<Object *> objects;
	
private:

	ModelManager modelManager;

	map<ObjectChildrenEnum, vector<ObjectInfo>> objectInfos = {

		{
			parents , { // objects that are not the children of any other objects - no not necessarily have any children of their own
				//ObjectInfo(Transform(Vector3(0,0,0)),ModelManager::ModelEnum::teapot,teapotKids),
				//ObjectInfo(Transform(Vector3(0,0,0)),ModelManager::ModelEnum::cow,none),
				//ObjectInfo(Transform(Vector3(0,20,-30)),ModelManager::ModelEnum::ufo,none),
				ObjectInfo(Transform(Vector3(0,0,0)),ModelManager::ModelEnum::garfield,none),
				
			}
		},
		{
			teapotKids , { // children of the teapot
				ObjectInfo(Transform(Vector3(10,0,0),Vector3(0.8,0.8,0.8),20.f),ModelManager::ModelEnum::teapot,teapotKids),

				
			}
		},
		{
			none , {}
		}
	};
	





	vector<Object *> transparentObjects;

};

