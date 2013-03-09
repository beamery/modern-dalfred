#ifndef PARTICLE_FOUNTAIN_H
#define PARTICLE_FOUNTAIN_H

#define PARTICLE_LIFETIME 5.0f

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "MatrixStack.h"
#include "ParticleData.h"
#include "Utils.h"
#include "Shader.h"
#include "Constants.h"

using namespace glm;

/*
 * This class is a test class for a simple particle system. 
 * Much of the code is lifted from the OpenGL 4.0 Shading Language Cookbook
 */
class ParticleFountain {

public:
	ParticleFountain(int numParticles);

	void update(float elapsedTime);

	bool draw(Shader &shader, MatrixStack &mvs, mat4 proj, float elapsedTime);
	bool initGL();

private:
	vector<ParticleData> particles;
	GLuint vertexArrayHandle;
	GLuint vertexBufferHandle;
};


#endif