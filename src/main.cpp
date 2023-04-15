//standard libraries
#include <vector>
#include <cmath>
#include <iostream>

//Relevant header files from this project
#include "GLFWwindowArgs.h"
#include "GLFWContextManager.h"
#include "ShaderFactory.h"
#include "GLProgram.h"
#include "Renderer.h"
#include "VertexBuffer.h"

int main(int argc, char* argv[]) {
    
    //Create a context (window) that will be used to render the thing. 
    GLFWwindowArgs window_args = {800, 800, "test"};
    GLFWContextManager *context = new GLFWContextManager(window_args);
 
    //Create the shaders
    std::vector<GLuint> shaders;
    std::string wd = "/home/steven/desktop/geoviz";
    shaders.push_back(
        ShaderFactory::read_and_create(wd + "/src/shaders/v.glsl", GL_VERTEX_SHADER)
    );
    shaders.push_back(
        ShaderFactory::read_and_create(wd + "/src/shaders/f.glsl", GL_FRAGMENT_SHADER)
    );
        
    //Create the opengl program using the shaders.
    GLProgram *program = new GLProgram(shaders);

    //Buffer some vertices (placeholder vertices)    
    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) / 2, 0.0f
    };
    int num_verts = 3;
    VertexBuffer *vbuffer = new VertexBuffer(vertices, sizeof(vertices), num_verts);
    
    //Give the program and vertex buffer to the renderer
    Color clear_color = {0.0f, 0.0f, 0.0f, 1.0f};
    Renderer *renderer = new Renderer(*program, *vbuffer, clear_color);
   
    //Now that we have created a renderer we can attach it to the window and activate the window.
    context->set_renderer(*renderer);
    context->run(); // <- render loop here
    
    //We created pointers to object instances. In this case we must manually clean them up. Out of good practice the order matters: LIFO
    delete renderer;
    delete program;
    delete vbuffer;
    delete context;

    return 0;

}
