#pragma once
#include "Model.h"
#include "Vector3.h"
class Object
{
public:
	Object();
	~Object();


	bool load(char* modelFilename, char* textureFilename);
	void render();

private:
	Vector3 positon;
	Model model;

};

