#pragma once
#include "Vector3.h"
#include <map>
enum ObjectChildrenEnum
{
	parents,
	teapotKids,
	none,
};

struct ObjectInfo
{
	ObjectInfo(char * ObjName, char * texName, Vector3 position, ObjectChildrenEnum childrenEnum = ObjectChildrenEnum::none)
		:objFileName(ObjName), texFileName(texName), position(position), childrenEnum(childrenEnum) {};
	char * objFileName;
	char * texFileName;
	Vector3 position;
	ObjectChildrenEnum childrenEnum;

};



