#pragma once

#include "Object.h"
#include <vector>
#include <array>
#include <map>
#include "Transform.h"


class Object;
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	bool loadObjects();

	void addObject(Object*obj) { objects.push_back(obj); };

	void drawObjects();

	vector<Object *> objects;
	
private:



	map<ObjectChildrenEnum, vector<ObjectInfo>> objectInfos = {

		{
			parents , { // objects that are not the children of any other objects - no not necessarily have any children of their own
				ObjectInfo(Transform(Vector3(0,0,0)),"models/teapot.obj", "gfx/checked.png",teapotKids),
				
			}
		},
		{
			teapotKids , { // children of the teapot
				ObjectInfo(Transform(Vector3(10,0,0),Vector3(0.8,0.8,0.8),20.f),"models/teapot.obj", "gfx/checked.png",teapotKids),

				
			}
		},
		{
			none , {}
		}
	};
	





	vector<Object *> transparentObjects;

};

