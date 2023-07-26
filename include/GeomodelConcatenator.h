#ifndef GEOMODEL_COLLECTOR_H
#define GEOMODEL_COLLECTOR_H

#include <vector>

#include "Geomodel.h"
#include "ImmutableArray.h"

/**
 * Wrapper class that collates homogeneously-structured `Geomodel`s into a single vector for buffering
*/
class GeomodelConcatenator {
    
    private:
        std::vector<float> _vertices;
        std::vector<GLuint> _indices;
    public:
        GeomodelConcatenator(){};
        void concat(Geomodel model);
        ImmutableArray<float> get_vertices();
        ImmutableArray<GLuint> get_indices();
};

#endif