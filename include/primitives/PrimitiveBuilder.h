#ifndef PRIMITIVE_BUILDER_H
#define PRIMITIVE_BUILDER_H

#include "../core/Geomodel.h"

class PrimitiveBuilder {
    public:
        static inline Geomodel cube(float x, float y, float z);
        static inline Geomodel cube(float x, float y, float z, float r, float g, float b);
        static inline Geomodel cube(float x, float y, float z, float r, float g, float b, float w, float h, float l);
};

#endif
