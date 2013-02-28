#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexData.h"
#include "Utils.h"
#include "Shader.h"

using namespace std;
using namespace glm;

class Mesh {

public:	
	Mesh();
	bool init(vector<VertexData> &verts, int rows, int cols);
	bool draw(Shader &shader, mat4 &mv, const mat4 &proj);
	void takeDown();

	static bool drawPoints;

private:
	vec3 calcNormFromTriangle(int i1, int i2, int i3, vector<VertexData> &verts);
	vec3 getAveragedNormal(vector<vec3> norms);
	void initVertexData(vector<VertexData> &verts, int rows, int cols);
	GLuint vertexArrayHandle;
	GLuint vertexBufferHandle;
	GLuint flatShadedVertexArrayHandle;
	GLuint flatShadedVertexBufferHandle;
	vector<VertexData> vertices;
	vector<VertexData> flatShadedVerts;
	vector<GLuint> indices;
};

/*
 * Kind of hacky struct that is used solely to aid in putting the smooth norms
 * into the vertices vector after calculating averaged norm from the flat norms.
 */
struct IndexedNorm {
	vector<int> indices;
	vector<vec3> norms;
};


#endif