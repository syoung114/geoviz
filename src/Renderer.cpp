#include "Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLProgram.h"
#include "VertexArrayBuffer.h"
#include "Vec4f.h"

//TODO should have a vector of vertexarraybuffers instead.

Renderer::Renderer(GLProgram &program, VertexArrayBuffer &vertex_buffer, Vec4f &clear_color) {
    _vbuffer = &vertex_buffer;
    _program = &program;
    _clear_color = &clear_color;
    
    //Set the rendering matrices
    _world = glm::mat4(1.0);

    _view = glm::mat4(1.0);
    _view = glm::translate(_view, glm::vec3(0.0, 0.0, -5.0));
    
    _proj = glm::mat4(1.0);
    _proj = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 1000.0f);

    //Remove fragments 'behind' other fragments
    glEnable(GL_DEPTH_TEST);
}

void Renderer::draw(int screen_width, int screen_height) {
    glClearColor(_clear_color->x, _clear_color->y, _clear_color->z, _clear_color->w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _program->use_program();

    _world = glm::rotate(_world, glm::radians(0.5f), glm::vec3(1.0f, 0.0f, 1.0f));
    
    //Give the transformation matrices to the shaders
    _program->set_uniform_mat4fv("world", _world);
    _program->set_uniform_mat4fv("view", _view);
    _program->set_uniform_mat4fv("proj", _proj);

    _vbuffer->buffer();
    _vbuffer->draw();
}
