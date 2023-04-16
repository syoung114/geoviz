#include <vector>
#include <stdexcept>

#include "VertexBuilder.h"

//This class could be made into a template somehow but I don't think that benefits the program

VertexBuilder* VertexBuilder::start(int dimensionality, int positions_len, float *positions) {
    //I usually sort argument lists by importantance but the stride arg would be harder to find after a huge inline array
    this->_internal.assign(positions, positions + positions_len);
    this->_stride = dimensionality;
    return this;
}
//VertexArrayBuilder::~VertexArrayBuilder() {
    //destroy the internal
//}

VertexBuilder* VertexBuilder::concat(int stride, int another_len, float *another) {
    if (!this->_stride || this->_stride == -1) {
        //I assume I will never pass a negative number into the stride arg. I could make it a uint16_t but that is overly cautionary
        throw std::runtime_error("Please run start() before concat()");
    }
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

int VertexBuilder::size() {
    return this->_internal.size() * sizeof(float);
}

float* VertexBuilder::finish() {
    float *result = this->_internal.data();
    this->_internal.clear();
    this->_stride = -1;
    return result;
}

