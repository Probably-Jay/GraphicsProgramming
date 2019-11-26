#pragma once
#include "Vector3.h"
class Light
{
public:
	Light();
	~Light();

	void setUpLight();

private:
	Vector3 position;
};

