// Below ifdef required to remove warnings for unsafe version of fopen and fscanf.
// Secure version won't work cross-platform, forcing this small hack.
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "model.h"
#include <iostream>

bool Model::load(char* modelFilename, char* textureFilename)
{
	bool result;

	// Load in the model data,
	result = loadModel(modelFilename);
	if (!result)
	{
		MessageBox(NULL, "Model failed to load", "Error", MB_OK);
		return false;
	}

	// Load the texture for this model.
	result = loadTexture(textureFilename);
	if (!result)
	{
		MessageBox(NULL, "Texture failed to load", "Error", MB_OK);
		return false;
	}

	return true;
}

void Model::render()
{
	// TODO: Need to add code here to render the loaded model
	// How this is done is based on how you stored and sorted the data

	glBindTexture(GL_TEXTURE_2D, texture);//tells openglwhich texture to use

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, &verts[0]);
	glNormalPointer(GL_FLOAT, 0, &norms[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &texCoords[0]);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < verts.size()/3 ; i++) {
		glArrayElement(i);
	}
	glEnd();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


// Modified from a mulit-threaded version by Mark Ropper.
bool Model::loadModel(char* filename)
{
	vector<Vector3> loadVerts;
	vector<Vector3> LoadNormals;
	vector<Vector3> LoadTexCoords;
	vector<unsigned int> faces;
	
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		return false;
	}
	while (true)
	{
		char lineHeader[128];

		// Read first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break; // exit loop
		}
		else // Parse
		{
			if (strcmp(lineHeader, "v") == 0) // Vertex
			{
				Vector3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				loadVerts.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) // Tex Coord
			{
				Vector3 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				LoadTexCoords.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) // Normal
			{
				Vector3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				LoadNormals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) // Face
			{
				unsigned int face[9];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &face[0], &face[1], &face[2],
																			&face[3], &face[4], &face[5],
																			&face[6], &face[7], &face[8]);
				if (matches != 9)
				{
					// Parser error, or not triangle faces
					return false;
				}
				
				for (int i = 0; i < 9; i++)
				{
					faces.push_back(face[i]);
				}


			}
		}
	}

	// "Unroll" the loaded obj information into a list of triangles.
	// TODO: By this point all model has been read from the file, but is not in the correct order.
	// You NEED to loop over all the data and sort it into a render ready order/format.
	
	//std::cout << faces.size() << endl;

	for (int i = 0; i < faces.size(); i += 3) { // three peices of informarion per vertex

		verts.push_back(loadVerts[faces[i]-1].x);
		verts.push_back(loadVerts[faces[i]-1].y);
		verts.push_back(loadVerts[faces[i]-1].z);

		texCoords.push_back(LoadTexCoords[faces[i + 1]-1].x);
		texCoords.push_back(LoadTexCoords[faces[i + 1]-1].y);

		norms.push_back(LoadNormals[faces[i + 2]-1].x);
		norms.push_back(LoadNormals[faces[i + 2]-1].y);
		norms.push_back(LoadNormals[faces[i + 2]-1].z);

	}
	
	// Once data has been sorted clear read data (which has been copied and are not longer needed).
	loadVerts.clear();
	LoadNormals.clear();
	LoadTexCoords.clear();
	faces.clear();

	return true;
}

bool Model::loadTexture(char* filename)
{
//	texture = SOIL_load_OGL_texture
//	(
//		filename,
//		SOIL_LOAD_AUTO,
//		SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT // Depending on texture file type some need inverted others don't.
//	);
	
	
	texture = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y // Depending on texture file type some need inverted others don't.
	);

	//check for an error during the load process
	if (texture == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
	return texture != 0;

}


