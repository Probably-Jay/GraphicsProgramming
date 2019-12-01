#pragma once

#include "Object.h"
#include <vector>
#include <array>
#include <map>
#include "ObjectInfo.h"


class Object;
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	bool loadObjects();

	void addObject(Object*obj) { objects.push_back(obj); };

	void drawObjects();

	
private:

	map<ObjectChildrenEnum, vector<ObjectInfo>> objectInfos = {

		{
			parents , { // objects that are not the children of any other objects - no not necessarily have any children of their own
				ObjectInfo("models/teapot.obj", "gfx/checked.png", Vector3(0,-20,0),teapotKids),
				
			}
		},
		{
			teapotKids , { // children of the teapot
				ObjectInfo("models/teapot.obj", "gfx/checked.png", Vector3(0,-40,0),teapotKids),
				
			}
		},
		{
			none , {}
		}
	};
	





	vector<Object *> objects;
	vector<Object *> transparentObjects;

};

