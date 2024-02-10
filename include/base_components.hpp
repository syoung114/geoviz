#pragma once

#include <variant>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "types.hpp"

namespace geoviz {

    struct MeshComponent {
        std::vector<float_t> vertices;
        std::vector<uint_t> indices;
    };

    struct TransformComponent {
        // https://upload.wikimedia.org/wikipedia/commons/thumb/2/2c/2D_affine_transformation_matrix.svg/1024px-2D_affine_transformation_matrix.svg.png
        // although I can just store the matrix directly, it's not transparent.
        glm::vec4 rotation;
        glm::vec3
            translation,
            scale
        ;
    };

    struct RenderComponent {
        GLuint
            vao,
            vbo,
            ebo
        ;
    };

    using component_variant = std::variant<MeshComponent, TransformComponent, RenderComponent>;

} // namespace geoviz
