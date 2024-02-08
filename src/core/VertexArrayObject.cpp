#include "core/VertexArrayObject.h"

#include <glad/glad.h>

VertexArrayObject::VertexArrayObject(const std::vector<int>& attribute_layout)
    : _attr_layout(&attribute_layout)
{
    glCreateVertexArrays(1, &_id);
}

VertexArrayObject::~VertexArrayObject() {
    glDeleteVertexArrays(1, &_id);
}

void VertexArrayObject::init() {
    //Read the loop first to understand this variable.
    //The offset needed to specify the beginning of a vertex attribute IS the sum of the attribute lengths we've already iterated
    int current_attr_sum = 0;

    for (int a = 0; a < _attr_layout->size(); a++) {
        int current_attr = _attr_layout->at(a);

        glEnableVertexArrayAttrib(_id, a);
        glVertexArrayAttribBinding(_id, a, 0);
        glVertexArrayAttribFormat(_id, a, current_attr, GL_FLOAT, GL_FALSE, current_attr_sum * sizeof(float)); //sizeof float because we're actually buffering floats

        current_attr_sum += current_attr;
    } 
}

void VertexArrayObject::bind() {
    //TODO check if init() has been run. could return a bool if so. not doing now, currently feeling risky.
    glBindVertexArray(_id);
}
