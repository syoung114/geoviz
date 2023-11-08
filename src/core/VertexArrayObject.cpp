#include "core/VertexArrayObject.h"

#include <glad/glad.h>

#include "util/ImmutableArray.h"

#include <string>
#include <iostream>

//TODO once the program becomes more complex I will need a decorator class that manages vertex buffer IDs and draw orchestration

VertexArrayObject::VertexArrayObject(ImmutableArray<int>& attribute_lengths) {
    glCreateVertexArrays(1, &_id);
    _attributes = &attribute_lengths;
    std::cout<<std::to_string(_id)<<std::endl;

    //Find the length of the vertex (being the sum of the attribute lengths). Buffers require this information.
    //TODO optionally integrate the binding loop into this onee. probably not good idea because I think vertices are needed before binding.
    //_vertex_length = _attributes->get_pointer()[0];
    //size_t num_attrs = _attributes->get_size() / sizeof(int);
    //for (int i = 1; i < num_attrs; i++) {
    //    _vertex_length += _attributes->get_pointer()[i];
    //}
_vertex_length = 6;
    //this->bind();
}

VertexArrayObject::~VertexArrayObject() {
    glDeleteVertexArrays(1, &_id);
}

void VertexArrayObject::bind() {

    //Read the loop first to understand this variable.
    //The offset needed to specify the beginning of a vertex attribute IS the sum of the attribute lengths we've already iterated
    int current_attr_sum = 0;

    //size_t num_attrs = _attributes->get_size() / sizeof(int);
    int num_attrs = 2;
    for (int a = 0; a < num_attrs; a++) {
        int current_attr = 3;
	
        glEnableVertexArrayAttrib(_id, a);
	glVertexArrayAttribBinding(_id, a, 0);
        glVertexArrayAttribFormat(_id, a, current_attr, GL_FLOAT, GL_FALSE, current_attr_sum * sizeof(float)); //sizeof float because we're actually buffering floats

	current_attr_sum += current_attr;
    } 
}

GLuint VertexArrayObject::get_id() {
    return _id;
}

/*
const ImmutableArray<int>& get_attributes() {
    return &_attributes;
}
*/

int VertexArrayObject::get_vertex_length() {
    return _vertex_length;
}

size_t VertexArrayObject::get_num_attrs() {
    return _attributes->get_size() / sizeof(int);
}

void VertexArrayObject::partial_bind() {
    glBindVertexArray(_id);
}
