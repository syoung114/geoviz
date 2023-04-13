#version 330 core
in vec4 vertexColour;
// out FragColour;
void main() {
    gl_FragColor = vertexColour;
}
