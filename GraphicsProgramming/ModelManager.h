#pragma once
#include "Model.h"
#include <vector>
#include <map>

class ModelManager
{

public:
	

	ModelManager();
	~ModelManager();

	


	bool loadModels();

	enum ModelEnum
	{
		teapot,

		none
	};

	Model* getModel(ModelEnum name);





private:

	
	

	map<ModelEnum, vector<char*> >filenames {
		{teapot,{"models/teapot.obj", "gfx/checked.png"}},
	};


	map<ModelEnum, Model*> models;
	


};

