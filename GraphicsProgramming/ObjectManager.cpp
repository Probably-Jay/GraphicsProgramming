#include "ObjectManager.h"



ObjectManager::ObjectManager()
{
	modelManager.loadModels();
	objects.push_back(&spaceship);
	
	
}


ObjectManager::~ObjectManager()
{
	for (auto obj : objects) {
		delete obj;
	}
}

void ObjectManager::loadObjects(LightManager * _lightManager)
{
	addCows(35);
	addGrass(30);
	addTrees(45);

	lightManager = _lightManager;


	for (auto objInfo : objectInfos.at(ObjectChildrenEnum::parents)) {
		Object* obj;
		if (objInfo.modelName == ModelManager::ModelEnum::cow) {
			obj = new Cow();
		}
		else {
			obj = new Object();
		}
		objects.push_back(obj);
		obj->initialise(objInfo, modelManager, lightManager, &objectInfos); 
	}

	bool objectIsOrContainsTransparentObjects;  // transparent objects must be drawn last for them to both depth sort and alpha blend correctly

	for (auto obj : objects) {
		objectIsOrContainsTransparentObjects = obj->initialise(modelManager, lightManager); // this is an virtual overloaded function
		if (objectIsOrContainsTransparentObjects) {
			transparentObjects.push_back(obj);
		}
		else {
			opaqueObjects.push_back(obj);
		}
	}

	
}

void ObjectManager::handleInput(Input* input)
{
	for (auto obj : objects) {
		obj->handleInput(input);
	}
}

void ObjectManager::updateObjects(float dt)
{
	
	float t = (glutGet(GLUT_ELAPSED_TIME) / 1000.f);
	for (auto obj : objects) {
		if (obj->info.modelName == ModelManager::ModelEnum::grass) {
			ObjectInfo childInfo = obj->childObjects[0]->info;
			obj->applyTransformToAllChildren(Transform(childInfo.position, childInfo.scale, 10 * sin(t + obj->info.randomSeed), Vector3(cos(obj->info.randomSeed), 0, 2 * sin(obj->info.randomSeed))));
		}
		else if (obj->info.modelName == ModelManager::ModelEnum::cow) {
			obj->update(dt, spaceship.transform.position);

		}
		else {
			obj->update(dt);

		}
		
	}
	
	

	


}

void ObjectManager::renderObjects()
{
	
	for (auto obj : opaqueObjects) {
		obj->render();
	}
	for (auto obj : transparentObjects) {
		obj->render();
	}
}

void ObjectManager::doLighting()
{
	lightManager->doGlobalLighting();
	for (auto obj : objects) {
		obj->doLighting();
	}
}
 
void ObjectManager::doSunShadows()
{
	float* shadowMatrix = lightManager->getSunShadow();
	glPushMatrix();
	glMultMatrixf((GLfloat*)shadowMatrix);
	for (auto obj : opaqueObjects) {
		obj->renderShadow();
	}
	glPopMatrix();
							
}

void ObjectManager::moveSpaceship(Vector3 vec, bool addToCurrentPosition )
{
	if (addToCurrentPosition) {
		spaceship.transform.position += vec ;
	}
	else {
		spaceship.transform.position = vec;
	}
}

void ObjectManager::deleteObjectMarkedForDeletion()
{
	vector<Object*> toDel;
	opaqueObjects.erase( // removes from array from given iterators
		std::remove_if( // returns iterator of item(s) to be removed based on condition
			opaqueObjects.begin(), // from the beggining of the array
			opaqueObjects.end(),	// to the end
			[&](Object* obj) { // lambda function condition
				return obj->markedForDeletion;// if the object is marked for deletion
			}),
	opaqueObjects.end() // from returned itterator to the end of the array
	);

	objects.erase( // removes from array from given iterators
		std::remove_if( // returns iterator of item(s) to be removed based on condition
			objects.begin(), // from the beggining of the array
			objects.end(),	// to the end
			[&](Object* obj) { // lambda function condition
				if (obj->markedForDeletion) { // kep track of object so we can delete it
					toDel.push_back(obj);
				}
				return obj->markedForDeletion;// if the object is marked for deletion
			}),
		objects.end() // from returned itterator to the end of the array
		);

	for (auto obj : toDel) { // delete objects
		delete obj;
	}
	toDel.clear();
}





void ObjectManager::addCows(int numberOfCows)
{
	srand(time(NULL));
	for (int i = 0; i < numberOfCows; i++) {
		float xpos = -MAP_SIZE + fmod(rand(), 2.f * MAP_SIZE); 
		float zpos = -MAP_SIZE + fmod(rand(), 2.f * MAP_SIZE); 
		//xpos = 0; 
		//zpos = 0;
		objectInfos[ObjectChildrenEnum::parents].push_back(ObjectInfo(ModelManager::ModelEnum::cow, Transform(Vector3(xpos, -10, zpos), Vector3(0.05, 0.05, 0.05), rand() % 360, Vector3(0, 1, 0)), Vector3(1, 1, 1), 1, ObjectChildrenEnum::none, rand()));

	}
}

void ObjectManager::addGrass(int grass)
{
	srand(time(NULL)+1);
	for (int i = 0; i < grass; i++) {
		float xpos = -MAP_SIZE + fmod(rand(), 2.f * MAP_SIZE);
		float zpos = -MAP_SIZE + fmod(rand(), 2.f * MAP_SIZE);
		objectInfos[ObjectChildrenEnum::parents].push_back(ObjectInfo(ModelManager::ModelEnum::grass, Transform(Vector3(xpos, -10, zpos), Vector3(0.08, 0.08,0.08), rand() % 360, Vector3(0, 1, 0)),Vector3(1,1,1),1,ObjectChildrenEnum::grassKids,rand()));

	}
}

void ObjectManager::addTrees(int trees)
{
	srand(time(NULL) + 1);
	for (int i = 0; i < trees; i++) {
		float xpos = -MAP_SIZE + fmod(rand(), 2.f * MAP_SIZE);
		float zpos = -MAP_SIZE + fmod(rand(), 2.f * MAP_SIZE);
		objectInfos[ObjectChildrenEnum::parents].push_back(ObjectInfo(ModelManager::ModelEnum::tree, Transform(Vector3(xpos, -10, zpos), Vector3(1, 1, 1), rand() % 360, Vector3(0, 1, 0))));

	}
}
