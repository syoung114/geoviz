#include <algorithm>
#include <cstddef>
#include <stdexcept>

#include "core/Geomodel.h"

bool Geomodel::concat(const Geomodel& other) {
    if (!std::equal(_attr_layout.begin(), _attr_layout.begin() + _attr_layout.size(), other.get_attribute_layout().begin())) {
        return false;
    }
    vertices.insert(vertices.end(), other.vertices.begin(), other.vertices.end());

    //concatAndAccumulate :: [Int] -> [Int] -> [Int]
    //concatAndAccumulate xs ys = scanl1 (+) (xs ++ ys)
    
    //get the highest index in this model which will be the reference point for concatenating the indices of the other model
    GLuint max = indices.size() > 0
        ? *std::max_element(indices.begin(), indices.end()) + 1
        : 0;
    
    //now that the other model's indices are relative, actually add them to this one
    indices.reserve(indices.size() + other.indices.size());
    for (size_t i = 0; i < other.indices.size(); i++) {
        indices.push_back(other.indices.at(i) + max);
    }    

    return true;
}

void Geomodel::translate(GLfloat x, GLfloat y, GLfloat z) {
    for (size_t i = 0; i < vertices.size(); i += _vertex_length) {
        vertices[i] += x;
        vertices[i+1] += y;
        vertices[i+2] += z;
    }
}
