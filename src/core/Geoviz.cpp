//standard libraries
#include <vector>
#include <cmath>
#include <iostream>
#include <memory>

//Relevant header files from this project
#include "core/Geoviz.h"
#include "core/SDLContext.h"
#include "core/SDLContextLogic.h"
#include "core/ShaderFactory.h"
#include "core/GLProgram.h"
#include "core/Renderer.h"
#include "core/VertexArrayObject.h"
#include "core/VertexBuffer.h"
//#include "core/VertexIndexMediator.h"
#include "core/IndexBuffer.h"
#include "core/ShaderFile.h"
#include "core/Geomodel.h"
#include "util/ImmutableArray.h"
#include "util/Vec4f.h"

void Geoviz::run(Geomodel model_pool) {
    //create an SDLContext and choose the logic to go with it.
    std::unique_ptr<SDLContext> context = std::make_unique<SDLContextLogic>(800, 800, "Geoviz"); //do not move. must be first function.

    //Create the shaders
    std::vector<ShaderFile> shaders;
    std::string wd = "/home/steven/desktop/geoviz";
    shaders.push_back(
        ShaderFactory::read_shader_file(wd + "/src/shaders/v.glsl")
    );
    shaders.push_back(
        ShaderFactory::read_shader_file(wd + "/src/shaders/f.glsl")
    );
        
    //Create the opengl program using the shaders.
    GLProgram program = GLProgram(shaders);

    ImmutableArray<float> vertices = model_pool.get_vertices();
    ImmutableArray<GLuint> indices = model_pool.get_indices();

    //Create the arraybuffer and give it the vertices and indices we just defined, and some addiional information about how we defined it.
    /*
    VertexArrayBuffer vabuffer = VertexArrayBuffer();
    vabuffer.update(va, model_pool.get_stride(), model_pool.get_parts_per_attribute());

    IndexBuffer ibuffer = IndexBuffer();
    ibuffer.update(ia);
    
    VertexIndexMediator vimediator = VertexIndexMediator(vabuffer, ibuffer);
    */
    ImmutableArray<int> dimensions({3,3});

    VertexArrayObject vao = VertexArrayObject(dimensions);
    vao.bind();

    VertexBuffer vbo = VertexBuffer(vao);
    vbo.update(vertices);

    IndexBuffer ebo = IndexBuffer(vao);
    ebo.update(indices);

    //Give the program and vertex buffer to the renderer
    Vec4f clear_color = {0.5, 0.5, 0.5, 1.0};
    Renderer renderer = Renderer(program, ebo, vbo, vao, clear_color);
    //Renderer renderer = Renderer(program, vimediator, clear_color);
   
    //Now that we have created a renderer we can attach it to the window and activate the window.
    context->set_renderer(renderer);
    context->run(); // <- render loop here
}
