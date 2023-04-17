#include "Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLProgram.h"
#include "VertexArrayBuffer.h"
#include "Vec4f.h"

//TODO should have a vector of vertexarraybuffers instead.

Renderer::Renderer(GLProgram &program, VertexArrayBuffer &vertex_buffer, Vec4f &clear_color) {
    this->_vbuffer = &vertex_buffer;
    this->_program = &program;
    this->_clear_color = &clear_color;
    
    this->_world = glm::mat4(1.0);

    this->_view = glm::mat4(1.0);
    _view = glm::translate(_view, glm::vec3(0.0, 0.0, -5.0));
    
    this->_proj = glm::mat4(1.0);
    _proj = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 1000.0f);

    glEnable(GL_DEPTH_TEST);
}

void Renderer::draw(int screen_width, int screen_height) {
    glClearColor(this->_clear_color->x, this->_clear_color->y, this->_clear_color->z, this->_clear_color->w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->_program->use_program();

    this->_world = glm::rotate(this->_world, glm::radians(0.5f), glm::vec3(1.0f, 1.0f, 0.0f));

    this->_program->set_uniform_mat4fv("world", this->_world);
    this->_program->set_uniform_mat4fv("view", this->_view);
    this->_program->set_uniform_mat4fv("proj", this->_proj);

    this->_vbuffer->buffer();
    this->_vbuffer->draw();
}
