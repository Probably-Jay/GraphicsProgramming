#pragma once
#include "Light.h"
#include "Shadow.h"
#include <vector>
using namespace std;

class LightManager
{
public:
	LightManager();
	~LightManager();

	void initialise(Vector3 floorNormal, Vector3 floorPoint);

	Light* newPointLight(Vector3 position, Vector3 diffuse = Vector3(), float intensity = 1);
	Light* newDirectionalLight(Vector3 position, Vector3 diffuse = Vector3(), Vector3 ambient = Vector3(), float intensity =1, float ambientIntensity = 1);
	Light* newSpotLight(Vector3 position, Vector3 diffuse = Vector3(), Vector3 direction = Vector3(),float intensity = 1, float angle = 30);

	float* getSunShadow();
	//void addLight(Light * l);

	void doAllLighting();
	void doSpecificLighting(Light* l);
	void doGlobalLighting();

private:

	Light * sun;
	Shadow sunShadow;


	//std::array<std::pair< GLint, Light*>, 8> lights;
	//

	vector<GLint> GLlights;
	vector<Light*> lights;

};

