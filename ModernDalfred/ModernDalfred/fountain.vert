#version 400

// This shader is used to simulate a particle fountain. It was taken from
// the OpenGL 4.0 Shading Language Cookbook.

// Initial velocity and start time
layout (location = 0) in vec3 vertexInitVel;
layout (location = 1) in float startTime;

out float transparency;

uniform float time; // animation time
uniform vec3 gravity = vec3(0.0, -0.2, 0.0); // world coords
uniform float particleLifetime; // max particle particleLifetime
uniform mat4 mvp;

void main() {

    // Assume initial position is (0,0,0)
    vec3 pos = vec3(0.0);
    transparency = 0.0;

    // particle doesn't exist until the start time
    if (time > startTime) {
        float t = time - startTime;

        if (t < particleLifetime) {
            pos = vertexInitVel * t + gravity * t * t;
            transparency = 1.0 - t / particleLifetime;
        }
        else {
            transparency = 0.0;
        }
    }
    gl_Position = mvp * vec4(pos, 1.0);
}