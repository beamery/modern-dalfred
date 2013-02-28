#include "Triangle.h"

Triangle::Triangle() {

}

bool Triangle::init() {

	// check errors before initialization
	if (Utils::GLReturnedError("Triangle::init - Error on entry"))
		return false;

	// put three vertices in the triangle
	vertices.push_back(VertexData(vec3(-1.0f, -1.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f)));
	vertices.push_back(VertexData(vec3(1.0f, -1.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f)));
	vertices.push_back(VertexData(vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f)));

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	// Get handle for the entire bundle
	glGenVertexArrays(1, &vertexArrayHandle);
	glBindVertexArray(vertexArrayHandle);

	// Generate and move buffer data
	glGenBuffers(1, &vertexBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(VertexData), &this->vertices[0], GL_STATIC_DRAW);

	// Specify buffer layout
	glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(VertexData), (GLvoid*) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, FALSE, sizeof(VertexData), (GLvoid*) sizeof(vec3));
	glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(VertexData), (GLvoid*) (2 * sizeof(vec3)));

	// Enable the attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// Unbind the buffer and vertex array
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// check errors which occurred in the initialization
	if (Utils::GLReturnedError("Triangle::init - Error on entry"))
		return false;

	return true;
}

bool Triangle::draw(Shader &shader, mat4 &mv, const mat4 &proj, const ivec2 &size, const float time) {
	if (Utils::GLReturnedError("Triangle::draw - Error on entry"))
		return false;
	mv = rotate(mv, time * 90.0f, vec3(0.0f, 1.0f, 0.0f));

	mat4 mvp = proj * mv;
	shader.use();
	shader.setUniform("mvp", mvp);
	shader.setUniform("time", time);
	shader.setUniform("size", size);

	glBindVertexArray(vertexArrayHandle);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, &this->indices[0]); 
	//glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glUseProgram(0);
	glBindVertexArray(0);

	if (Utils::GLReturnedError("Triangle::draw - Error on exit"))
		return false;

	return true;
}

void Triangle::takeDown() {

}

