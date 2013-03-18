#include "Scene.h"

/*
 * Initializes the ambient, diffuse, and specular components of the scene's objects
 * as well as setting the specular hotspot size (smaller number = wider hotspot).
 * Also initialize the lights for the scene as well as their ADS components.
 */
Scene::Scene() : 
	cube(vec3(0.0f, 0.8f, 0.8f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f), 20.0f),
	grid(vec3(0.6f, 0.4f, 0.4f), vec3(0.6f, 0.4f, 0.4f), vec3(0.1f, 0.1f, 0.1f), 15.0f),
	ceiling(vec3(0.6f, 0.6f, 0.6f), vec3(0.6f, 0.6f, 0.6f), vec3(0.1f, 0.1f, 0.1f), 15.0f),
	wallFar(vec3(0.3f, 0.4f, 0.3f), vec3(0.5f, 0.6f, 0.5f), vec3(0.05f, 0.05f, 0.05f), 1.0f),
	wallLeft(vec3(0.3f, 0.4f, 0.3f), vec3(0.5f, 0.6f, 0.5f), vec3(0.05f, 0.05f, 0.05f), 1.0f),
	sDisk(vec3(0.0f, 0.8f, 0.8f), vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, 1.0f, 1.0f), 40.0f),
	torus(vec3(0.0f, 0.8f, 0.8f), vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, 1.0f, 1.0f), 40.0f),
	stoolModel(vec3(0.2f, 0.1f, 0.1f), vec3(0.3f, 0.2f, 0.2f), vec3(1.0f, 0.8f, 0.8f)),
	tableModel(vec3(0.2f, 0.1f, 0.1f), vec3(0.3f, 0.2f, 0.2f), vec3(1.0f, 0.8f, 0.8f)),
	vaseModel(vec3(0.4f, 0.5f, 0.4f), vec3(0.7f, 0.8f, 0.7f), vec3(0.3f, 0.3f, 0.3f), 
			14.0f, 2.5f, 1.0f, 2 * PI / 14.0f, 0.0f, 20, 10),
	bowl(vec3(0.4f, 0.4f, 0.5f), vec3(0.7f, 0.7f, 0.8f), vec3(0.3f, 0.3f, 0.3f),
			4.0f, 3.0f, 3.0f, 2 * PI / 14.0f, 0.0f, 20, 10),
	goblet(vec3(0.5f, 0.4f, 0.4f), vec3(0.8f, 0.7f, 0.7f), vec3(0.3f, 0.3f, 0.3f),
			6.0f, 1.5f, 1.0f, 2 * PI / 8.0f, 4.0f, 32, 10),
	fountain(10000),
	fire(3000),
	fireplace(vec3(0.0f, 0.0f, -WALL_DIST + FP_BLOCK_THICKNESS / 2 * METERS_PER_INCH), vec3(0.9f, 0.9f, 0.9f), vec3(0.9f, 0.9f, 0.9f), vec3(0.9f, 0.9f, 0.9f)),
	triangle(),
	painting("starry_night")
{
	// light position in world space
	lightPos = vec4(0.0f, 0.3f, -WALL_DIST + FP_BLOCK_THICKNESS / 2 * METERS_PER_INCH + 0.2f, 1.0f);
	lightDiffuse = vec3(0.7f, 0.5f, 0.3f);
	lightAmbient = vec3(0.1f, 0.1f, 0.1f);
	lightSpecular = vec3(0.65f, 0.5f, 0.5f);

	// add stools to surround the table
	stools.push_back(Stool(&stoolModel, vec3(0.0f, 0.0f, 30.0f)));
	stools.push_back(Stool(&stoolModel, vec3(0.0f, 0.0f, -30.0f)));
	stools.push_back(Stool(&stoolModel, vec3(30.0f, 0.0f, 0.0f)));
	stools.push_back(Stool(&stoolModel, vec3(-30.0f, 0.0f, 0.0f)));
}

/*
 * Release any pointers allocated for the scene
 */
Scene::~Scene() {
}


/*
 * Initialize the meshes for the objects in the scene.
 */
bool Scene::init() {
	bool success = stoolModel.initMesh();
	if (!success) return false;

	success = tableModel.initMesh();
	if (!success) return false;

	success = vaseModel.initMesh();
	if (!success) return false;
	
	success = bowl.initMesh();
	if (!success) return false;

	success = goblet.initMesh();
	if (!success) return false;

	success = grid.init(GRID_SIZE, GRID_SIZE);
	if (!success) return false;

	success = ceiling.init(GRID_SIZE, GRID_SIZE);
	if (!success) return false;

	success = wallFar.init(WALL_LENGTH, WALL_HEIGHT);
	if (!success) return false;

	success = wallLeft.init(WALL_HEIGHT, WALL_LENGTH);
	if (!success) return false;

	success = cube.init();
	if (!success) return false;

	success = sDisk.init(1.0f, 2.0f, 10, 1.0f);
	if (!success) return false;

	success = torus.init(4.0f, 0.5f, 20, 20);
	if (!success) return false;

	success = fountain.initGL();
	if (!success) return false;

	success = fire.initGL();
	if (!success) return false;

	success = fireplace.initMesh();
	if (!success) return false;

	success = triangle.init(); 
	if (!success) return false;

	success = painting.init(); 
	if (!success) return false;

	return true;
}


void Scene::update(float elapsedTime) {
	fountainShader->use();
	fountainShader->setUniform("elapsedTime", elapsedTime);
}


bool Scene::draw(Shader &shader, MatrixStack &mvs, const mat4 &proj, 
				 const ivec2 &size, const float time) {

	shader.use();
	shader.setUniform("time", time);
	//shader.setUniform("size", size);

	mvs.push();

	mvs.active = scale(mvs.active, vec3(WORLD_UNITS_PER_METER, WORLD_UNITS_PER_METER, WORLD_UNITS_PER_METER));
	mvs.push();
	//mvs.active = rotate(mvs.active, 20 * time, vec3(1.0f, 0.0f, 0.0f));
	vec4 eyeLightPos = mvs.active * lightPos;
	mvs.pop();
	//mvs.active = rotate(mvs.active, 10 * time, vec3(0.0f, 1.0f, 0.0f));

	// on random intervals change the light color slightly to emulate the
	// flickering of light given off by flames
	if (rand() % 10 < 5) {
		adjLightAmb = lightAmbient;
		adjLightDiff = lightDiffuse;
		adjLightSpec = lightSpecular;

		float adjustment = mix(-0.02f, 0.02f, float(rand()) / RAND_MAX);
		adjLightAmb += adjustment;
		adjLightDiff += adjustment;
		adjLightSpec += adjustment;
	}


	// push the light properties to the shader
	shader.setUniform("lightPosition", eyeLightPos);
	shader.setUniform("La", adjLightAmb);
	shader.setUniform("Ld", adjLightDiff);
	shader.setUniform("Ls", adjLightSpec);

	// push light properties to the texture shader
	textureShader->use();
	textureShader->setUniform("lightPosition", eyeLightPos);
	textureShader->setUniform("Ld", lightDiffuse);
	textureShader->setUniform("La", lightAmbient);
	textureShader->setUniform("Ls", lightSpecular);

	// draw the grid in meters
	grid.draw(shader, mvs.active, proj);

	// draw a ceiling
	mvs.push();
	mvs.active = translate(mvs.active, vec3(0.0f, WALL_HEIGHT - 1, 0.0f));
	mvs.active = rotate(mvs.active, 180.0f, vec3(1.0f, 0.0f, 0.0f));
	ceiling.draw(shader, mvs.active, proj);
	mvs.pop();

	// transform far wall and draw it
	mvs.push();
	mvs.active = translate(mvs.active, vec3(0.0f, 0.0f, -WALL_DIST));
	mvs.active = translate(mvs.active, vec3(0.0f, WALL_HEIGHT / 2.0f, 0.0f));
	mvs.active = rotate(mvs.active, 90.0f, vec3(1.0f, 0.0f, 0.0f));
	wallFar.draw(shader, mvs.active, proj);
	mvs.pop();

	// transform near wall and draw it
	mvs.push();
	mvs.active = rotate(mvs.active, 180.0f, vec3(0.0f, 1.0f, 0.0f));
	mvs.active = translate(mvs.active, vec3(0.0f, 0.0f, -WALL_DIST));
	mvs.active = translate(mvs.active, vec3(0.0f, WALL_HEIGHT / 2.0f, 0.0f));
	mvs.active = rotate(mvs.active, 90.0f, vec3(1.0f, 0.0f, 0.0f));
	wallFar.draw(shader, mvs.active, proj);
	mvs.pop();

	// draw fireplace
	fireplace.draw(*textureShader, mvs, proj, time);

	mvs.push();
	mvs.active = translate(mvs.active, vec3(-WALL_DIST + 0.001f, 1.5f, -1.5f));
	mvs.active = rotate(mvs.active, 90.0f, vec3(0.0f, 1.0f, 0.0f));
	mvs.active = scale(mvs.active, vec3(1.28f * 1.5f, 1.014f * 1.5f, 1.0f));
	painting.draw(*textureShader, mvs, proj);
	mvs.pop();

	// transform right wall and draw it
	mvs.push();
	mvs.active = translate(mvs.active, vec3(WALL_DIST, 0.0f, 0.0f));
	mvs.active = translate(mvs.active, vec3(0.0f, WALL_HEIGHT / 2.0f, 0.0f));
	mvs.active = rotate(mvs.active, 90.0f, vec3(0.0f, 0.0f, 1.0f));
	wallLeft.draw(shader, mvs.active, proj);
	mvs.pop();

	// transform left wall and draw it
	mvs.push();
	mvs.active = rotate(mvs.active, 180.0f, vec3(0.0f, 1.0f, 0.0f));
	mvs.active = translate(mvs.active, vec3(WALL_DIST, 0.0f, 0.0f));
	mvs.active = translate(mvs.active, vec3(0.0f, WALL_HEIGHT / 2.0f, 0.0f));
	mvs.active = rotate(mvs.active, 90.0f, vec3(0.0f, 0.0f, 1.0f));
	wallLeft.draw(shader, mvs.active, proj);
	mvs.pop();

	//triangle.draw(*textureShader, mvs, proj, size, time);

	// draw fountain - DEBUGGING
	//fountain.draw(*fountainShader, mvs, proj, time);

	//mvs.active = translate(mvs.active, vec3(0.0f, 1.0f, 0.0f));
	//torus.draw(shader, mvs.active, proj);
	//sDisk.draw(shader, mvs.active, proj);

	// perform transforms on scene objects
	//mvs.active = translate(mvs.active, vec3(0.0f, 12.0f, 0.0f));
	//mvs.active = rotate(mvs.active, 30 * sin(time), vec3(1.0f, 0.0f, 1.0f));
	//mvs.active = rotate(mvs.active, -45.0f * time, vec3(0.0f, 1.0f, 0.0f));
	//mvs.active = rotate(mvs.active, 45.0f, vec3(1.0f, 1.0f, 1.0f));
	//mvs.active = translate(mvs.active, vec3(0.0f, -10.0f, 0.0f));

	// draw scene objects
	bool success = true;
	//cube.draw(shader, mvs.active, proj);
	//sDisk.draw(shader, mvs.active, proj);

	// scale stools down to inches
	mvs.active = scale(mvs.active, vec3(METERS_PER_INCH, METERS_PER_INCH, METERS_PER_INCH));

	// draw stools
	for (auto i = stools.begin(); i != stools.end(); i++) {
		success = i->draw(shader, mvs, proj);
		if (!success) return false;
	}

	// draw table
	success = tableModel.draw(shader, mvs, proj);
	if (!success) return false;

	// draw vase
	mvs.active = translate(mvs.active, vec3(0.0f, TABLE_HEIGHT, 0.0f));
	mvs.push();
	mvs.active = translate(mvs.active, vec3(12.0f, 0.0f, 6.0f));
	success = vaseModel.draw(shader, mvs, proj);	
	if (!success) return false;
	mvs.pop();
	// draw bowl
	mvs.push();
	mvs.active = translate(mvs.active, vec3(-10.0f, 0.0f, -5.0f));
	success = bowl.draw(shader, mvs, proj);	
	if (!success) return false;
	mvs.pop();
	// draw goblet
	mvs.push();
	mvs.active = translate(mvs.active, vec3(-6.0f, 0.0f, 8.0f));
	success = goblet.draw(shader, mvs, proj);	
	if (!success) return false;
	mvs.pop();

	// scale back up to meters and draw particle fountain
	//mvs.active = translate(mvs.active, vec3(0.0f, 15.0f, 0.0f));
	//mvs.active = scale(mvs.active, vec3(1 / METERS_PER_INCH, 1 / METERS_PER_INCH, 1 / METERS_PER_INCH));
	//success = fountain.draw(*fountainShader, mvs, proj, time);
	//if (!success) return false;

	mvs.pop();


	
	return true;
}

void Scene::moveLight(float x, float z) {
	lightPos.z += z;
	lightPos.x += x;
}

void Scene::adjustStoolHeight(float amount) {
	stoolModel.adjustHeight(amount);
}


void Scene::setFountainShader(ParticleShader *shader) {
	fountainShader = shader;	
	fireplace.setFireShader(shader);
}

void Scene::setTextureShader(Shader *shader) {
	textureShader = shader;	
}