#version 400

in float transparency;

uniform sampler2D spriteTexture;

layout (location = 0) out vec4 fragColor;

void main() {
    vec4 color = texture(spriteTexture, gl_PointCoord);
    if (color.a < 0.0000001)
        discard;

    fragColor = vec4(color);
    fragColor.a *= transparency;
}