/*	Perry Kivolowitz - University of Wisconsin - Madison 
	Computer Sciences Department

	A sample hello world like program demonstrating modern
	OpenGL techniques. 

	Created:	2/25/13
	Updates:
*/

#pragma once
#include <iostream>
#include <sstream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Utils.h"

class Shader {
public:
	Shader();
	void TakeDown();
	void Use();
	virtual bool Initialize(char * vertex_shader_file, char * fragment_shader_file);
	virtual void CustomSetup();
	void CommonSetup(const float time, const GLint * size, const GLfloat * mvp);
	std::stringstream GetShaderLog(GLuint shader_id);

	GLuint vertex_shader_id;
	GLuint fragment_shader_id;
	GLuint program_id;

protected:
	GLuint modelview_matrix_handle;
	GLuint projection_matrix_handle;
	GLuint normal_matrix_handle;
	GLuint mvp_handle;
	GLuint size_handle;
	GLuint time_handle;


	bool LoadShader(const char * file_name, GLuint shader_id);

private:
	typedef Shader super;
};
