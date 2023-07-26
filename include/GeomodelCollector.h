#ifndef GEOMODEL_COLLECTOR_H
#define GEOMODEL_COLLECTOR_H

#include <vector>

#include "Geomodel.h"
#include "ImmutableArray.h"

/**
 * Wrapper class that collates homogeneously-structured `Geomodel`s into a single vector for buffering
*/
class GeomodelCollector {
    
    private:
        std::vector<float> _vertices;
        std::vector<GLuint> _indices;
    public:
        GeomodelCollector();
        void append(Geomodel model);
        ImmutableArray<float> get_vertices;
        ImmutableArray<GLuint> get_indices;
};

#endif