#include <vector>

#include "VertexBuilder.h"

//This class could be made into a template somehow but I don't think that benefits the program

VertexBuilder::VertexBuilder(int dimensionality, int positions_len, float *positions) {
    //I usually sort argument lists by importantance but the stride arg would be harder to find after a huge inline array
    this->_internal.assign(positions, positions + positions_len);
    this->_stride = dimensionality;
}
//VertexArrayBuilder::~VertexArrayBuilder() {
    //destroy the internal
//}

VertexBuilder* VertexBuilder::concat(int stride, int another_len, float *another) {
    int next = this->_stride + stride;
    int another_location = 0;
    for (int i = this->_stride; another_location < another_len; i += next) {
        for (int j = 0; j < stride; j++) {
            this->_internal.insert(this->_internal.begin() + i + j, another[another_location++]);
        }
    }
    this->_stride = next;
    return this;
}

float* VertexBuilder::finish() {
    float *f = &_internal[0];
    return f;
}

