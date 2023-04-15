#include "Renderer.h"

#include "GLProgram.h"
#include "VertexBuffer.h"
#include "Color.h"

Renderer::Renderer(GLProgram &program, VertexBuffer &vertex_buffer, Color &clear_color) {
    this->_vbuffer = &vertex_buffer;
    this->_program = &program;
    this->_clear_color = &clear_color;
}

void Renderer::draw() {
    glClearColor(this->_clear_color->red, this->_clear_color->green, this->_clear_color->blue, this->_clear_color->alpha);
    glClear(GL_COLOR_BUFFER_BIT);
    this->_program->use_program();
    this->_vbuffer->buffer();
    this->_vbuffer->draw();
}
