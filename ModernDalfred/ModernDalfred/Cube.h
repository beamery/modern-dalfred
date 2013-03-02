#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexData.h"
#include "Utils.h"
#include "Shader.h"
#include "Mesh.h"
#include "Object.h"

using namespace std;
using namespace glm;

class Cube : Object {

public:
	Cube(vec3 matAmbient = vec3(1.0f,1.0f,1.0f), vec3 matDiffuse= vec3(1.0f,1.0f,1.0f));
	bool init();
	virtual bool draw(Shader &shader, mat4 &mv, const mat4 &proj);

private:
	void initVertices();
	//GLuint vertexArrayHandle;
	//GLuint vertexBufferHandle;
	//vector<VertexData> vertices;

	vec3 color;
	//vec3 materialDiffuse;
	//vec3 materialAmbient;
};


#endif