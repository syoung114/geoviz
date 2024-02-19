#pragma once

#include <cmath>
#include <variant>
#include <array>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "types.hpp"

namespace geoviz {

    struct Component {};

    struct Mesh : public Component {
        std::array<float_t, 6> vertices;
        std::array<uint_t, 3> indices;

        constexpr Mesh(std::array<float_t, 6>&& verts, std::array<uint_t, 3>&& inds)
            : vertices(std::move(verts)),
              indices(std::move(inds))
        {}
    };

    struct Transform : public Component {
        // https://upload.wikimedia.org/wikipedia/commons/thumb/2/2c/2D_affine_transformation_matrix.svg/1024px-2D_affine_transformation_matrix.svg.png
        // although I can just store the matrix directly, it's not transparent.
        glm::vec4 rotation;
        glm::vec3
            translation,
            scale
        ;
    };

    struct Render : public Component {
        GLuint
            vao,
            vbo,
            ebo
        ;
    };

    template<typename C>
    concept IsComponent = std::is_base_of_v<Component, C>;

} // namespace geoviz
