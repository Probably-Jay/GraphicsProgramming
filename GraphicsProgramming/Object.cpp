#include "Object.h"



Object::Object()
{
}


Object::~Object()
{
}

bool Object::load(char * modelFilename, char * textureFilename)
{
	return model.load(modelFilename, textureFilename);
}

void Object::render()
{
	model.render();
}
