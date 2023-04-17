#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 world;
uniform mat4 view;
uniform mat4 proj;

out vec3 vertex_color;

void main() {
    gl_Position = proj * view * world * vec4(aPos, 1.0);
    vertex_color = aColor;
}
