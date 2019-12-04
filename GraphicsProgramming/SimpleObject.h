#pragma once
#include"GlHeaders.h"
#include "Vector3.h"
#include <map>;
#include "SOIL.h"
class SimpleObjectManager
{
public:

	SimpleObjectManager();

	void loadTextures();




	enum SimpleTextureEnum
	{
		grass,
		none,
	};

	void drawPlane(Vector3 pos, float size, int resolution, SimpleTextureEnum tex);



private:

	void prepareTexture(SimpleTextureEnum tex);

	std::map<SimpleTextureEnum, GLuint> textures;

	std::map<SimpleTextureEnum, char*> textureFilpaths = {
		{grass,"gfx/grass.png"},
	};




};

