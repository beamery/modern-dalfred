#include "Scene.h"

/*
 * Initializes the ambient, diffuse, and specular components of the scene's objects
 * as well as setting the specular hotspot size (smaller number = wider hotspot).
 * Also initialize the lights for the scene as well as their ADS components.
 */
Scene::Scene() : 
	cube(vec3(0.0f, 0.8f, 0.8f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f), 20.0f),
	grid(vec3(0.6f, 0.8f, 0.6f), vec3(0.6f, 0.8f, 0.6f), vec3(0.4f, 0.8f, 0.4f), 15.0f),
	sDisk(vec3(0.0f, 0.8f, 0.8f), vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, 1.0f, 1.0f), 40.0f)	
{
	lightPos = vec4(0.0f, 20.0f, 0.0f, 0.0f);
	lightDiffuse = vec3(0.4f, 0.4f, 0.4f);
	lightAmbient = vec3(0.2f, 0.2f, 0.2f);
	lightSpecular = vec3(0.4f, 0.4f, 0.4f);
}

/*
 * Release any pointers allocated for the scene
 */
Scene::~Scene() {
}


/*
 * Initialize the meshes for the objects in the scene.
 */
void Scene::init() {
	grid.init(GRID_SIZE);
	cube.init();
	sDisk.init(1.0f, 2.0f, 10, 1.0f);

}


void Scene::draw(Shader &shader, MatrixStack &mvs, const mat4 &proj, 
				 const ivec2 &size, const float time) {
	shader.use();
	//shader.setUniform("time", time);
	//shader.setUniform("size", size);

	mvs.push();

	mvs.active = scale(mvs.active, vec3(WORLD_UNITS_PER_METER, WORLD_UNITS_PER_METER, WORLD_UNITS_PER_METER));
	mvs.push();
	//mvs.active = rotate(mvs.active, 20 * time, vec3(1.0f, 0.0f, 0.0f));
	vec4 eyeLightPos = mvs.active * lightPos;
	mvs.pop();
	//mvs.active = rotate(mvs.active, 10 * time, vec3(0.0f, 1.0f, 0.0f));

	// push the light properties to the shader
	shader.setUniform("lightPosition", eyeLightPos);
	shader.setUniform("Ld", lightDiffuse);
	shader.setUniform("La", lightAmbient);
	shader.setUniform("Ls", lightSpecular);

	// draw the grid in meters
	grid.draw(shader, mvs.active, proj);

	// perform transforms on scene objects
	mvs.active = translate(mvs.active, vec3(0.0f, 12.0f, -5.0f));
	mvs.active = rotate(mvs.active, 30 * sin(time), vec3(1.0f, 0.0f, 1.0f));
	//mvs.active = rotate(mvs.active, -45.0f * time, vec3(0.0f, 1.0f, 0.0f));
	//mvs.active = rotate(mvs.active, 45.0f, vec3(1.0f, 1.0f, 1.0f));
	mvs.active = translate(mvs.active, vec3(0.0f, -10.0f, 0.0f));

	// draw scene objects
	cube.draw(shader, mvs.active, proj);
	sDisk.draw(shader, mvs.active, proj);

	mvs.pop();
}

void Scene::moveLight(float x, float z) {
	lightPos.z += z;
	lightPos.x += x;
}


