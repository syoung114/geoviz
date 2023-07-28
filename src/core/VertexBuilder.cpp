#include <vector>
#include <stdexcept>

#include "VertexBuilder.h"

//This class could be made into a template somehow but I don't think that benefits the program

VertexBuilder* VertexBuilder::start(int dimensionality, int positions_len, float *positions) {
    //I usually sort argument lists by importantance but the stride arg would be harder to find after a huge inline array
    _internal.assign(positions, positions + positions_len);
    _stride = dimensionality;
    return this;
}
//VertexArrayBuilder::~VertexArrayBuilder() {
    //destroy the internal
//}

VertexBuilder* VertexBuilder::concat(int stride, std::vector<float> another) {
    float *another_ptr = another.data();
    return concat(stride, another.size(), another_ptr);
}

VertexBuilder* VertexBuilder::concat(int stride, int another_len, float *another) {
    if (!_stride || _stride == -1) {
        //I assume I will never pass a negative number into the stride arg. I could make it a uint16_t but that is overly cautionary
        throw std::runtime_error("Please run start() before concat()");
    }
    int next = _stride + stride;
    int another_location = 0;
    for (int i = _stride; another_location < another_len; i += next) {
        for (int j = 0; j < stride; j++) {
            _internal.insert(_internal.begin() + i + j, another[another_location++]);
        }
    }
    _stride = next;
    return this;
}

int VertexBuilder::size() {
    return _internal.size() * sizeof(float);
}

float* VertexBuilder::finish() {
    float *result = _internal.data();
    _internal.clear();
    _stride = -1;
    return result;
}

