#include "VertexArrayBuffer.h"

#include <cstddef>

#include <glad/glad.h>

//TODO once the program becomes more complex I will need a decorator class that manages vertex buffer IDs and draw orchestration

VertexArrayBuffer::VertexArrayBuffer(float *verts, std::size_t size, int num_verts, int shape, int shape_unit) {
    this->_id = 0;
    this->set_vertices(verts, size, num_verts, shape, shape_unit);
    glGenVertexArrays(1, &(this->_varray));
    glGenBuffers(1, &(this->_vbuffer)); 
}
VertexArrayBuffer::~VertexArrayBuffer() {
    //varray and vbuffer could be null so check first before deleting
    if (this->_varray) {
        glDeleteVertexArrays(1, &this->_varray);
    }
    if (this->_vbuffer) {
        glDeleteBuffers(1, &this->_vbuffer);
    } 
}

void VertexArrayBuffer::set_vertices(float *verts, std::size_t size, int num_verts, int shape, int shape_unit) {
	this->_verts = verts;
    this->_size = size;
    this->_num_verts = num_verts;
    this->_shape_unit = shape_unit;
    this->_shape = shape;
    this->_unit_count = this->_shape / this->_shape_unit;
}

void VertexArrayBuffer::_bind() {
    glBindVertexArray(this->_varray);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbuffer);
    for (int a = 0; a < this->_unit_count; a++) {
        glEnableVertexAttribArray(a);
    }
}

void VertexArrayBuffer::_unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    for (int a = 0; a < this->_unit_count; a++) {
        glDisableVertexAttribArray(a);
    }
}

void VertexArrayBuffer::buffer() {
    this->_bind();
    
    for (int a = 0; a < this->_unit_count; a++) { 
        glVertexAttribPointer(
            a,
            this->_shape_unit,
            GL_FLOAT,
            GL_FALSE,
            this->_shape * sizeof(float),
            (void*)(a * this->_shape_unit * sizeof(float))
        );
    }
    glBufferData(GL_ARRAY_BUFFER, this->_size, this->_verts, GL_STATIC_DRAW);
    
//  glDisableVertexAttribArray(0);
    this->_unbind();
}

/**
 * Do not use in isolation. Intended as one part of a draw call.
 */
void VertexArrayBuffer::draw() {
    this->_bind();
    glDrawArrays(GL_TRIANGLES, 0, this->_num_verts);
    this->_unbind();
}
