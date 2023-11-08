#ifndef GEOMODEL_H
#define GEOMODEL_H

#include <vector>
#include <glad/glad.h>

#include "../util/ImmutableArray.h"

class Geomodel {
    private:
        int _attribute_shape;
        int _stride;
        size_t _num_parts;
        std::vector<float> _vertices;
        std::vector<GLuint> _indices;

        void _concat(ImmutableArray<float> verts, ImmutableArray<GLuint> indices);
  
    public:
        Geomodel(int parts_per_attribute, int stride);
        Geomodel(int parts_per_attribute, int stride, const std::vector<float> verts, const std::vector<GLuint> indices);
        
        void concat(Geomodel& other);
  
        size_t num_children();
        int get_parts_per_attribute();
        int get_stride();
        ImmutableArray<float> get_vertices();
        ImmutableArray<GLuint> get_indices();

        void translate(float x, float y, float z);
        // Geomodel(std::vector<float> verts, std::vector<GLuint> indcs);
};

#endif
