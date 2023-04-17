#include "VertexArrayBuffer.h"

#include <cstddef>

#include <glad/glad.h>

//TODO once the program becomes more complex I will need a decorator class that manages vertex buffer IDs and draw orchestration

VertexArrayBuffer::VertexArrayBuffer(float *verts, std::size_t verts_size, int shape, int shape_unit, GLuint *indices, size_t indices_size, short num_indices) {
    this->set_vertices(verts, verts_size, shape, shape_unit, indices, indices_size, num_indices);
    glGenVertexArrays(1, &(this->_varray));
    glGenBuffers(1, &(this->_vbuffer));
    glGenBuffers(1, &(this->_ibuffer));
}
VertexArrayBuffer::~VertexArrayBuffer() {
    //varray and vbuffer could be null so check first before deleting
    if (this->_varray) {
        glDeleteVertexArrays(1, &(this->_varray));
    }
    if (this->_vbuffer) {
        glDeleteBuffers(1, &(this->_vbuffer));
    }
    if (this->_ibuffer) {
        glDeleteBuffers(1, &(this->_ibuffer));
    }
}

void VertexArrayBuffer::set_vertices(float *verts, std::size_t verts_size, int shape, int shape_unit, GLuint *indices, size_t indices_size, short num_indices) {
	this->_verts = verts;
    this->_verts_size = verts_size;
    this->_shape_unit = shape_unit;
    this->_shape = shape;
    this->_unit_count = this->_shape / this->_shape_unit;
    this->_indices = indices;
    this->_indices_size = indices_size;
    this->_num_indices = num_indices;
}

void VertexArrayBuffer::_bind() {
    glBindVertexArray(this->_varray);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ibuffer);
    for (int a = 0; a < this->_unit_count; a++) {
        glEnableVertexAttribArray(a);
    }
}

void VertexArrayBuffer::_unbind() {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    for (int a = 0; a < this->_unit_count; a++) {
        glDisableVertexAttribArray(a);
    }
}

void VertexArrayBuffer::buffer() {
    this->_bind();
    
    for (int a = 0; a < this->_unit_count; a++) { 
        glVertexAttribPointer(
            a, this->_shape_unit, GL_FLOAT, GL_FALSE, this->_shape * sizeof(float), (void*)(a * this->_shape_unit * sizeof(float))
        );
    }
    glBufferData(GL_ARRAY_BUFFER, this->_verts_size, this->_verts, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_indices_size, this->_indices, GL_STATIC_DRAW);
    
    this->_unbind();
}

void VertexArrayBuffer::draw() {
    this->_bind();
    //glDrawArrays(GL_TRIANGLES, 0, 36);
    glDrawElements(GL_TRIANGLES, this->_num_indices, GL_UNSIGNED_INT, 0);
    this->_unbind();
}
