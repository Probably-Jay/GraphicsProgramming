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

	void drawPlane(Vector3 pos, float xsize, float ysize, int resolution, SimpleTextureEnum tex = SimpleTextureEnum::none, Vector3 colour = Vector3(1,1,1), float alpha = 1.f);



private:

	void prepareTexture(SimpleTextureEnum tex);

	std::map<SimpleTextureEnum, GLuint> textures;

	std::map<SimpleTextureEnum, char*> textureFilpaths = {
		{grass,"gfx/grass.png"},
		{grass,"gfx/grass.png"},
	};




};

