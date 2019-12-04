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
		cow,
		ufo,
		garfield,
		none
	};

	Model* getModel(ModelEnum name);





private:

	
	

	map<ModelEnum, vector<char*> >filenames {
		{teapot,{"models/teapot.obj", "gfx/checked.png"}},
		{cow,{"models/moo.obj", "gfx/garfieldskin.png"}},
		{ufo,{"models/ufo.obj", "gfx/ufo.png"}},
		//{garfield,{"models/garfiled.obj", "gfx/garfieldskin.png"}},
	};


	map<ModelEnum, Model*> models;
	


};

