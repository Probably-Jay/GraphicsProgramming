#pragma once
#include "Vector3.h"
#include "Transform.h"

#include <map>
enum ObjectChildrenEnum
{
	parents,
	teapotKids,
	none,
};

struct ObjectInfo:Transform
{
	ObjectInfo(Transform const & trans, char * ObjName, char * texName, ObjectChildrenEnum childrenEnum = ObjectChildrenEnum::none) 
		:Transform(trans), objFileName(ObjName), texFileName(texName), childrenEnum(childrenEnum) 
	{};

	char * objFileName;
	char * texFileName;
	ObjectChildrenEnum childrenEnum;


	/*ObjectInfo(char * ObjName, char * texName, Vector3 position, Vector3 scale, float roatationScalar, Vector3 rotationVector, ObjectChildrenEnum childrenEnum = ObjectChildrenEnum::none)
		:objFileName(ObjName), texFileName(texName), position(position), scale(scale), roatationScalar(roatationScalar), rotationVector(rotationVector), childrenEnum(childrenEnum) {};
*/
	/*Vector3 position;
	Vector3 scale;
	float roatationScalar;
	Vector3 rotationVector;
*/
	//Transform returnTransform() { return Transform(*this); };

	//Transform returnTransform() { return Transform(position, scale, roatationScalar, rotationVector); };

};



