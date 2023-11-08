#include "core/VertexBuffer.h"

#include <cstddef>
#include <stdexcept>
#include <string>
#include <iostream>
#include <functional>

#include <glad/glad.h>

#include "util/ImmutableArray.h"
#include "core/VertexArrayObject.h"

//TODO once the program becomes more complex I will need a decorator class that manages vertex buffer IDs and draw orchestration

VertexBuffer::VertexBuffer(VertexArrayObject& vao) {
    glCreateBuffers(1, &_id);
    std::cout<<std::to_string(vao.get_id()) + "\n";
    //_vao = &vao;
/*
    size_t vao_num_attrs = vao.get_num_attrs();
    for (int a = 0; a < vao_num_attrs; a++) {
        glVertexArrayAttribBinding(vao.get_id(), a, _id);
    }
*/
    glVertexArrayVertexBuffer(vao.get_id(), 0, _id, 0, vao.get_vertex_length() * sizeof(float));
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &_id);
}

/**
 * @param verts The vertices
 * @param vertex_length How many numbers does a vertex contain? eg. xyz is 3, xyzrgb is 6, xyzrgbijk is 9
 * @param attribute_length Within a vertex, how many numbers are a single unit of information? ie the number to place here for xyzrgb is 3 because xyz and rgb have three numbers that descibe the postion and color 'attributes'.
 */
void VertexBuffer::update(ImmutableArray<float> verts) {
    _verts = verts;
}

void VertexBuffer::buffer() {
    glNamedBufferData(_id, _verts.get_size(), 0, GL_STATIC_DRAW);
    glNamedBufferSubData(_id, 0, _verts.get_size(), _verts.get_pointer());
    //glNamedBufferData(_id, _verts.get_size(), _verts.get_pointer(), GL_STATIC_DRAW);
}

/*
void VertexBuffer::draw() {
    glDrawElements(GL_TRIANGLES, _num_indices, GL_UNSIGNED_INT, 0);
}
*/
