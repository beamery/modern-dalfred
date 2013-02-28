#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {
	delete grid;
}


void Scene::init() {
	grid = new Grid(3);	
}


void Scene::draw(Shader &shader, mat4 &mv, const mat4 &proj, 
				 const ivec2 &size, const float time) {

	//triangle.draw(shader, mv, proj, size, time);
	grid->draw(shader, mv, proj);
}

