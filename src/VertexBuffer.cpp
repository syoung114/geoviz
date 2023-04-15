#include "VertexBuffer.h"

#include <cstddef>

#include <glad/glad.h>

//TODO once the program sbecomes more complex I will need a 'super' class that manages vertex buffer IDs and draw orchestration

VertexBuffer::VertexBuffer(float *verts, std::size_t size, int num_verts) {
    this->_id = 0;
    this->set_vertices(verts, size, num_verts);
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

void VertexBuffer::set_vertices(float *verts, std::size_t size, int num_verts) { 
	this->_verts = verts;
    this->_size = size;
    this->_num_verts = num_verts;
}

void VertexBuffer::bind() {
    glBindVertexArray(this->_varray);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbuffer);
    glEnableVertexAttribArray(this->_id);
}

void VertexBuffer::unbind() {
    glDisableVertexAttribArray(this->_id);
    glBindBuffer(GL_ARRAY_BUFFER, this->_id);
    glBindVertexArray(this->_id);
}

void VertexBuffer::buffer() {
    this->bind();

    glBufferData(GL_ARRAY_BUFFER, this->_size, this->_verts, GL_STATIC_DRAW);
    
    glVertexAttribPointer(this->_id, this->_num_verts, GL_FLOAT, GL_FALSE, this->_num_verts * sizeof(float), (void*)0);

    this->unbind();
}

/**
 * Do not use in isolation. Intended as one part of a draw call.
 */
void VertexBuffer::draw() {
    this->bind();
    glDrawArrays(GL_TRIANGLES, 0, this->_num_verts);
    this->unbind();
}
