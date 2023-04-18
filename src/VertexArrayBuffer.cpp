#include "VertexArrayBuffer.h"

#include <cstddef>
#include <stdexcept>
#include <string>

#include <glad/glad.h>

//TODO once the program becomes more complex I will need a decorator class that manages vertex buffer IDs and draw orchestration

VertexArrayBuffer::VertexArrayBuffer() {
    glGenVertexArrays(1, &_varray);
    glGenBuffers(1, &_vbuffer);
    glGenBuffers(1, &_ibuffer);
}
VertexArrayBuffer::~VertexArrayBuffer() {
    //these could be null so check first before deleting
    if (_varray) {
        glDeleteVertexArrays(1, &_varray);
    }
    if (_vbuffer) {
        glDeleteBuffers(1, &_vbuffer);
    }
    if (_ibuffer) {
        glDeleteBuffers(1, &_ibuffer);
    }
}

/**
 * @param verts The vertices
 * @param verts_size sizeof the vertices. Remember this cannot be sizeof a pointer. It must be the size it would be in array.
 * @param shape How many numbers does a vertex contain? eg. xyz is 3, xyzrgb is 6, xyzrgbijk is 9
 * @param shape_unit Within a vertex, how many numbers are a single unit of information? ie the number to place here for xyzrgb is 3 because xyz and rgb have three numbers that descibe the postion and color.
 * @param indices The indices
 * @param indices_size Same as verts_size except for the indices
 */
void VertexArrayBuffer::set_vertices(float *verts, std::size_t verts_size, int shape, int shape_unit, GLuint *indices, size_t indices_size) {
    //Check if the shape makes sense
    if (shape == 0 || shape_unit == 0) {
        throw std::runtime_error("Invalid shape: shape and shape_unit cannot equal zero. shape: " + std::to_string(shape) + " shape_unit: " + std::to_string(shape_unit));
    }

    //Class attributes
    _verts = verts;
    _verts_size = verts_size;
    _shape = shape;
    _shape_unit = shape_unit;
    _indices = indices;
    _indices_size = indices_size;

    //Set derived attributes. These are only used once but they are here for convenience.
    _num_indices = _indices_size / sizeof(short);
    _num_attributes = _shape / _shape_unit;
}

void VertexArrayBuffer::_bind() {
    glBindVertexArray(_varray);
    glBindBuffer(GL_ARRAY_BUFFER, _vbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibuffer);
    
    //Enable opengl to accept (rgbxyz...). We need to use a loop because xyz and rgb are different attributes, or shape units, as I call them.
    for (int a = 0; a < _num_attributes; a++) {
        glEnableVertexAttribArray(a);
    }
}

void VertexArrayBuffer::_unbind() {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    //Don't accept any attributes at the moment.
    for (int a = 0; a < _num_attributes; a++) {
        glDisableVertexAttribArray(a);
    }
}

void VertexArrayBuffer::buffer() {
    _bind();
    
    //Define the shape of the vertex (xyz rgb etc..)
    for (int a = 0; a < _num_attributes; a++) { 
        //It would be best if you just read the documentation on what this function is and what the variables are doing here. Too much detail for here.
        glVertexAttribPointer(
            a, _shape_unit, GL_FLOAT, GL_FALSE, _shape * sizeof(float), (void*)(a * _shape_unit * sizeof(float))
        );
    }
    //Buffer the vertices and indices
    glBufferData(GL_ARRAY_BUFFER, _verts_size, _verts, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices_size, _indices, GL_STATIC_DRAW);
    
    _unbind();
}

void VertexArrayBuffer::draw() {
    _bind();
    glDrawElements(GL_TRIANGLES, _num_indices, GL_UNSIGNED_INT, 0);
    _unbind();
}
