#include <cstddef>
#include <stdexcept>
#include <functional>

#include <glad/glad.h>

#include "core/IndexBuffer.h"
#include "util/ImmutableArray.h"
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
void IndexBuffer::update(ImmutableArray<GLuint> indices) {
    _indices = indices;
    _num_indices = _indices.get_size() / sizeof(GLuint);
}

void IndexBuffer::_bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibuffer);
}

void IndexBuffer::_unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::buffer() { 
    _bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.get_size(), 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, _indices.get_size(), _indices.get_pointer()); 
    _unbind();
}

/**
 * Requires manual binding by wrapping with binding_call
 */
void IndexBuffer::draw() {
    glDrawElements(GL_TRIANGLES, _num_indices, GL_UNSIGNED_INT, 0);
}
