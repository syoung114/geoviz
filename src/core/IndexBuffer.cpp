#include <cstddef>
#include <stdexcept>
#include <functional>

#include <glad/glad.h>

#include "core/IndexBuffer.h"
#include "core/VertexArrayObject.h"
//TODO once the program becomes more complex I will need a decorator class that manages vertex buffer IDs and draw orchestration

IndexBuffer::IndexBuffer(const VertexArrayObject& vao) {
    glCreateBuffers(1, &_id);
    glVertexArrayElementBuffer(vao.get_id(), _id);
    _needs_buffer = false;
}
IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &_id);
}

bool IndexBuffer::buffer(const bool forceful) { 
    if (_needs_buffer || forceful) {
        size_t isize_bytes = _indices->size() * sizeof(GLuint);
        glNamedBufferData(_id, isize_bytes, 0, GL_STATIC_DRAW);
        glNamedBufferSubData(_id, 0, isize_bytes, _indices->data()); 

	_needs_buffer = false;
	return true;
    }
    return false;
}

/**
 * Requires manual binding by wrapping with binding_call
 */
void IndexBuffer::draw() {
    glDrawElements(GL_TRIANGLES, _indices->size(), GL_UNSIGNED_INT, 0);
}
