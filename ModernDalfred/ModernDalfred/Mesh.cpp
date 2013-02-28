#include "Mesh.h"

Mesh::Mesh() {}

bool Mesh::init(vector<VertexData> &verts, int rows, int cols) {

	initVertexData(verts, rows, cols);

	//vector<VertexData> herpDerp;
	//herpDerp.push_back(VertexData(vec3(-1.0f, -1.0f, 0.0f), vec3(1, 1, 1), vec3(0, 0, 1)));
	//herpDerp.push_back(VertexData(vec3(1.0f, -1.0f, 0.0f), vec3(1, 1, 1), vec3(0, 0, 1)));
	//herpDerp.push_back(VertexData(vec3(0.0f, 1.0f, 0.0f), vec3(1, 1, 1), vec3(0, 0, 1)));
	//vertices = herpDerp;

	// first, check for entry errors
	if (Utils::GLReturnedError("Mesh::init - Error on entry"))
		return false;

	// initialize vertex array
	glGenVertexArrays(1, &vertexArrayHandle);
	glBindVertexArray(vertexArrayHandle);

	// intialize array buffer
	glGenBuffers(1, &vertexBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData), &vertices[0], GL_STATIC_DRAW);

	// logical setup of array buffer
	// channel 0 - vertex geometry
	// channel 1 - vertex color
	// channel 2 - vertex normal
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), 0);	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*) sizeof(vec3));	
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*) (2 * sizeof(vec3)));	

	// enable the channels
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// unbind the buffer and vertex array
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//////// Repeat the process for the flat-shaded vertices /////////

	// initialize vertex array
	glGenVertexArrays(1, &flatShadedVertexArrayHandle);
	glBindVertexArray(flatShadedVertexArrayHandle);

	// intialize array buffer
	glGenBuffers(1, &flatShadedVertexBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, flatShadedVertexBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, flatShadedVerts.size() * sizeof(VertexData), &flatShadedVerts[0], GL_STATIC_DRAW);

	// logical setup of array buffer
	// channel 0 - vertex geometry
	// channel 1 - vertex color
	// channel 2 - vertex normal
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), 0);	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*) sizeof(vec3));	
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*) (2 * sizeof(vec3)));	

	// enable the channels
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// unbind the buffer and vertex array
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// check for exit errors
	if (Utils::GLReturnedError("Mesh::init - Error on exit"))
		return false;

	return true;
}

/**
 * Convert the grid into something useful to GL. This handles most of the
 * heavy lifting for the Mesh class.
 *
 * The grid must go from left to right, bottom to top, according the the
 * outside of the mesh.
 *
 *  a  b  c
 *  *--*--*
 *  |\ |\ |
 *  |d\|e\|f
 *  *--*--*
 *  |\ |\ |
 *  | \| \|
 *  *--*--*
 *  g  h  i
 *
 */
void Mesh::initVertexData(vector<VertexData> &verts, int rows, int cols) {
	vector<IndexedNorm> smoothNorms(verts.size());

	// number of rows - 1 so that we don't run out of bounds
	for (int y = 0; y < rows - 1; y++) {
		for (int x = 0; x < cols; x++) {
			int curIdx = (cols * y) + x;
			int upIdx = (cols * (y+1)) + x;
			int upLeftIdx = (cols * (y+1)) + x-1;
			int rightIdx = (cols * (y)) + x+1;
			
			// if we are at any col but the first, construct the previous triangle
			if (x != 0) {
				// get the flat-shaded normal for this triangle
				vec3 flatNorm = calcNormFromTriangle(curIdx, upIdx, upLeftIdx, verts);

				// Initially push back the index of this vertex so that we can come
				// back later and put the correct averaged normal into the vertices vector.
				// Also put in the flat norm of this triangle to allow us to calculate the 
				// averaged normal

				// current (x, y)
				smoothNorms[curIdx].indices.push_back(flatShadedVerts.size());
				smoothNorms[curIdx].norms.push_back(flatNorm);

				// Push back the vertices in the correct order for this mesh (into each vector).
				// We'll come back later and give 'vertices' the correct normals
				flatShadedVerts.push_back(VertexData(verts[curIdx].position, verts[curIdx].color, flatNorm));
				vertices.push_back(VertexData(verts[curIdx].position, verts[curIdx].color, flatNorm));
				
				// up (x, y+1)
				smoothNorms[upIdx].indices.push_back(flatShadedVerts.size());
				smoothNorms[upIdx].norms.push_back(flatNorm);
				flatShadedVerts.push_back(VertexData(verts[upIdx].position, verts[upIdx].color, flatNorm));
				vertices.push_back(VertexData(verts[upIdx].position, verts[upIdx].color, flatNorm));

				// up and left (x-1, y+1)
				smoothNorms[upLeftIdx].indices.push_back(flatShadedVerts.size());
				smoothNorms[upLeftIdx].norms.push_back(flatNorm);
				flatShadedVerts.push_back(VertexData(verts[upLeftIdx].position, verts[upLeftIdx].color, flatNorm));
				vertices.push_back(VertexData(verts[upLeftIdx].position, verts[upLeftIdx].color, flatNorm));

			}

			// if we are at any col but the last, construct the following triangle
			if (x != cols - 1) {
				// get the flat-shaded normal for this triangle
				vec3 flatNorm = calcNormFromTriangle(curIdx, rightIdx, upIdx, verts);

				// current (x, y)
				smoothNorms[curIdx].indices.push_back(flatShadedVerts.size());
				smoothNorms[curIdx].norms.push_back(flatNorm);
				flatShadedVerts.push_back(VertexData(verts[curIdx].position, verts[curIdx].color, flatNorm));
				vertices.push_back(VertexData(verts[curIdx].position, verts[curIdx].color, flatNorm));

				// right (x+1, y)
				smoothNorms[rightIdx].indices.push_back(flatShadedVerts.size());
				smoothNorms[rightIdx].norms.push_back(flatNorm);
				flatShadedVerts.push_back(VertexData(verts[rightIdx].position, verts[rightIdx].color, flatNorm));
				vertices.push_back(VertexData(verts[rightIdx].position, verts[rightIdx].color, flatNorm));

				// up (x, y+1)
				smoothNorms[upIdx].indices.push_back(flatShadedVerts.size());
				smoothNorms[upIdx].norms.push_back(flatNorm);
				flatShadedVerts.push_back(VertexData(verts[upIdx].position, verts[upIdx].color, flatNorm));
				vertices.push_back(VertexData(verts[upIdx].position, verts[upIdx].color, flatNorm));

			}

		}

		// Go through and give 'vertices' the correct normals
		for (auto i = smoothNorms.begin(); i != smoothNorms.end(); i++) {
			vec3 normal = getAveragedNormal(i->norms);
			for (auto j = i->indices.begin(); j != i->indices.end(); j++) {
				vertices[*j].normal = normal;
			}
		}
	}

	//for (auto i = vertices.begin(); i != vertices.end(); i++) {
	//	vec3 pos = i->position;
	//	cout << "(" << pos.x << ", " << pos.y << ", " << pos.z << ")" << endl;
	//}

}


bool Mesh::draw(Shader &shader, mat4 &mv, const mat4 &proj) {
	// first, check for entry errors
	if (Utils::GLReturnedError("Mesh::init - Error on entry"))
		return false;

	mat4 mvp = proj * mv;

	shader.use();
	shader.setUniform("mvp", mvp);

	//glBindVertexArray(this->vertexArrayHandle);
	glBindVertexArray(this->flatShadedVertexArrayHandle);
	glDrawArrays(GL_POINTS, 0, vertices.size());
	//glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	// check for exit errors
	if (Utils::GLReturnedError("Mesh::init - Error on exit"))
		return false;

	return true;
}

void Mesh::takeDown() {
	if (this->vertexArrayHandle != GLuint(-1)) {
		glDeleteVertexArrays(1, &this->vertexArrayHandle);
	}

	if (this->vertexBufferHandle != GLuint(-1)) {
		glDeleteBuffers(1, &this->vertexBufferHandle);
	}

	this->vertexArrayHandle = this->vertexBufferHandle = GLuint(-1);
}

/*
 * Calculates the normal of a triangle, given its vertex indices and the 
 * vector of vertices they come from. Assumes counter-clockwise vertex winding
 * and calculates the normal by doing the following computation:
 *
 * (i2 - i1) x (i3 - i1)
 */
vec3 Mesh::calcNormFromTriangle(int i1, int i2, int i3, vector<VertexData> &verts) {
	
	vec3 v1 = verts[i1].position;
	vec3 v2 = verts[i2].position;
	vec3 v3 = verts[i3].position;
	vec3 norm = cross((v2 - v1), (v3 - v1));
	norm = normalize(norm);

	return norm;
}

/*
 * Given a list of vectors, find the average of the vectors and normalize it.
 */
vec3 Mesh::getAveragedNormal(vector<vec3> norms) {
	vec3 total(0, 0, 0);
	for (unsigned int i = 0; i < norms.size(); i++) {
		total += norms[i];
	}
	return normalize(total);
}