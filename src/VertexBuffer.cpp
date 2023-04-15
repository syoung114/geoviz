#include "VertexBuffer.h"

#include <cstddef>
#include <cmath>
#include <glad/glad.h>
//#include <iostream>

VertexBuffer::VertexBuffer(float *verts, std::size_t size) {
    this->set_vertices(verts, size);
    glGenVertexArrays(1, &(this->_varray));
    glGenBuffers(1, &(this->_vbuffer));
}
VertexBuffer::~VertexBuffer() {
    //varray and vbuffer could be null so check first before deleting
    if (this->_varray) {
        glDeleteVertexArrays(1, &this->_varray);
    }
    if (this->_vbuffer) {
        glDeleteBuffers(1, &this->_vbuffer);
    } 
}

void VertexBuffer::set_vertices(float *verts, std::size_t size) { 
	this->_verts = verts;
    this->_size = size;
    //this->_num_verts = size / sizeof(GLfloat);
    //std::cout << _num_verts;
    _num_verts = 3;
}

void VertexBuffer::bind() {
    glBindVertexArray(this->_varray);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbuffer);
}

void VertexBuffer::unbind() {
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void VertexBuffer::buffer_vertices() {
    this->bind();

    //glBufferData(GL_ARRAY_BUFFER, pow(this->_size, 2) / sizeof(this->_verts[0]), &this->_verts[0], GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, this->_size, this->_verts, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, this->_num_verts, GL_FLOAT, GL_FALSE, this->_num_verts * sizeof(float), (void*)0);

    this->unbind();
}

/**
 * Do not use in isolation. Intended as one part of a draw call.
 */
void VertexBuffer::draw() {
    //this->bind();
    glBindVertexArray(this->_varray);
    glDrawArrays(GL_TRIANGLES, 0, this->_num_verts);
    //this->unbind();
}
