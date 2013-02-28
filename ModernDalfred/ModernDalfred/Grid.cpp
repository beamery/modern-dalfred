#include "Grid.h"

/*
 * Holds a grid, to be used as a floor (or terrain). Grid is modeled in meters
 */
Grid::Grid(int size) {

	materialDiffuse = vec3(0.4f, 0.6f, 0.4f);
	
	// center the grid when drawn
	for (float i = -size / 2.0f; i < size / 2.0f; i++) {
		for (float j = -size / 2.0f; j < size / 2.0f; j++) {
			data.push_back(VertexData(vec3(j, 0, i), vec3(0.8f, 0.8f, 0.8f), vec3(0, 1, 0)));	
		}
	}
	mesh.init(data, size, size);
}

bool Grid::draw(Shader &shader, mat4 &mv, const mat4 &proj) {

	shader.setUniform("Kd", materialDiffuse);
	return mesh.draw(shader, mv, proj);
}
