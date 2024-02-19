#pragma once

#include "components.hpp"
#include "types.hpp"

namespace geoviz {

    enum class Entity : size_type {
        PLAYER = 0
    };

    template<Entity e>
    struct EntityComponent;

    #define M_NEW_COMPONENTS(name, ...) \
        template<> \
        struct EntityComponent<Entity::name> { \
            using type = std::tuple<__VA_ARGS__>; \
        };

    M_NEW_COMPONENTS(PLAYER, Mesh)//, TransformComponent)
}
