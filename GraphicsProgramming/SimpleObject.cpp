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
			////MessageBox(NULL, "Texture failed to load", "Error", MB_OK);
			
		}
		else {
			textures.insert(std::pair<SimpleTextureEnum,GLint>(tex.first,  texture));
		}
	}
}

void SimpleObjectManager::drawPlane(Vector3 pos, float xsize, float ysize, int resolution, SimpleTextureEnum tex, Vector3 colour , float alpha)
{
	// if not to be texured
	if (tex == SimpleTextureEnum::none) {
		glBindTexture(GL_TEXTURE_2D,0);
	}
	else {
		prepareTexture(tex);
	}

	// if transparent
	if (alpha < 1.f) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_LIGHTING);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);	
	}

	glPushMatrix();
	
	glTranslatef(pos.x,pos.y,pos.z); // translate to position


	// generate plane 

	float halfTrianglesPerSide = resolution/2.f;

	float xtrianglesize = xsize / halfTrianglesPerSide;
	float ytrianglesize = ysize / halfTrianglesPerSide;

	float xhalfTrianglesize = xtrianglesize / 2.f;
	float yhalfTrianglesize = ytrianglesize / 2.f;

	float xhalfTriangleProportion = xhalfTrianglesize / xsize;
	float yhalfTriangleProportion = yhalfTrianglesize / xsize;

	glNormal3f(0.0f, 1.0f, 0.0f); // normal is up
	glColor4f(colour.x,colour.y,colour.z,alpha); // assign colour

	for (float i = -halfTrianglesPerSide; i < halfTrianglesPerSide; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (float j = -halfTrianglesPerSide; j < halfTrianglesPerSide; j++) {

			glTexCoord2f(20.f*((j+xhalfTrianglesize)/halfTrianglesPerSide), 20.f*(-yhalfTriangleProportion + (i + yhalfTrianglesize) / halfTrianglesPerSide));
			glVertex3f(xtrianglesize*j, 0.f, -yhalfTrianglesize + ytrianglesize * i);

			glTexCoord2f(20.f*((j + xhalfTrianglesize) / halfTrianglesPerSide), 20.f*(yhalfTriangleProportion + (i + yhalfTrianglesize) / halfTrianglesPerSide));
			glVertex3f(xtrianglesize*j, 0.f, yhalfTrianglesize + ytrianglesize * i);
		}
		glEnd();
	}
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glColor4f(1,1,1,1); // reset colour
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


