#include "Scene.h"

Scene::Scene() {}

void Scene::init() {
	if (!triangle.init()) {
		cerr << "Error initializing triangle" << endl;
	}
}


void Scene::draw(Shader &shader, mat4 &mv, const mat4 &proj, 
				 const ivec2 &size, const float time) {

	triangle.draw(shader, mv, proj, size, time);
}
