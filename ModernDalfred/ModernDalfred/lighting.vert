#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec3 vertexNormal;

out vec3 lightIntensity;

uniform vec4 lightPosition;
uniform vec3 Kd; // material diffuse 
uniform vec3 Ld; // light diffuse intensity

uniform mat4 mvMat;
uniform mat4 projMat;
uniform mat4 normalMat;
uniform mat4 mvp;

void main() {
    // convert normal and position to eye coordinates
    vec3 eyeNorm = vec3(normalize(normalMat * vec4(vertexNormal, 1.0)));
    vec4 eyePos = mvMat * vec4(vertexPosition, 1.0);

    // get the vector from the surface to the light
    vec3 posToLight = normalize(vec3(lightPosition - eyePos));

    // apply the diffuse equation
    lightIntensity = Ld * Kd * max(dot(posToLight, eyeNorm), 0.0);

    // pass along vertex position
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}