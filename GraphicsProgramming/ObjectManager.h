#pragma once


#include "Globals.h"
#include "Object.h"
#include <vector>
#include <ctime>
#include <array>
#include <map>
#include "Transform.h"
#include "ModelManager.h"
#include "Spaceship.h"
#include "LightManager.h"
#include "Cow.h"
#include "SimpleObject.h"


class Object;
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void initialiseObjects(LightManager * lightManager);
	void handleInput(Input* input);
	void updateObjects(float dt);

	void addObject(Object*obj) { objects.push_back(obj); };

	void renderObjects();
	void renderReflections(SimpleObjectManager& simpleObjectManager);
	void doLighting();
	void doSunShadows(SimpleObjectManager& simpleObjectManager);

	vector<Object *> objects;

	void moveSpaceship(Vector3 direction);

	ModelManager& getModelManager() { return modelManager; };

	
private:

	void deleteObjectMarkedForDeletion();

	
	void addCows(int cows);
	void addGrass(int grass);
	void addTrees(int trees);

	

	ModelManager modelManager;
	LightManager * lightManager;

	map<ObjectChildrenEnum, vector<ObjectInfo>> objectInfos = {

		{
			parents , { // top level objects
				// filled by addCows, addGrass, addTrees functions
			}
		},
		{
			grassKids, { // children of grass
				// this object has itself as its child, allowing for recursive children and fractal-like animations
 				ObjectInfo(ModelManager::ModelEnum::grass,Transform(Vector3(0,0.8,0),Vector3(0.85,0.9,0.85)),Vector3(1,1,1),1,grassKids),
			}
		},

		{
			none , {}
		}
	};
	

	Spaceship spaceship;


	vector<Object *> opaqueObjects;
	vector<Object *> transparentObjects;

};

