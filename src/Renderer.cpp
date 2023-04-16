#include "Renderer.h"

#include "GLProgram.h"
#include "VertexArrayBuffer.h"
#include "Vec4f.h"

Renderer::Renderer(GLProgram &program, VertexArrayBuffer &vertex_buffer, Vec4f &clear_color) {
    this->_vbuffer = &vertex_buffer;
    this->_program = &program;
    this->_clear_color = &clear_color;
}

void Renderer::draw() {
    glClearColor(this->_clear_color->x, this->_clear_color->y, this->_clear_color->z, this->_clear_color->w);
    glClear(GL_COLOR_BUFFER_BIT);
    this->_program->use_program();
    this->_vbuffer->buffer();
    this->_vbuffer->draw();
}
