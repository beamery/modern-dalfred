#include "Grid.h"

/*
 * Holds a grid, to be used as a floor (or terrain). Grid is modeled in meters
 */
Grid::Grid(int size) {

	materialDiffuse = vec3(0.6f, 0.8f, 0.6f);
	materialAmbient = vec3(0.6f, 0.8f, 0.6f);
	
	// center the grid when drawn
	for (float i = -size / 2.0f; i < size / 2.0f; i++) {
		for (float j = -size / 2.0f; j < size / 2.0f; j++) {
			data.push_back(VertexData(vec3(j, float(rand()) / RAND_MAX, i), vec3(0.8f, 0.8f, 0.8f), vec3(0, 1, 0)));	
		}
	}
	mesh.init(data, size, size);
}

bool Grid::draw(Shader &shader, mat4 &mv, const mat4 &proj) {

	shader.setUniform("Kd", materialDiffuse);
	shader.setUniform("Ka", materialAmbient);
	return mesh.draw(shader, mv, proj);
}
