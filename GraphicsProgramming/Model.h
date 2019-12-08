// Model class, represents a loaded OBJ model
// handles the loading/processing of the model file. Also loads and stores its own texture

#ifndef _MODEL_H_
#define _MODEL_H_

// INCLUDES //
#include <glut.h>
#include <fstream>
#include <gl/gl.h>
#include <gl/glu.h>

using namespace std;

// MY CLASS INCLUDES //
#include <vector>
#include "Vector3.h"
#include "SOIL.h"

class Model
{
	friend class Object;
public:

	bool load(char* modelFilename, char* textureFilename);
	void render(float alpha = 1);

private:

	void renderShadow();

	bool loadTexture(char*);
	bool loadModel(char*);

	int m_vertexCount;
	GLuint texture;

	//vector<float> loadVertex, loadNormals, loadTexCoords;

	vector<float> verts, norms, texCoords;


};

#endif