#include "ParticleFountain.h"

ParticleFountain::ParticleFountain(int numParticles) {
	
	vec3 vel(0.0f);
	float velocity, theta, phi;
	float time = 0.0f, rate = 0.00020f;
	for (int i = 0; i < numParticles; i++) {

		// get the direction of the initial velocity
		theta = mix(0.0f, PI / 6.0f, float(rand()) / RAND_MAX);
		phi = mix(0.0f, 2.0f * PI, float(rand()) / RAND_MAX);
		vel.x = sinf(theta) * cosf(phi);
		vel.y = cosf(theta);
		vel.z = sinf(theta) * sinf(phi);

		// scale to get the magnitude of the initial velocity
		velocity = mix(1.25f, 1.5f, float(rand() / RAND_MAX));
		vel = vel * velocity;

		// push back the particle with the given velocity and start time
		particles.push_back(ParticleData(vel, time));
		time += rate;
	}
}

// initialize OpenGL buffers for this particle fountain
bool ParticleFountain::initGL() {
	if (Utils::GLReturnedError("ParticleFountain::initGL - on entry")) return false;

	// generate handle for whole bundle
	glGenVertexArrays(1, &vertexArrayHandle);
	glBindVertexArray(vertexArrayHandle);

	// initialize graphics memory locations
	glGenBuffers(1, &vertexBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(ParticleData), &particles[0], GL_STATIC_DRAW);

	// initial velocity
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleData), 0);
	// start time
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleData), (void*) sizeof(vec3));

	// enable the channels
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	// unbind handles
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	if (Utils::GLReturnedError("ParticleFountain::initGL - on exit")) return false;

	return true;
}


void ParticleFountain::update(float elapsedTime) {

}

bool ParticleFountain::draw(Shader &shader, MatrixStack &mvs, mat4 proj, float elapsedTime) {
	if (Utils::GLReturnedError("ParticleFountain::draw - on entry")) return false;

	// set up fountain drawing
	//glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(3.0f);

	mat4 mvp = proj * mvs.active;
	shader.use();
	shader.setUniform("time", elapsedTime);
	shader.setUniform("particleLifetime", PARTICLE_LIFETIME);
	shader.setUniform("mvp", mvp);

	glBindVertexArray(vertexArrayHandle);
	glDrawArrays(GL_POINTS, 0, particles.size());

	// take down fountain setup
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glBindVertexArray(0);

	if (Utils::GLReturnedError("ParticleFountain::draw - on exit")) return false;
	return true;
}

