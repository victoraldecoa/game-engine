#version 410 core

layout(location = 0) in vec3 vert;
in vec2 vertTexCoord;
in vec3 vertNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 fragVert;
out vec2 fragTexCoord;
out vec3 fragNormal;


void main() {
    fragTexCoord = vertTexCoord;
    fragNormal = vertNormal;
    fragVert = vert;
    gl_Position = projection * view * model * vec4(vert, 1.0);//w is 1.0, also notice cast to a vec4
}
