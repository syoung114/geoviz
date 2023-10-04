#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <iostream>

#include "Geomodel.h"
#include "ImmutableArray.h"

Geomodel::Geomodel(int parts_per_attribute, int stride) {
    _attribute_shape = parts_per_attribute;
    _stride = stride;
    _num_parts = 0;
};

Geomodel::Geomodel(int parts_per_attribute, int stride, const std::vector<float> verts, const std::vector<GLuint> indices) {
    _attribute_shape = parts_per_attribute;
    _stride = stride;
    _num_parts = 1;
    _vertices = verts;
    _indices = indices;
};

void Geomodel::_concat(ImmutableArray<float> other_verts, ImmutableArray<GLuint> other_inds) {
    //concat the vertices
    size_t num_other_verts = other_verts.get_size()/sizeof(float);
    _vertices.reserve(_vertices.size() + num_other_verts);
    for (size_t i = 0; i < num_other_verts; i++) {
        _vertices.push_back(other_verts.get_pointer()[i]);
    }
    
    //Process the indices. Special atteention is need to make the indices of the other model now relative to this one.
    //First we need some variables and locality optimizations
    GLuint* other_inds_ptr = other_inds.get_pointer();
    size_t num_other_indices = other_inds.get_size()/sizeof(GLuint);
   
    //get the highest index in this model which will be the reference point for concatenating the indices of the other model
    GLuint max = _indices.size() > 0
        ? *std::max_element(_indices.begin(), _indices.end()) + 1
        : 0;
    
    //now that the other model's indices are relative, actually add them to this one
    _indices.reserve(_indices.size() + num_other_indices);
    for (size_t i = 0; i < num_other_indices; i++) {
        _indices.push_back(other_inds_ptr[i] + max);
    }

    _num_parts++;
}

void Geomodel::concat(Geomodel other) {
    if (_attribute_shape != other.get_parts_per_attribute() || _stride != other.get_stride()) {
        throw std::runtime_error("Geomodel attribute buffer mismatch");
    }
    _concat(other.get_vertices(),other.get_indices());
}

size_t Geomodel::num_children() {
    return _num_parts;
}

int Geomodel::get_parts_per_attribute() {
    return _attribute_shape;
}

int Geomodel::get_stride() {
    return _stride;
}

ImmutableArray<float> Geomodel::get_vertices() {
    ImmutableArray<float> a(_vertices.data(), _vertices.size() * sizeof(float));
    return a;
}

ImmutableArray<GLuint> Geomodel::get_indices() {
    ImmutableArray<GLuint> a(_indices.data(), _indices.size() * sizeof(GLuint));
    return a;
}

void Geomodel::translate(float x, float y, float z) {
    for (size_t i = 0; i < _vertices.size(); i += get_stride()) {
        _vertices[i] += x;
        _vertices[i+1] += y;
        _vertices[i+2] += z;
    }
}
