#version 410 core

layout(location = 0) out vec4 finalColor;

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragVert;

uniform sampler2D materialTex;

void main(void) {
    finalColor = texture(materialTex, fragTexCoord);
}
