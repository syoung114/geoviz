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
#include "VertexIndexMediator.h"
#include "IndexBuffer.h"
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
    	
    //VertexBuilder vb;
    /*
    float *vertices = vb
        .start(3,9,positions)
        ->concat(3,9,rgb)
        ->finish();
    
    int num_verts = 3;
    int size = 24*sizeof(float);
    */
    
    float vertices[] = {
        -0.5, -0.5, -0.5, 1.0, 0.0, 0.0,
        -0.5, -0.5, 0.5, 0.0, 1.0, 0.0,
        -0.5, 0.5, -0.5, 0.0, 0.0, 1.0,
        -0.5, 0.5, 0.5, 1.0, 0.0, 1.0,
        0.5, -0.5, -0.5, 1.0, 1.0, 1.0,
        0.5, -0.5, 0.5, 0.0, 1.0, 1.0,
        0.5, 0.5, -0.5, 1.0, 1.0, 1.0,
        0.5, 0.5, 0.5, 0.0, 0.0, 0.0
    };
    size_t verts_size = sizeof(vertices);
	GLuint indices[] = {
		0, 2, 1, 
		1, 2, 3,
		4, 5, 6, 
		5, 7, 6,
		0, 1, 4, 
		1, 5, 4,
		2, 6, 3, 
		3, 6, 7,
		0, 4, 2, 
		2, 4, 6,
		1, 3, 5, 
		3, 7, 5,
	};
    size_t indices_size = sizeof(indices);

    //Create the arraybuffer and give it the vertices and indices we just defined, and some addiional information about how we defined it.
    VertexArrayBuffer *vabuffer = new VertexArrayBuffer();
    vabuffer->update(vertices, verts_size, 6, 3);

    IndexBuffer *ibuffer = new IndexBuffer();
    ibuffer->update(indices, indices_size);
    
    VertexIndexMediator *vimediator = new VertexIndexMediator(*vabuffer, *ibuffer);

    //Give the program and vertex buffer to the renderer
    Vec4f clear_color = {0.0, 0.0, 0.05f, 1.0};
    Renderer *renderer = new Renderer(*program, *vimediator, clear_color);
   
    //Now that we have created a renderer we can attach it to the window and activate the window.
    context->set_renderer(*renderer);
    context->run(); // <- render loop here
    
    //We created pointers to object instances. In this case we must manually clean them up. Out of good practice the order matters: LIFO
    delete renderer;
    delete vimediator;
    //delete ibuffer;
    //delete vabuffer;
    delete program;
    delete context;
    
    return 0;
}
