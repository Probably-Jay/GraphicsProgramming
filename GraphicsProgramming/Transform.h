#pragma once
#include "Vector3.h"
//#include "ObjectInfo.h"
//struct ObjectInfo;
struct Transform 
{
	
	
	//Transform(ObjectInfo const & info) :ObjectInfo(info) {};

	Transform(Vector3 position = Vector3::zero(), Vector3 scale = Vector3::one(), float roatationScalar = 0, Vector3 rotationVector = Vector3(0,0,1)): 
		position(position), scale(scale), rotationScalar(roatationScalar), rotationVector(rotationVector){};

	Vector3 position;
	Vector3 scale;
	float rotationScalar;
	Vector3 rotationVector;
};