#include <algorithm>

#include "Geomodel.h"
#include "ImmutableArray.h"
#include "GeomodelPool.h"

void GeomodelPool::concat(Geomodel geomodel) {
    _vertices.insert(_vertices.end(), geomodel.vertices.begin(), geomodel.vertices.end());

    //We need to convert model-relative indices to absolute indices. Not doing this means all model indices count from zero, which is not the case for rendering multiple objects.
    GLuint max = _indices.size() > 0
        ? *std::max_element(_indices.begin(), _indices.end()) + 1
        : 0;
    std::vector<GLuint> other(geomodel.indices);
    for (int i = 0; i < other.size(); i++) {
        other.at(i) += max;
    }
    _indices.insert(_indices.end(), other.begin(), other.end());
}

ImmutableArray<float> GeomodelPool::get_vertices() {
    ImmutableArray<float> a(_vertices.data(), _vertices.size() * sizeof(float));
    return a;
}

ImmutableArray<GLuint> GeomodelPool::get_indices() {
    ImmutableArray<GLuint> a(_indices.data(), _indices.size() * sizeof(GLuint));
    return a;
}