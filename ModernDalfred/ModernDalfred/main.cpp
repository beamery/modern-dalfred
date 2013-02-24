#include <iostream>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "MatrixStack.h"

using namespace std;

struct WindowData
{
	GLint height, width;
	GLint handle;
} window;

MatrixStack mvs;

void DisplayFunc()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	glViewport(0, 0, window.width, window.height);


	glutSwapBuffers();
	glutPostRedisplay();
}

void ReshapeFunc(GLint w, GLint h)
{
	if (h > 0)
	{
		window.height = h;
		window.width = w;
	}
}

void KeyboardFunc(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 'x':
	case 27:
		glutLeaveMainLoop();
		return;
	}
}

int main(int argc, char * argv[])
{
	cout << "Hello World" << endl;
	glutInit(&argc , argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(window.width , window.height);
	window.handle = glutCreateWindow("Hello World");
	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutKeyboardFunc(KeyboardFunc);

	glutMainLoop();
}