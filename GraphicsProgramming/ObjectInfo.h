#pragma once
#include "Vector3.h"
#include "Transform.h"
#include "Model.h"
#include "ModelManager.h"

#include <map>
enum ObjectChildrenEnum
{
	parents,
	teapotKids,
	none,
};

//  char * ObjName, char * texName

struct ObjectInfo:Transform
{
	ObjectInfo(ModelManager::ModelEnum model, Transform const& trans = Transform(),ObjectChildrenEnum childrenEnum = ObjectChildrenEnum::none)
		: modelName(model),  Transform(trans), childrenEnum(childrenEnum)
	{};

	ModelManager::ModelEnum modelName;
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



