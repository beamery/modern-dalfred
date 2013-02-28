/*
 * Brian Murray
 * CS 559 Project 2
 */

#include <iostream>
#include <assert.h>
#include <vector>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Scene.h"
#include "Shader.h"
#include "Mesh.h"
#include "MatrixStack.h"

using namespace std;
using namespace glm;

struct Window {
	int window_handle;
	ivec2 size;
	float window_aspect;
	vector<string> instructions;
} window;

Scene scene;
Shader shader;
MatrixStack mvs;

void ReshapeFunc(int w, int h) {
	if (window.window_handle != -1 &&  h > 0)
	{
		window.size = ivec2(w, h);
		window.window_aspect = float(w) / float(h);
	}
}

void KeyboardFunc(unsigned char c, int x, int y) {
	if (window.window_handle == -1)
		return;

	switch (c)
	{
	case 'p':
		Mesh::drawPoints = !Mesh::drawPoints;
		break;
	case 'x':
	case 27:
		glutLeaveMainLoop();
		return;
	}
}

void SpecialFunc(int c, int x, int y) {
}

void DisplayInstructions() {
	if (window.window_handle == -1)
		return;

	vector<string> * s = &window.instructions;
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window.size.x, 0, window.size.y, 1, 10);
	glViewport(0, 0, window.size.x, window.size.y);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(10, 18 * s->size(), -5.5);
	glScaled(0.1, 0.1, 1.0);
	for (auto i = s->begin(); i < s->end(); ++i)
	{
		glPushMatrix();
		glutStrokeString(GLUT_STROKE_MONO_ROMAN, (const unsigned char *) (*i).c_str());
		glPopMatrix();
		glTranslated(0, -150, 0);
	}
}

void DisplayFunc() {
	if (window.window_handle == -1)
		return;

	glEnable(GL_DEPTH_TEST);

	mvs.push();

	float time = float(glutGet(GLUT_ELAPSED_TIME)) / 1000.0f;
	mat4 projection = perspective(50.0f, window.window_aspect, 1.0f, 1000.0f);

	// put camera 2m above the scene
	mvs.active = translate(mvs.active, vec3(0.0f, -2.5f, 0.0f));

	glViewport(0, 0, window.size.x, window.size.y);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene.draw(shader, mvs, projection, window.size, time);
	
	mvs.pop();
	
	//DisplayInstructions();
	glutSwapBuffers();
	glutPostRedisplay();
}

void initShaders() {
	shader.init("lighting.vert", "lighting.frag");
	shader.getUniformLocation("lightPosition");
	shader.getUniformLocation("Kd");
	shader.getUniformLocation("Ld");
}

void initScene() {
	scene.init();
}

void testMesh() {
}



int main(int argc, char * argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(1280, 720);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	window.window_handle = glutCreateWindow("Modern Hello World");
	glutReshapeFunc(ReshapeFunc);
	glutDisplayFunc(DisplayFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);

	window.instructions.push_back("Brian Murray - CS 559 Project 2");

	if (glewInit() != GLEW_OK)
	{
		cerr << "GLEW failed to initialize." << endl;
		return 0;
	}
	initShaders();
	initScene();
	glutMainLoop();
}
