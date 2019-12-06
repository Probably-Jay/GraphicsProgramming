#include "SimpleObject.h"




SimpleObjectManager::SimpleObjectManager()
{
}

void SimpleObjectManager::loadTextures()
{
	for (auto tex : textureFilpaths) {
		GLint texture = SOIL_load_OGL_texture
		(
			tex.second,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y 
		);
		if (texture == 0)
		{
			printf("SOIL loading error: '%s'\n", SOIL_last_result());
			MessageBox(NULL, "Texture failed to load", "Error", MB_OK);
			
		}
		else {
			textures.insert(std::pair<SimpleTextureEnum,GLint>(tex.first,  texture));
		}
	}
}

void SimpleObjectManager::drawPlane(Vector3 pos, float scale, int resolution, SimpleTextureEnum tex)
{

	prepareTexture(tex);
	
	glPushMatrix();
	
	glTranslatef(pos.x,pos.y,pos.z);

	float halfTrianglesPerSide = resolution/2;

	float trianglesize = scale / halfTrianglesPerSide;
	float halfTrianglesize = trianglesize / 2.f;

	float halfTriangleProportion = halfTrianglesize / scale;

	glNormal3f(0.0f, 1.0f, 0.0f);

	glColor3f(1, 1, 1);
	for (float i = -halfTrianglesPerSide; i < halfTrianglesPerSide; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (float j = -halfTrianglesPerSide; j < halfTrianglesPerSide; j++) {

			glTexCoord2f(20.f*((j+halfTrianglesize)/halfTrianglesPerSide), 20.f*(-halfTriangleProportion + (i + halfTrianglesize) / halfTrianglesPerSide));
			glVertex3f(trianglesize*j, 0.f, -halfTrianglesize + trianglesize * i);

			glTexCoord2f(20.f*((j + halfTrianglesize) / halfTrianglesPerSide), 20.f*(halfTriangleProportion + (i + halfTrianglesize) / halfTrianglesPerSide));
			glVertex3f(trianglesize*j, 0.f, halfTrianglesize + trianglesize * i);
		}
		glEnd();
	}


	glPopMatrix();
}

void SimpleObjectManager::prepareTexture(SimpleTextureEnum tex)
{
	glBindTexture(GL_TEXTURE_2D, textures.at(tex));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}


