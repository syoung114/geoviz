GL_VERTEX_SHADER
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 model_view_projection;

out vec3 vertex_color;

void main() {
    gl_Position = model_view_projection * vec4(aPos, 1.0);
    vertex_color = aColor;
}
