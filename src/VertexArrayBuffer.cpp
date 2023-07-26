#include "VertexArrayBuffer.h"

#include <cstddef>
#include <stdexcept>
#include <string>
#include <functional>

#include <glad/glad.h>

#include "ImmutableArray.h"

//TODO once the program becomes more complex I will need a decorator class that manages vertex buffer IDs and draw orchestration

VertexArrayBuffer::VertexArrayBuffer() {
    glGenVertexArrays(1, &_varray);
    glGenBuffers(1, &_vbuffer);
}
VertexArrayBuffer::~VertexArrayBuffer() {
    //these could be null so check first before deleting
    glDeleteVertexArrays(1, &_varray);
    glDeleteBuffers(1, &_vbuffer);
}

/**
 * @param verts The vertices
 * @param vertex_length How many numbers does a vertex contain? eg. xyz is 3, xyzrgb is 6, xyzrgbijk is 9
 * @param attribute_length Within a vertex, how many numbers are a single unit of information? ie the number to place here for xyzrgb is 3 because xyz and rgb have three numbers that descibe the postion and color 'attributes'.
 */
void VertexArrayBuffer::update(ImmutableArray<float> verts, int vertex_length, int attribute_length) {
    //Check if the shape makes sense
    if (vertex_length == 0 || attribute_length == 0) {
        throw std::runtime_error("Invalid shape: vertex_length and attribute_length cannot equal zero. vertex_length: " + std::to_string(vertex_length) + " attribute_length: " + std::to_string(attribute_length));
    }

    //Class attributes
    _verts = verts;
    _vertex_length = vertex_length;
    _attribute_length = attribute_length;

    //Set derived attributes. These are only used once but they are here for convenience.
    _num_attributes = _vertex_length / _attribute_length;
}

void VertexArrayBuffer::_bind() {
    glBindVertexArray(_varray);
    glBindBuffer(GL_ARRAY_BUFFER, _vbuffer);
    
    //Enable opengl to accept (rgbxyz...). We need to use a loop because xyz and rgb are different attributes, or shape units, as I call them.
    for (int a = 0; a < _num_attributes; a++) {
        glEnableVertexAttribArray(a);
    }
}

void VertexArrayBuffer::_unbind() {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
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
            a, _attribute_length, GL_FLOAT, GL_FALSE, _vertex_length * sizeof(float), (void*)(a * _attribute_length * sizeof(float))
        );
    }
    //Buffer the vertices and indices
    glBufferData(GL_ARRAY_BUFFER, _verts.get_size(), 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, _verts.get_size(), _verts.get_pointer());
    _unbind();
}

/*
void VertexArrayBuffer::draw() {
    glDrawElements(GL_TRIANGLES, _num_indices, GL_UNSIGNED_INT, 0);
}
*/
