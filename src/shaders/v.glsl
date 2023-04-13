#version 330 core
layout (location = 0) in vec3 aPos;
//out vec4 vertexColour; // specify a colour output to the fragment shader
void main()
{
    gl_Position = vec4(aPos, 1.0); // we give a vec3 to vec4’s constructor
    vertexColour = vec4(0.5, 0.0, 0.0, 1.0); // output variable to dark-red
}
