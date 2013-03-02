#include "Cube.h"

Cube::Cube(vec3 matAmbient, vec3 matDiffuse) : Object(matAmbient, matDiffuse) {}

bool Cube::init() {
	// first, check for entry errors
	if (Utils::GLReturnedError("Cube::init - Error on entry"))
		return false;

	initVertices();

	// get handle for whole bundle
	glGenVertexArrays(1, &vertexArrayHandle);
	glBindVertexArray(vertexArrayHandle);

	// allocate a GPU buffer
	glGenBuffers(1, &vertexBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData), &vertices[0], GL_STATIC_DRAW);

	// setup buffer layout
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*) sizeof(vec3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*) (2 * sizeof(vec3)));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*) (3 * sizeof(vec3)));

	// enable vertex attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	// unbind vertex and buffer handles
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// check for exit errors
	if (Utils::GLReturnedError("Cube::init - Error on entry"))
		return false;

	return true;
}

void Cube::initVertices() {
	// front face
	vertices.push_back(VertexData(vec3(-0.5f, -0.5f, 0.5f), color, vec3(0, 0, 1.0f)));
	vertices.push_back(VertexData(vec3(0.5f, -0.5f, 0.5f), color, vec3(0, 0, 1.0f)));
	vertices.push_back(VertexData(vec3(-0.5f, 0.5f, 0.5f), color, vec3(0, 0, 1.0f)));
	vertices.push_back(VertexData(vec3(0.5f, -0.5f, 0.5f), color, vec3(0, 0, 1.0f)));
	vertices.push_back(VertexData(vec3(0.5f, 0.5f, 0.5f), color, vec3(0, 0, 1.0f)));
	vertices.push_back(VertexData(vec3(-0.5f, 0.5f, 0.5f), color, vec3(0, 0, 1.0f)));

	// back face
	vertices.push_back(VertexData(vec3(-0.5f, -0.5f, -0.5f), color, vec3(0, 0, -1.0f)));
	vertices.push_back(VertexData(vec3(-0.5f, 0.5f, -0.5f), color, vec3(0, 0, -1.0f)));
	vertices.push_back(VertexData(vec3(0.5f, -0.5f, -0.5f), color, vec3(0, 0, -1.0f)));
	vertices.push_back(VertexData(vec3(0.5f, -0.5f, -0.5f), color, vec3(0, 0, -1.0f)));
	vertices.push_back(VertexData(vec3(-0.5f, 0.5f, -0.5f), color, vec3(0, 0, -1.0f)));
	vertices.push_back(VertexData(vec3(0.5f, 0.5f, -0.5f), color, vec3(0, 0, -1.0f)));

	// top face
	vertices.push_back(VertexData(vec3(-0.5f, 0.5f, 0.5f), color, vec3(0, 1.0f, 0)));
	vertices.push_back(VertexData(vec3(0.5f, 0.5f, 0.5f), color, vec3(0, 1.0f, 0)));
	vertices.push_back(VertexData(vec3(-0.5f, 0.5f, -0.5f), color, vec3(0, 1.0f, 0)));
	vertices.push_back(VertexData(vec3(0.5f, 0.5f, 0.5f), color, vec3(0, 1.0f, 0)));
	vertices.push_back(VertexData(vec3(0.5f, 0.5f, -0.5f), color, vec3(0, 1.0f, 0)));
	vertices.push_back(VertexData(vec3(-0.5f, 0.5f, -0.5f), color, vec3(0, 1.0f, 0)));

	// bottom face
	vertices.push_back(VertexData(vec3(-0.5f, -0.5f, 0.5f), color, vec3(0, -1.0f, 0)));
	vertices.push_back(VertexData(vec3(-0.5f, -0.5f, -0.5f), color, vec3(0, -1.0f, 0)));
	vertices.push_back(VertexData(vec3(0.5f, -0.5f, 0.5f), color, vec3(0, -1.0f, 0)));
	vertices.push_back(VertexData(vec3(0.5f, -0.5f, 0.5f), color, vec3(0, -1.0f, 0)));
	vertices.push_back(VertexData(vec3(-0.5f, -0.5f, -0.5f), color, vec3(0, -1.0f, 0)));
	vertices.push_back(VertexData(vec3(0.5f, -0.5f, -0.5f), color, vec3(0, -1.0f, 0)));

	// right face
	vertices.push_back(VertexData(vec3(0.5f, -0.5f, 0.5f), color, vec3(1.0f, 0, 0)));
	vertices.push_back(VertexData(vec3(0.5f, -0.5f, -0.5f), color, vec3(1.0f, 0, 0)));
	vertices.push_back(VertexData(vec3(0.5f, 0.5f, -0.5f), color, vec3(1.0f, 0, 0)));
	vertices.push_back(VertexData(vec3(0.5f, -0.5f, 0.5f), color, vec3(1.0f, 0, 0)));
	vertices.push_back(VertexData(vec3(0.5f, 0.5f, -0.5f), color, vec3(1.0f, 0, 0)));
	vertices.push_back(VertexData(vec3(0.5f, 0.5f, 0.5f), color, vec3(1.0f, 0, 0)));

	// left face
	vertices.push_back(VertexData(vec3(-0.5f, -0.5f, 0.5f), color, vec3(-1.0f, 0, 0)));
	vertices.push_back(VertexData(vec3(-0.5f, 0.5f, -0.5f), color, vec3(-1.0f, 0, 0)));
	vertices.push_back(VertexData(vec3(-0.5f, -0.5f, -0.5f), color, vec3(-1.0f, 0, 0)));
	vertices.push_back(VertexData(vec3(-0.5f, -0.5f, 0.5f), color, vec3(-1.0f, 0, 0)));
	vertices.push_back(VertexData(vec3(-0.5f, 0.5f, 0.5f), color, vec3(-1.0f, 0, 0)));
	vertices.push_back(VertexData(vec3(-0.5f, 0.5f, -0.5f), color, vec3(-1.0f, 0, 0)));
}

bool Cube::draw(Shader &shader, mat4 &mv, const mat4 &proj) {
	// first, check for entry errors
	if (Utils::GLReturnedError("Cube::init - Error on entry"))
		return false;

	mat4 mvp = proj * mv;
	shader.use();
	shader.setUniform("mvMat", mv);
	shader.setUniform("projMat", proj);
	shader.setUniform("normalMat", transpose(inverse(mv)));
	shader.setUniform("mvp", mvp);
	shader.setUniform("Kd", materialDiffuse);
	shader.setUniform("Ka", materialAmbient);

	glBindVertexArray(vertexArrayHandle);

	if (Mesh::drawPoints)
		glDrawArrays(GL_POINTS, 0, vertices.size());
	else
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glBindVertexArray(0);
	
	// check for exit errors
	if (Utils::GLReturnedError("Cube::init - Error on entry"))
		return false;

	return true;
}


