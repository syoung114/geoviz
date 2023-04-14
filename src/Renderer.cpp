#include "Renderer.h"

#include "GLProgram.h"
#include "VertexBuffer.h"
#include "Color.h"

Renderer::Renderer(GLProgram &program, VertexBuffer &vertex_buffer, Color clear_color) {
    this->_buffer = &vertex_buffer;
    this->_program = &program;
    glClearColor(this->_clear_color->red, this->_clear_color->green, this->_clear_color->blue, this->_clear_color->alpha);
}

void Renderer::draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    this->_program->use_program();
    this->_buffer->buffer_vertices();
    this->_buffer->draw();
}
