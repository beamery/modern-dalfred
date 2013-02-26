#ifndef SHADER_H
#define SHADER_H

#include <gl/freeglut.h>

class Shader {
public:
	// create a shader program with the given vertex and fragment shaders
	Shader(const char *vert, const char *frag);

	void use();

private:
	GLuint createShader(const char *src, GLenum type);
};


#endif