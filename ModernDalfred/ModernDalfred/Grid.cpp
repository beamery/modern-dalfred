#include "Grid.h"

Grid::Grid(int size) {
	
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			data.push_back(VertexData(vec3(j, i, 0), vec3(0.8f, 0.8f, 0.8f), vec3(0, 0, 0)));	
		}
	}
	mesh.init(data, size, size);
}

bool Grid::draw(Shader &shader, MatrixStack &mvs, const mat4 &proj) {

	return mesh.draw(shader, mvs.active, proj);
}
