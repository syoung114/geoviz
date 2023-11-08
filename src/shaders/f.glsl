GL_FRAGMENT_SHADER
#version 460 core
in vec3 vertex_color;

out vec4 FragColor;

void main() {
    //FragColor = vec4(1.0, 0.0, 0.0, 1.0f);
    FragColor = vec4(vertex_color, 1.0f);
}
