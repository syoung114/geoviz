#ifndef GEOMODEL_H
#define GEOMODEL_H

#include <vector>
#include <glad/glad.h>

class Geomodel {
    public:
        std::vector<float> vertices;
        std::vector<GLuint> indices;
        Geomodel(){};
        // Geomodel(std::vector<float> verts, std::vector<GLuint> indcs);
};

#endif