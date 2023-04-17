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
#include "VertexArrayBuffer.h"
#include "Vec4f.h"

#include "VertexBuilder.h"

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

    //Buffer some vertices, giving positions and rgb to a vertex buffer.

	
    float vertices[] = {
         -0.5f,-0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     1.0f, 0.0f, 0.0f, // Lower left corner
       	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.0f, 1.0f, 0.0f, // Lower right corner
       	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     0.0f, 0.0f, 1.0f, // Upper corner
         -0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,    0.0f, 1.0f, 0.0f, // Inner left
         0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     1.0f, 0.0f, 0.0f, // Inner right
         0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.0f, 0.0f, 1.0f  // Inner down
    };
    GLuint indices[] = {
        0, 3, 5,
        3, 2, 4,
        5, 4, 1
    };
/*
    float rgb[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    VertexBuilder vb;
    float *vertices = vb
        .start(3,9,positions)
        ->concat(3,9,rgb)
        ->finish();
    
    int num_verts = 3;
    int size = 24*sizeof(float);
*/
    int num_indices = 9;
    //int verts_size = 24*sizeof(float);
    size_t verts_size = sizeof(vertices);
    size_t indices_size = sizeof(indices);
    //short indices_size = sizeof(indices);
    VertexArrayBuffer *vbuffer = new VertexArrayBuffer(vertices, verts_size, 6, 3, indices, indices_size, num_indices);
    
    //Give the program and vertex buffer to the renderer
    Vec4f clear_color = {0.0, 0.0, 0.0, 1.0};
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
