#include "Shadow.h"


void Shadow::initialiseShadow(GLfloat floor[12])
{

}

void Shadow::initialiseShadow(Vector3 planeNormal, Vector3 point) // intialise varaibles that arnt going to change
{
	floorNormal = planeNormal;
	floorPoint = point;
	
}


// shadow matrix generation funciton, adapted from lab example
void Shadow::generateShadowMatrix( Vector3 lightPos, Vector3 direction, Vector3 planeNormal, Vector3 point)
{
	//Equation of plane is ax + by + cz = d
	//a, b and c are the coefficients of the normal to the plane (i.e. normal = ai + bj + ck)
	//If (x0, y0, z0) is any point on the plane, d = a*x0 + b*y0 + c*z0
	//i.e. d is the dot product of any point on the plane (using P here) and the normal to the plane
	Vector3 normal = planeNormal;
	
	float a, b, c, d;
	a = normal.getX();
	b = normal.getY();
	c = normal.getZ();
	d = normal.dot(point);

	//Origin of projection is at x, y, z. Projection here originating from the light source's position
	float x, y, z;
	if (lightPos == Vector3(0, 0, 0)) { // directional light
		//	directional light projection point can be aproximated as a point
		//		at a far distance in the negative direction of the light
		x = 10000.f * -direction.x; 
		y = 10000.f * -direction.y;
		z = 10000.f * -direction.z;

	} else if (direction == Vector3(0, 0, 0)) { // point light
		x = lightPos.x;
		y = lightPos.y;
		z = lightPos.z;
	}
	else { // spot light
		x = lightPos.x;
		y = lightPos.y;
		z = lightPos.z;
	}
	


	//This is the general perspective transformation matrix from a point (x, y, z) onto the plane ax + by + cz = d
	shadowMatrix[0] = d - (b * y + c * z);
	shadowMatrix[1] = a * y;
	shadowMatrix[2] = a * z;
	shadowMatrix[3] = a;

	shadowMatrix[4] = b * x;
	shadowMatrix[5] = d - (a * x + c * z);
	shadowMatrix[6] = b * z;
	shadowMatrix[7] = b;

	shadowMatrix[8] = c * x;
	shadowMatrix[9] = c * y;
	shadowMatrix[10] = d - (a * x + b * y);
	shadowMatrix[11] = c;

	shadowMatrix[12] = -d * x;
	shadowMatrix[13] = -d * y;
	shadowMatrix[14] = -d * z;
	shadowMatrix[15] = -(a * x + b * y + c * z);
		

	

}





float* Shadow::getShadowMatrix(Vector3 lightPos,Vector3 lightDirection)
{
	generateShadowMatrix(lightPos,lightDirection,floorNormal, floorPoint);
	return shadowMatrix;
}

