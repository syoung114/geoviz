#ifndef VERTEX_BUILDER_H
#define VERTEX_BUILDER_H

#include <vector>

class VertexBuilder {
    private:
        std::vector<float> _internal;
        int _stride;
    public:
        VertexBuilder* start(int dimensionality, int positions_len, float *positions);

        /**
         * Adds another component to each vertex.
         */
        VertexBuilder* concat(int stride, std::vector<float> another);

        /**
         * Adds another component to each vertex.
         */
        VertexBuilder* concat(int stride, int another_len, float *another);

        /**
         * Returns the number of bytes contained
         */
        int size();

        /**
         * Complete building and return a usable array pointer
         */
        float* finish();
};

#endif
