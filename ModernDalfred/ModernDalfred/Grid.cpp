#include "Grid.h"

/*
 * Holds a grid, to be used as a floor (or terrain). Grid is modeled in meters
 */
Grid::Grid(vec3 matAmbient, vec3 matDiffuse, vec3 matSpecular, float shine) : 
	mesh(matAmbient, matDiffuse, matSpecular, shine) {}

bool Grid::init(int size) {
	vector<VertexData> data;
	// center the grid when drawn
	for (float i = size / 2.0f; i >= -size / 2.0f; i--) {
		for (float j = -size / 2.0f; j < size / 2.0f; j++) {
			data.push_back(VertexData(vec3(j, float(rand()) / RAND_MAX, i), vec3(0,0,0), vec3(0, 1, 0)));	
			//data.push_back(VertexData(vec3(j, 0.0f, i), vec3(0,0,0), vec3(0, 1, 0)));	
		}
	}
	return mesh.init(data, size, size);
}


bool Grid::draw(Shader &shader, mat4 &mv, const mat4 &proj) {

	return mesh.draw(shader, mv, proj);
}
