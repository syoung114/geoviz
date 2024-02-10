#pragma once

#include "base_components.hpp"
#include "types.hpp"

namespace geoviz {

    // https://stackoverflow.com/a/41900074/8724072
    constexpr auto ENTITY_START_LINE = __LINE__;
    enum class Entity : size_type {
        PLAYER
    };
    constexpr auto ENTITY_COUNT = __LINE__ - ENTITY_START_LINE - 3;

    template<Entity e>
    struct EntityComponents;

    #define M_NEW_COMPONENTS(name, ...) \
        template<> \
        struct EntityComponents<Entity::name> { \
            using type = std::tuple<__VA_ARGS__>; \
        };

    M_NEW_COMPONENTS(PLAYER, MeshComponent)//, TransformComponent)
}
