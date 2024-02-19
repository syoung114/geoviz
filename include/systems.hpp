#pragma once

#include <glad/glad.h>

#include "types.hpp"
#include "world.hpp"

namespace geoviz {
    
    template<typename Derived>
    struct System {
        template<template <class> StaticWorld world_t>
        void update(float_t dt, world_t& world) {
            static_cast<Derived*>(this)->update(dt, world);
        }
    };

    class Renderer : System<Renderer> {
        public:
            template<template <class> StaticWorld world_t>
            void update(float_t dt, world_t& world) {
                // "le functional" call of glClearColor
                std::apply(glClearColor, *(world.get_component<Entity::RENDER_PROPERTIES, ClearColor>()));

                auto render_ec = world.get_components<Render>();
            }
    };
}
