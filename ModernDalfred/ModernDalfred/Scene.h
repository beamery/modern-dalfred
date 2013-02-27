#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <GL/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Triangle.h"
#include "Shader.h"

class Scene {

public:
	Scene();
	void init();
	void draw(Shader &shader, mat4 &mv, const mat4 &proj, const ivec2 &size, const float time);

private:
	Triangle triangle;
};


#endif