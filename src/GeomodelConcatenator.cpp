#include "Geomodel.h"
#include "ImmutableArray.h"
#include "GeomodelConcatenator.h"

void GeomodelConcatenator::concat(Geomodel geomodel) {
    _vertices.insert(_vertices.end(), geomodel.vertices.begin(), geomodel.vertices.end());
    _indices.insert(_indices.end(), geomodel.indices.begin(), geomodel.indices.end());
}

ImmutableArray<float> GeomodelConcatenator::get_vertices() {
    ImmutableArray<float> a(_vertices.data(), _vertices.size() * sizeof(float));
    return a;
}

ImmutableArray<GLuint> GeomodelConcatenator::get_indices() {
    ImmutableArray<GLuint> a(_indices.data(), _indices.size() * sizeof(GLuint));
    return a;
}