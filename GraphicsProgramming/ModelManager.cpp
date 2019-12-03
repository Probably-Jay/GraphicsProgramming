#include "ModelManager.h"

//ModelManager::instance = nullptr;

ModelManager::ModelManager()
{
}

ModelManager::~ModelManager()
{
}

bool ModelManager::loadModels()
{
	bool sucess = true;
	for (auto f : filenames) {
		models[f.first] = new Model();
		sucess = sucess && models[f.first]->load(f.second[0], f.second[1]);
	}

	return sucess;
}

Model* ModelManager::getModel(ModelEnum name)
{
	return models.at(name);
}
