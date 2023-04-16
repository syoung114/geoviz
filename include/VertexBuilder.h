#ifndef VERTEX_BUILDER_H
#define VERTEX_BUILDER_H

#include <vector>

class VertexBuilder {
    private:
        std::vector<float> _internal;
        int _stride;
    public:
        VertexBuilder(int dimensionality, int positions_len, float *positions);

        VertexBuilder* concat(int stride, int another_len, float *another);

        float* finish();
};

#endif
