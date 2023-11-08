#include <cstddef>
#include <stdexcept>
#include <functional>

#include <glad/glad.h>

#include "core/IndexBuffer.h"
#include "util/ImmutableArray.h"
#include "core/VertexArrayObject.h"
//TODO once the program becomes more complex I will need a decorator class that manages vertex buffer IDs and draw orchestration

#include <iostream>
#include<string>

IndexBuffer::IndexBuffer(VertexArrayObject& vao) {
    glCreateBuffers(1, &_id);
    glVertexArrayElementBuffer(vao.get_id(), _id);
    std::cout<<std::to_string(_id) + "\n";
}
IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &_id);
}

/**
 * @param indices The indices
 * @param indices_size Same as verts_size except for the indices
 */
void IndexBuffer::update(ImmutableArray<GLuint> indices) {
    _indices = indices;
    _num_indices = _indices.get_size() / sizeof(GLuint);
}

void IndexBuffer::buffer() { 
    glNamedBufferData(_id, _indices.get_size(), 0, GL_STATIC_DRAW);
    glNamedBufferSubData(_id, 0, _indices.get_size(), _indices.get_pointer()); 
    //glNamedBufferData(_id, _indices.get_size(), _indices.get_pointer(), GL_STATIC_DRAW);
}

/**
 * Requires manual binding by wrapping with binding_call
 */
void IndexBuffer::draw() {
    glDrawElements(GL_TRIANGLES, _num_indices, GL_UNSIGNED_INT, 0);
}
