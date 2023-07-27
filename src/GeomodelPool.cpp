#include "Geomodel.h"
#include "ImmutableArray.h"
#include "GeomodelPool.h"

void GeomodelPool::concat(Geomodel geomodel) {
    _vertices.insert(_vertices.end(), geomodel.vertices.begin(), geomodel.vertices.end());
    _indices.insert(_indices.end(), geomodel.indices.begin(), geomodel.indices.end());
}

ImmutableArray<float> GeomodelPool::get_vertices() {
    ImmutableArray<float> a(_vertices.data(), _vertices.size() * sizeof(float));
    return a;
}

ImmutableArray<GLuint> GeomodelPool::get_indices() {
    ImmutableArray<GLuint> a(_indices.data(), _indices.size() * sizeof(GLuint));
    return a;
}