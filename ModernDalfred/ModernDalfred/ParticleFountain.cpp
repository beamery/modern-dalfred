#include "ParticleFountain.h"

ParticleFountain::ParticleFountain(int numParticles) {
	
	vec3 vel(0.0f);
	float velocity, theta, phi;
	float time = 0.0f, rate = 0.00075f;
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
//		particles.push_back(ParticleData(vel, time));
		positions.push_back(vec3(0,0,0));
		velocities.push_back(vel);
		startTimes.push_back(time);
		time += rate;
	}

}

// initialize OpenGL buffers for this particle fountain
bool ParticleFountain::initGL() {
	if (Utils::GLReturnedError("ParticleFountain::initGL - on entry")) return false;

	// generate handles for whole bundle
	glGenVertexArrays(2, particleArray);

	// generate two buffers for each attribute (to be used with transform feedback)
	glGenBuffers(2, posBuf);
	glGenBuffers(2, velBuf);
	glGenBuffers(2, startBuf);

	// set up bundles 0 and 1
	for (int i = 0; i < 2; i++) {
		// bind bundle
		glBindVertexArray(particleArray[i]);

		// set up position buffer
		glBindBuffer(GL_ARRAY_BUFFER, posBuf[i]);
		glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(vec3), &positions[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);

		// set up velocity buffer
		glBindBuffer(GL_ARRAY_BUFFER, velBuf[i]);
		glBufferData(GL_ARRAY_BUFFER, velocities.size() * sizeof(vec3), &velocities[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);

		// set up start time buffer
		glBindBuffer(GL_ARRAY_BUFFER, startBuf[i]);
		glBufferData(GL_ARRAY_BUFFER, startTimes.size() * sizeof(GLfloat), &startTimes[0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float), 0);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
	}

	// unbind handles
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// set up transform feedback objects
	glGenTransformFeedbacks(2, feedback);

	// transform feedback 0 and 1
	for (int i = 0; i < 2; i++) {
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedback[i]);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, posBuf[i]);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, velBuf[i]);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, startBuf[i]);
	}

	
	/*
	glGenVertexArrays(1, &vertexArrayHandle);
	glBindVertexArray(vertexArrayHandle);
	glGenBuffers(1, &vertexBufferHandle);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(ParticleData), &particles[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleData), 0);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleData), (void*) sizeof(vec3));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	*/

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

	glBindVertexArray(particleArray[1]);
	//glBindVertexArray(vertexArrayHandle);
	//glDrawArrays(GL_POINTS, 0, particles.size());
	glDrawArrays(GL_POINTS, 0, positions.size());

	// take down fountain setup
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glBindVertexArray(0);

	if (Utils::GLReturnedError("ParticleFountain::draw - on exit")) return false;
	return true;
}

