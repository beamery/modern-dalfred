#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {
	delete grid;
}


void Scene::init() {
	grid = new Grid(GRID_SIZE);	
	cube.init();
	t.init();
	lightPos = vec4(0.0f, 3.0f, 0.0f, 0.0f);
	lightDiffuse = vec3(1.0f, 1.0f, 1.0f);
}


void Scene::draw(Shader &shader, MatrixStack &mvs, const mat4 &proj, 
				 const ivec2 &size, const float time) {
	shader.use();
	//shader.setUniform("time", time);
	//shader.setUniform("size", size);
	shader.setUniform("lightPosition", lightPos);
	shader.setUniform("Ld", lightDiffuse);

	mvs.push();

	mvs.active = scale(mvs.active, vec3(WORLD_UNITS_PER_METER, WORLD_UNITS_PER_METER, WORLD_UNITS_PER_METER));

	grid->draw(shader, mvs.active, proj);

	mvs.active = translate(mvs.active, vec3(0.0f, 2.0f, -5.0f));
	mvs.active = rotate(mvs.active, time * 20, vec3(0.0f, 1.0f, 0.0f));
	mvs.active = rotate(mvs.active, 45.0f, vec3(1.0f, 1.0f, 0.0f));
	cube.draw(shader, mvs.active, proj);
	//t.draw(shader, mvs.active, proj, size, time);

	mvs.pop();
}

