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
		cow,
		ufo,
		beam,
		grass,
		skybox,
		tree,

		none
	};

	Model* getModel(ModelEnum name);





private:

	
	
	// list of the filepaths for the objects
	map<ModelEnum, vector<char*> >filenames {
		{ufo,{"models/ufo.obj", "gfx/ufo.png"}},
		{beam,{"models/beam.obj", "gfx/Beam.png"}},
		{cow,{"models/moo.obj", "gfx/cow.png"}},
		{tree,{"models/Poplar_Tree.obj", "gfx/tree.png"}},
		{grass,{"models/grassCube.obj", "gfx/grass.png"}},
		{ball,{"models/ball.obj", "gfx/light.png"}},
		{skybox,{"models/invertedCube.obj", "gfx/kisspng-space-skybox-texture.png"}},
	};


	map<ModelEnum, Model*> models;
	


};


		//{teapot,{"models/teapot.obj", "gfx/checked.png"}},
		//{garfield,{"models/garfiled.obj", "gfx/garfieldskin.png"}},