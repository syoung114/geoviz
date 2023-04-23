#include <cstddef>
#include <stdexcept>
#include <functional>

#include <glad/glad.h>

#include "IndexBuffer.h"
//TODO once the program becomes more complex I will need a decorator class that manages vertex buffer IDs and draw orchestration

IndexBuffer::IndexBuffer() {
    glGenBuffers(1, &_ibuffer);
}
IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &_ibuffer);
}

/**
 * @param indices The indices
 * @param indices_size Same as verts_size except for the indices
 */
void IndexBuffer::update(GLuint *indices, size_t indices_size) {
    _indices = indices;
    _indices_size = indices_size;
    _num_indices = _indices_size / sizeof(GLuint);
}

void IndexBuffer::_bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibuffer);
}

void IndexBuffer::_unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::buffer() { 
    _bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices_size, 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, _indices_size, _indices); 
    _unbind();
}

/**
 * Requires manual binding by wrapping with binding_call
 */
void IndexBuffer::draw() {
    glDrawElements(GL_TRIANGLES, _num_indices, GL_UNSIGNED_INT, 0);
}
