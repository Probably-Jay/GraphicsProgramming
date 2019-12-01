#include "SimpleObject.h"




void SimpleObject::drawPlane(Vector3 pos, float scale, int resolution)
{

	glPushMatrix();
	
	glTranslatef(pos.x,pos.y,pos.z);

	float halfTrianglesPerSide = resolution/2;

	float trianglesize = scale / halfTrianglesPerSide;
	float halfTrianglesize = trianglesize / 2.f;

	glNormal3f(0.0f, 0.0f, -1.0f);

	glColor3f(1, 1, 1);
	for (float i = -halfTrianglesPerSide; i < halfTrianglesPerSide; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (float j = -halfTrianglesPerSide; j < halfTrianglesPerSide; j++) {
			glVertex3f(trianglesize*j, 0.f, -halfTrianglesize + trianglesize * i);
			glVertex3f(trianglesize*j, 0.f, halfTrianglesize + trianglesize * i);
		}
		glEnd();
	}


	glPopMatrix();
}


