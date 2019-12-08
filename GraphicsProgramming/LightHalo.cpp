#include "LightHalo.h"
#include "ModelManager.h"
bool LightHalo::initialise(ObjectInfo myinfo, ModelManager& modelManager, LightManager* lightManager)
{
	light = lightManager->newPointLight(myinfo.position, Vector3(1, 0, 0), 1);
	lights.push_back(light);
	return Object::initialise(myinfo, modelManager, lightManager);
}
void LightHalo::update(float dt, Vector3 pos)
{
	time += 3*dt;
	float offset = std::floorf(std::fmod(time, 6.f));
	transform.position = (Vector3(2 * cos(offset), 0.3, 2 * sin(offset)));
	updateLightPosition(pos + transform.position);
	Object::update(dt);
}
void LightHalo::updateLightPosition(Vector3 position)
{
	light->updatePosition(position);
}
//void LightHalo::update(float dt)
//{
//	light->updatePosition(transform.position);
//}

//void LightHalo::render()
//{
//	glPushMatrix();
//		glTranslatef(transform.position.x, transform.position.y, transform.position.z);
//		glRotatef(transform.rotationScalar, transform.rotationVector.x, transform.rotationVector.y, transform.rotationVector.z);
//		glScalef(transform.scale.x, transform.scale.y, transform.scale.z);
//		renderModel();
//	glPopMatrix();
//}

//void LightHalo::renderModel()
//{
//
//	bool lightOn = glIsEnabled(GL_LIGHTING);
//	if (alpha < 1) {
//		glEnable(GL_BLEND);
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//		lightOn = glIsEnabled(GL_LIGHTING);
//		glDisable(GL_LIGHTING);
//		glEnable(GL_CULL_FACE);
//		glCullFace(GL_BACK);
//	}
//
//
//	gluSphere(gluNewQuadric(), 1,1, 1);
//
//	
//	glDisable(GL_BLEND);
//	glDisable(GL_CULL_FACE);
//	
//
//	if (lightOn) {
//		glEnable(GL_LIGHTING);
//	}
//
//}