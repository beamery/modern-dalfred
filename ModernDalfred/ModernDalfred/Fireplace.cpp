#include "Fireplace.h"

Fireplace::Fireplace(vec3 pos, vec3 ambient, vec3 diff, vec3 spec) : 
	position(pos),
	cube(ambient, diff, spec, 1.0f, "brick"),
	fire(3000)
{}

bool Fireplace::initMesh() {
	if (!cube.init()) return false;
	if (!fire.initGL()) return false;

	return true;
}

bool Fireplace::draw(Shader &shader, MatrixStack &mvs, const mat4 &proj, float time) {
	mvs.push();
	bool success;

	mvs.active = translate(mvs.active, this->position);

	fire.draw(*fireShader, mvs, proj, time);

	mvs.active = scale(mvs.active, vec3(METERS_PER_INCH, METERS_PER_INCH, METERS_PER_INCH));

	// draw sides of fireplace
	success = drawSide(shader, mvs, proj, FP_WIDTH / 2 - FP_BLOCK_THICKNESS / 2);
	if (!success) return false;
	success = drawSide(shader, mvs, proj, -(FP_WIDTH / 2 - FP_BLOCK_THICKNESS / 2));
	if (!success) return false;

	// draw top of fireplace
	for (int i = 0; i < 6; i++) {
		mvs.push();
		mvs.active = translate(mvs.active, vec3(FP_BLOCK_THICKNESS * i, 0.0f, 0.0f));
		mvs.active = translate(mvs.active, 
			vec3(-(FP_WIDTH / 2 - FP_BLOCK_THICKNESS / 2), 3.5 * FP_BLOCK_THICKNESS, 0.0f));
		mvs.active = scale(mvs.active, vec3(FP_BLOCK_THICKNESS, FP_BLOCK_THICKNESS, FP_BLOCK_THICKNESS));
		cube.draw(shader, mvs.active, proj);
		mvs.pop();
	}


	// draw chimney
	for (int i = 0; i < 8; i++) {
		mvs.push();
		mvs.active = translate(mvs.active, vec3(0.0f, FP_BLOCK_THICKNESS * i, 0.0f));
		mvs.active = translate(mvs.active, 
			vec3(0.0f, FP_BLOCK_THICKNESS * 4.5, -FP_BLOCK_THICKNESS / 4));
		mvs.active = scale(mvs.active, vec3(FP_CHIMNEY_WIDTH, FP_BLOCK_THICKNESS, FP_BLOCK_THICKNESS / 2));
		cube.draw(shader, mvs.active, proj);
		mvs.pop();

	}


	mvs.pop();
	return true;
}

bool Fireplace::drawSide(Shader &shader, MatrixStack &mvs, const mat4 &proj, float xOffset) {
	mvs.push();

	mvs.active = translate(mvs.active, vec3(xOffset, 0.0f, 0.0f));

	// place the bottom of the side at 0 in the y direction
	for (int i = 0; i < 3; i++) {
		mvs.push();
		mvs.active = translate(mvs.active, vec3(0.0f, FP_BLOCK_THICKNESS / 2, 0.0f));
		mvs.active = translate(mvs.active, vec3(0.0f, FP_BLOCK_THICKNESS * i, 0.0f));
		mvs.active = scale(mvs.active, vec3(FP_BLOCK_THICKNESS, FP_BLOCK_THICKNESS, FP_BLOCK_THICKNESS));
		bool success = cube.draw(shader, mvs.active, proj);
		if (!success) return false;
		mvs.pop();
	}



	mvs.pop();
	return true;
}
