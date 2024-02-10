#pragma once

#include <iostream>
#include <tuple>
#include <array>
#include <type_traits>

#include "base_components.hpp"
#include "types.hpp"
#include "entities.hpp"

namespace geoviz {

    template<size_type n=ENTITY_COUNT>
    class World {
        private:
            std::array<std::tuple<component_variant>, n> _world;

        public:
            World()
                : _world({typename EntityComponents<Entity::PLAYER>::type()})
            {
                using T = std::decay_t<decltype(std::get<0>(std::get<0>(_world[0])))>;
                static_assert(std::is_same_v<T, MeshComponent>);
            }

            void printInfo() {
                std::visit(
                    [](auto&& arg) {
                        using T = std::decay_t<decltype(arg)>;
                        if constexpr (std::is_same_v<T, MeshComponent>) {
                            std::cout
                                << "MeshComponent with "
                                << arg.vertices.size()
                                << " vertices and "
                                << arg.indices.size()
                                << " indices.\n";
                        }
                        //else if constexpr (std::is_same_v<T, TransformComponent>) {
                        //    std::cout
                        //        << "TransformComponent with position ("
                        //        << arg.rotation
                        //        << ", "
                        //        << arg.translation
                        //        << ", "
                        //        << arg.scale
                        //        << ").\n"
                        //        ;
                        //}
                        //else if constexpr (std::is_same_v<T, RenderComponent>) {
                        //    std::cout
                        //        << "RenderComponent with textureID "
                        //        << arg.
                        //        << ".\n";
                        //}
                    },
                    std::get<0>(_world[0])
                );
            }
            //{
            //    using components = typename EntityComponents<Entity::PLAYER>::type;
            //    _world = {{components()}};
            //}

            //template<typename Component, Entity e>
            //constexpr auto get_component() {
            //    using components = typename EntityComponents<e>::type;

            //    //if constexpr (std::tuple_size_v<components> != 0) {
            //        for 
            //    //}
            //    //else {
            //        // dynamic resolution
            //    //}
            //}

            //template<typename Component, Entity e>
            //constexpr bool has_component() {
            //    using components = typename EntityComponents<e>::type;

            //    if constexpr(std::tuple_size_v<components> == 0) {
            //        return false;
            //    }


            //}
    };

} // namespace geoviz
