#ifndef SCENE_H
#define SCENE_H

#define WORLD_UNITS_PER_METER 1.00f
#define METERS_PER_INCH 0.0254f
#define GRID_SIZE 64

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "MatrixStack.h"
#include "Shader.h"
#include "Mesh.h"
#include "Grid.h"
#include "Cube.h"
#include "Triangle.h"

using namespace std;
using namespace glm;

class Scene {

public:
	Scene();
	~Scene();
	void init();
	void draw(Shader &shader, MatrixStack &mvs, const mat4 &proj, const ivec2 &size, const float time);

private:
	Grid *grid;
	Cube cube;
	Triangle t;

	vec4 lightPos;
	vec3 lightDiffuse;
	vec3 lightAmbient;
};


#endif