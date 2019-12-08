#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
		
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);

	// Other OpenGL / render setting should be applied here.

	cam.loadSkybox(objectManager.getModelManager());

	input->setMousePos(width / 2, height / 2);
	glutWarpPointer(width / 2, height / 2);
	glutSetCursor(GLUT_CURSOR_NONE);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	// Initialise scene variables
	lightManager.initialise(Vector3(0,1,0),Vector3(0,-10,0));
	objectManager.loadObjects(&lightManager);
	simpleObjectManager.loadTextures();

	
	
}

void Scene::handleInput(float dt)
{
	// Handle user input
	cam.handleInput(input, width, height, dt);

	if (input->isKeyDown('m')) {
		warpCursor = !warpCursor;
		
		input->SetKeyUp('m');
	}

	if (warpCursor) {
		glutWarpPointer(width / 2, height / 2);
	}


	if (input->isKeyDown('r')) {
		glGetIntegerv(GL_POLYGON_MODE, &polygonMode);

		if (polygonMode == GL_LINE) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else if (polygonMode == GL_FILL) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		input->SetKeyUp('r');
	}
	objectManager.handleInput(input);

}

void Scene::update(float dt)
{
	// update scene related variables.
	cam.update(dt);
	float s = sin(glutGet(GLUT_ELAPSED_TIME) / 1000.f);

	//objectManager.objects[0]->transform.rotationScalar = 20 + 50*sin(glutGet(GLUT_ELAPSED_TIME)/1000.f);
	//objectManager.objects[0]->applyTransformToAllChildren(Transform(Vector3(10,55,0), Vector3(0.8,0.8,0.8),   50 * s));

	cam.updateLookAt();
	objectManager.updateObjects(dt);
	if (cam.isFollowingSpaceship()) {
		objectManager.moveSpaceship( cam.getLookAt() +cam.getForwardDirection().multiply(20) , false);
	}


	// Calculate FPS for output
	calculateFPS();
}

void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(cam.getPosition().x, cam.getPosition().y, cam.getPosition().z, cam.getLookAt().x, cam.getLookAt().y, cam.getLookAt().z, cam.getUpDirection().x, cam.getUpDirection().y, cam.getUpDirection().z);
	cam.drawSkybox();
	// Render geometry/scene here -------------------------------------
	

	simpleObjectManager.drawPlane(Vector3(0,-10,0), 1.2*MAP_SIZE, 300,SimpleObjectManager::grass);
	objectManager.renderObjects();
	
	
	objectManager.doLighting();
	//objectManager.doSunShadows();


	//lightManager.doAllLighting();
	

	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}





// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 300.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

	
}

// Calculates FPS
void Scene::calculateFPS()
{

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	sprintf_s(camPos, "Camera at: (%f, %f)", cam.getRotation().x, cam.getRotation().y);
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
	displayText(-1.f, 0.84f, 1.f, 0.f, 0.f, camPos);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
