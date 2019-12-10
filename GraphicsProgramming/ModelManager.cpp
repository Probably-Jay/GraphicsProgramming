#include "ModelManager.h"

//ModelManager::instance = nullptr;

ModelManager::ModelManager()
{
}

ModelManager::~ModelManager()
{
	for (auto m : models) { // delete children
		delete m.second;
	}
}

bool ModelManager::loadModels() // load in each of the models
{
	bool sucess = true; 
	for (auto f : filenames) { // iterate over each filepath
		models[f.first] = new Model(); // create empty model object
		sucess = sucess && models[f.first]->load(f.second[0], f.second[1]); // load in the model
	}
	return sucess; //sucess will be false if any fail
}
 
Model* ModelManager::getModel(ModelEnum name) // return pointer to model from given enum index
{
	return models.at(name);
}
