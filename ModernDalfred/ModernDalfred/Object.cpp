#include "Object.h"

Object::Object(vec3 matAmbient, vec3 matDiffuse) : 
	materialAmbient(matAmbient), materialDiffuse(matDiffuse) {}


void Object::takeDown() {
	if (this->vertexArrayHandle != GLuint(-1)) {
		glDeleteVertexArrays(1, &this->vertexArrayHandle);
	}

	if (this->vertexBufferHandle != GLuint(-1)) {
		glDeleteBuffers(1, &this->vertexBufferHandle);
	}

	this->vertexArrayHandle = this->vertexBufferHandle = GLuint(-1);
}