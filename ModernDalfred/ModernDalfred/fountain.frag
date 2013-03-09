#version 400

in float transparency;

layout (location = 0) out vec4 fragColor;

void main() {
    fragColor = vec4(0.0, 0.7, 0.8, 1.0);
    fragColor.a *= transparency;
}