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
		uninitialised,
		ball,
		teapot,
		cow,
		ufo,
		beam,
		grass,
		skybox,
		tree,

		garfield,
		none
	};

	Model* getModel(ModelEnum name);





private:

	
	

	map<ModelEnum, vector<char*> >filenames {
		{teapot,{"models/teapot.obj", "gfx/checked.png"}},
		{ball,{"models/ball.obj", "gfx/light.png"}},
		{cow,{"models/moo.obj", "gfx/cow.png"}},
		{ufo,{"models/ufo.obj", "gfx/ufo.png"}},
		{beam,{"models/beam.obj", "gfx/Beam.png"}},
		{grass,{"models/grassCube.obj", "gfx/grass.png"}},
		{skybox,{"models/invertedCube.obj", "gfx/kisspng-space-skybox-texture.png"}},
		{tree,{"models/Poplar_Tree.obj", "gfx/tree.png"}},
		
		
		//{garfield,{"models/garfiled.obj", "gfx/garfieldskin.png"}},
	};


	map<ModelEnum, Model*> models;
	


};

