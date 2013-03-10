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
#include "ParticleShader.h"
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

	bool draw(ParticleShader &shader, MatrixStack &mvs, mat4 proj, float time);
	bool initGL();

private:
	vector<vec3> positions;
	vector<vec3> velocities;
	vector<GLfloat> startTimes;

	//vector<ParticleData> particles;

	GLuint particleArray[2];
	GLuint feedback[2];
	GLuint posBuf[2];
	GLuint velBuf[2];
	GLuint startBuf[2];
	GLuint initVelBuf;
	GLuint drawBuf;

	GLuint vertexArrayHandle;
	GLuint vertexBufferHandle;
};


#endif