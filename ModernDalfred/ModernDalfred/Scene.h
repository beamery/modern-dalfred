#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Triangle.h"
#include "Shader.h"
#include "Mesh.h"
#include "Grid.h"
#include "MatrixStack.h"

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
};


#endif