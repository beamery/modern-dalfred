#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec3 vertexNormal;
layout (location = 3) in vec2 vertexTexture;

out vec2 texCoord;

uniform mat4 mvMat;
uniform mat4 projMat;
uniform mat4 normalMat;
uniform mat4 mvp;

void main() {

    texCoord = vertexTexture;
    // pass along vertex position
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}

//void main() {
    // pass along vertex position
    //gl_Position = mvp * vec4(vertexPosition, 1.0);
//}
