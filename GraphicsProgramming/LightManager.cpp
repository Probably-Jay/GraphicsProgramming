#include "LightManager.h"

LightManager::LightManager()
{
}

LightManager::~LightManager()
{
}

void LightManager::initialise()
{
	lights = {};

	GLlights.push_back(GL_LIGHT0);
	GLlights.push_back(GL_LIGHT1);
	GLlights.push_back(GL_LIGHT2);
	GLlights.push_back(GL_LIGHT3);
	GLlights.push_back(GL_LIGHT4);
	GLlights.push_back(GL_LIGHT5);
	GLlights.push_back(GL_LIGHT6);
	GLlights.push_back(GL_LIGHT7);


	/*lights[1]=(std::pair< GLint, Light*>(GL_LIGHT0, nullptr));
	lights[2]=(std::pair< GLint, Light*>(GL_LIGHT1, nullptr));
	lights[3]=(std::pair< GLint, Light*>(GL_LIGHT2, nullptr));
	lights[4]=(std::pair< GLint, Light*>(GL_LIGHT3, nullptr));
	lights[5]=(std::pair< GLint, Light*>(GL_LIGHT4, nullptr));
	lights[6]=(std::pair< GLint, Light*>(GL_LIGHT5, nullptr));
	lights[7]=(std::pair< GLint, Light*>(GL_LIGHT6, nullptr));
	lights[8]=(std::pair< GLint, Light*>(GL_LIGHT7, nullptr));*/

}

Light* LightManager::newPointLight(Vector3 position, Vector3 diffuse)
{
	return nullptr;
}

Light* LightManager::newDirectionalLight(Vector3 position, Vector3 diffuse, Vector3 ambient)
{
	return nullptr;
}

Light* LightManager::newSpotLight(Vector3 position, Vector3 diffuse, Vector3 direction, float intensity, float angle)
{
	if (lights.size() < 8) {
		Light * l = new Light();
		l->initialise(Light::LightType::spot, position,diffuse,direction,Vector3(),intensity,angle);
		lights.push_back(l);
		return l;
	}
	else {
		return nullptr;
	}

}

void LightManager::doLighting()
{
	glEnable(GL_LIGHTING);
	for (int i = 0; i < lights.size(); i ++) {
		Light* light = lights[i];

		glLightfv(GLlights[i], GL_POSITION, light->lightPosition);
		glLightfv(GLlights[i], GL_DIFFUSE, light->diffuse);

		switch (light->type)
		{
		case Light::point:
			break;
		case Light::directional:
			glLightfv(GLlights[i], GL_AMBIENT, light->ambient);
			break;
		case Light::spot:
			glLightfv(GLlights[i], GL_SPOT_DIRECTION, light->direction);
			glLightf(GLlights[i], GL_SPOT_CUTOFF,  light->spotAngle);
			glLightf(GLlights[i], GL_SPOT_EXPONENT, light->intensity);
			break;
		default:
			break;
		}
		glEnable(GLlights[i]);
	}
}

