#version 400

in vec2 texCoord;

uniform sampler2D spriteTexture;

layout (location = 0) out vec4 fragColor;

void main() {
    vec3 color = vec3(texture(spriteTexture, texCoord));
    fragColor = vec4(color, 1.0);
}
