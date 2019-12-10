#pragma once
#include "Vector3.h"
#include "Transform.h"
#include "Model.h"
#include "ModelManager.h"

#include <map>
enum ObjectChildrenEnum
{
	parents,
	grassKids,
	none,
};

//  char * ObjName, char * texName

struct ObjectInfo:Transform
{
	ObjectInfo() {};
	//ObjectInfo(Transform const& trans = Transform(),  Vector3 colour = Vector3(1, 1, 1), float alpha = 1):
	//	Transform(trans), alpha(alpha), colour(colour) {};
	ObjectInfo(ModelManager::ModelEnum model, Transform const& trans = Transform(), Vector3 colour = Vector3(1,1,1), float alpha = 1, ObjectChildrenEnum childrenEnum = ObjectChildrenEnum::none, float randomSeed = 0)
		: modelName(model),  Transform(trans), alpha(alpha), colour(colour), childrenEnum(childrenEnum), randomSeed(randomSeed) {};


	ModelManager::ModelEnum modelName;
	ObjectChildrenEnum childrenEnum;
	float alpha;
	Vector3 colour;
	float randomSeed;

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



