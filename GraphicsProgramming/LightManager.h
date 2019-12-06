#pragma once
#include "Light.h"
#include <vector>
using namespace std;

class LightManager
{
public:
	LightManager();
	~LightManager();

	void initialise();

	Light* newPointLight(Vector3 position, Vector3 diffuse = Vector3());
	Light* newDirectionalLight(Vector3 position, Vector3 diffuse = Vector3(), Vector3 ambient = Vector3());
	Light* newSpotLight(Vector3 position, Vector3 diffuse = Vector3(), Vector3 direction = Vector3(),float intensity = 1, float angle = 30);


	//void addLight(Light * l);

	void doLighting();

private:

	//std::array<std::pair< GLint, Light*>, 8> lights;
	//

	vector<GLint> GLlights;
	vector<Light*> lights;

};

