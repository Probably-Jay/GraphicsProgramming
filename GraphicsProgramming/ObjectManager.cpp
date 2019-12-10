#include "ObjectManager.h"



ObjectManager::ObjectManager()
{
	modelManager.loadModels();
	objects.push_back(&spaceship); // add the spaceship to our objects

}


ObjectManager::~ObjectManager()
{
	for (auto obj : objects) { // clean up
		delete obj;
	}
}

void ObjectManager::initialiseObjects(LightManager * _lightManager)
{
	// add object infos to be initilaised for our repeating objects
	addCows(45);
	addGrass(40);
	addTrees(35);

	lightManager = _lightManager;

	// load objects
	for (auto objInfo : objectInfos.at(ObjectChildrenEnum::parents)) { // for all the object infos in the parent enum index
		Object* obj;
		if (objInfo.modelName == ModelManager::ModelEnum::cow) { // cow is a different object type (inherits from object)
			obj = new Cow();
		}
		else {
			obj = new Object();
		}
		objects.push_back(obj);
		obj->initialise(objInfo, modelManager, lightManager, &objectInfos);  // initialise the objects
	}

	bool objectIsOrContainsTransparentObjects;  // transparent objects must be drawn last for them to both depth sort and alpha blend correctly

	// add objects to arrays for rendereing
	for (auto obj : objects) {
		objectIsOrContainsTransparentObjects = obj->initialise(modelManager, lightManager); // this is an virtual overloaded function
		if (objectIsOrContainsTransparentObjects) {
			transparentObjects.push_back(obj); // adds transparent objct to seperate list that will be drawn after the opaque objects
		}
		else {
			opaqueObjects.push_back(obj);  // rest of the objects
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
	
	float t = (glutGet(GLUT_ELAPSED_TIME) / 1000.f); // get time in ms
	for (auto obj : objects) {
		if (obj->info.modelName == ModelManager::ModelEnum::grass) {  // grass is animated
			ObjectInfo childInfo = obj->childObjects[0]->info; // grab the info for transform and random seed
			obj->applyTransformToAllChildren(Transform(childInfo.position, childInfo.scale, 10 * sin(t + obj->info.randomSeed), Vector3(cos(obj->info.randomSeed), 0, 2 * sin(obj->info.randomSeed)))); // update grass animation
		}
		else if (obj->info.modelName == ModelManager::ModelEnum::cow) { // cows gotta know where the spaceship is
			obj->update(dt, spaceship.transform.position);
		}
		else {
			obj->update(dt); // update rest of the objects
		}
		
	}

}

void ObjectManager::renderObjects()
{
	for (auto obj : opaqueObjects) { // render opaque objects first so they dont get stopped by the depth buffer
		obj->render();
	}
	for (auto obj : transparentObjects) { // render transparent objects last so we can alpha blend
		obj->render();
	}
}

void ObjectManager::renderReflections(SimpleObjectManager &simpleObjectManager)
{
	glPushMatrix();
	glScalef(1, -1, 1); // scale -1 in axis normal to reflection
	glTranslatef(0, 2.f*10.01, 0); // translate to under the world
	for (auto obj : opaqueObjects) {
		if(obj->transform.position.length() > 0.8f*MAP_SIZE) // only render objects near reflective surface
			obj->render(); // render object otherwise as normal
	}
	for (auto obj : transparentObjects) {
		
		if (obj->transform.position.length() >0.8f*MAP_SIZE){ // only render objects near reflective surface
			glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);  // stencil for all colours
			glEnable(GL_STENCIL_TEST); // enable the stencil test
			glStencilFunc(GL_ALWAYS, 1, 1); // always make test
			glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); // keep value when test fails unless stencil and depth test pass
			glDisable(GL_DEPTH_TEST); 
			simpleObjectManager.drawPlane(Vector3(0, -10, 0), MAP_SIZE, MAP_SIZE, 300.f, SimpleObjectManager::grass); // main ground
			glEnable(GL_DEPTH_TEST);
			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);  // stencil for all colours
			glStencilFunc(GL_EQUAL, 0, 1); // only draw where there is a 0 (everything outside my geometry)
			glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); 
				obj->render(); // render object
			glDisable(GL_STENCIL_TEST); // disable stencil test
		}
	}
	glPopMatrix();
}

void ObjectManager::doLighting() // lighting for the scene
{
	lightManager->doGlobalLighting(); // main directinal light & ambient
	for (auto obj : objects) { // rest of the lights
		obj->doLighting();
	}
}
 
void ObjectManager::doSunShadows(SimpleObjectManager & simpleObjectManager)
{
	float* shadowMatrix = lightManager->getSunShadow();

	// same as above
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS,1,1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glDisable(GL_DEPTH_TEST);
	simpleObjectManager.drawPlane(Vector3(0, -10, 0),  MAP_SIZE, MAP_SIZE, 300.f, SimpleObjectManager::grass); // main ground
	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(GL_EQUAL, 1, 1); // draw only where there is a 1 (where the geometry is)
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glPushMatrix();
	glTranslatef(0, 0.01f, 0);
	glMultMatrixf((GLfloat*)shadowMatrix);
	for (auto obj : opaqueObjects) {
		obj->renderShadow();
	}
	spaceship.renderShadow();
	glPopMatrix();
	glDisable(GL_STENCIL_TEST);
							
}

void ObjectManager::moveSpaceship(Vector3 vec) // move the ufo
{
	
	spaceship.transform.position = vec ;
	
	
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
					toDel.push_back(obj); // save the ones im going to delete
				}
				return obj->markedForDeletion;// if the object is marked for deletion
			}),
		objects.end() // from returned itterator to the end of the array
		);

	for (auto obj : toDel) { // delete objects
		delete obj;
	}
	toDel.clear(); // clear that list
}


void ObjectManager::addGrass(int grass)
{
	srand(time(NULL));

	for (int i = 0; i < grass; i++) {

		float xpos = -MAP_SIZE + fmod(rand(), 2.f * MAP_SIZE); // randomised position
		float zpos = -MAP_SIZE + fmod(rand(), 2.f * MAP_SIZE);

		objectInfos[ObjectChildrenEnum::parents].push_back( // vector of objects that will be created, marked as a parent
			ObjectInfo(			// structure used to pass all the information of an object to the fucntions that initialise them
				ModelManager::ModelEnum::grass,	// enumerator for the model that will be loaded	
				Transform(						// transform structure
						Vector3(xpos, -10, zpos),	// random position on the plane
						Vector3(0.08, 0.08,0.08),	// scale down
						rand() % 360,				// random rotation scalar
						Vector3(0, 1, 0)			// rotate on y-axis
				),Vector3(1,1,1),1,					// colour and alpha (this model has texture so set to white)
				ObjectChildrenEnum::grassKids,		// this object has children in the index of 'grassKids'
				rand()								// random seed for time offset in animation
			)
		);
	}
}

void ObjectManager::addCows(int numberOfCows)
{
	srand(time(NULL)+1);
	for (int i = 0; i < numberOfCows; i++) {
		float xpos = -MAP_SIZE*1.25f + fmod(rand(), 2.f * MAP_SIZE); // randomised position
		float zpos = -MAP_SIZE*1.25f + fmod(rand(), 2.f * MAP_SIZE);  // cows can stand in the shallow water

		objectInfos[ObjectChildrenEnum::parents].push_back( // vector of objects that will be created, marked as a parent
			ObjectInfo(			// structure used to pass all the information of an object to the fucntions that initialise them
				ModelManager::ModelEnum::cow,// enumerator for the model that will be loaded	
				Transform(					 // transform structure
					Vector3(xpos, -10, zpos),	// random position on the plane
					Vector3(0.05, 0.05, 0.05),	// scale down
					rand() % 360,				// random rotation scalar
					Vector3(0, 1, 0)),			// rotate on y-axis
				Vector3(1, 1, 1), 1,			// colour and alpha (this model has texture so set to white)
				ObjectChildrenEnum::none,		// this object has no children objetcs
				rand()							// random seed for use in animation
			)
		);

	}
}


void ObjectManager::addTrees(int trees) // see above
{
	srand(time(NULL) + 2);
	for (int i = 0; i < trees; i++) {
		float xpos = -MAP_SIZE + fmod(rand(), 2.f * MAP_SIZE);
		float zpos = -MAP_SIZE + fmod(rand(), 2.f * MAP_SIZE);
		objectInfos[ObjectChildrenEnum::parents].push_back(ObjectInfo(ModelManager::ModelEnum::tree, Transform(Vector3(xpos, -10, zpos), Vector3(1, 1, 1), rand() % 360, Vector3(0, 1, 0))));

	}
}
