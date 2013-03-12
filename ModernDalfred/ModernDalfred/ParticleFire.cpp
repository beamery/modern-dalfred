#include "ParticleFire.h"

ParticleFire::ParticleFire(int numParticles) :
	ParticleEmitter(numParticles, 25.0f, FIRE_PARTICLE_LIFETIME, "fire", vec3(0.0f, 0.1f, 0.0f)) {

	vec3 vel(0.0f);
	vec3 pos(0.0f);
	float initVel, initX;
	float time = 0.0f, rate = 0.00550f;
	for (int i = 0; i < numParticles; i++) {

		// get initial position
		initX = mix(-1.0f, 1.0f, float(rand()) / RAND_MAX);
		pos = vec3(initX, 0.0f, 0.0f);

		// get initial velocity
		initVel = mix(0.05f, 0.5f, float(rand()) / RAND_MAX);
		vel = vec3(0.0f, initVel, 0.0f);

		positions.push_back(pos);
		velocities.push_back(vel);
		startTimes.push_back(time);
		time += rate;
	}
}

void ParticleFire::update(float elapsedTime) {

}
