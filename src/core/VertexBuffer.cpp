#include <glad/glad.h>
#include <cstddef>

#include "core/VertexBuffer.h"
#include "core/VertexArrayObject.h"

//TODO once the program becomes more complex I will need a decorator class that manages vertex buffer IDs and draw orchestration

VertexBuffer::VertexBuffer(const VertexArrayObject& vao, const int vertex_length) {
    glCreateBuffers(1, &_id);
    glVertexArrayVertexBuffer(vao.get_id(), 0, _id, 0, vertex_length * sizeof(float));
    _needs_buffer = false;
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &_id);
}

bool VertexBuffer::buffer(const bool forceful) {
    if (_needs_buffer || forceful) {
        size_t vsize_bytes = _verts->size() * sizeof(float);
        glNamedBufferData(_id, vsize_bytes, 0, GL_STATIC_DRAW);
        glNamedBufferSubData(_id, 0, vsize_bytes, _verts->data());

	_needs_buffer = false;
        return true;
    }
    return false;
}

/*
void VertexBuffer::draw() {
    glDrawElements(GL_TRIANGLES, _verts->size(), GL_UNSIGNED_INT, 0);
}
*/
