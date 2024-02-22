#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

#include "BoundArray.hpp"
#include "compile_init.hpp"
#include "components.hpp"
#include "systems.hpp"
#include "types.hpp"
#include "entities.hpp"
#include "templates.hpp"

namespace geoviz {

    // forward decl.
    template<typename Types>
    class CompileWorld;

    template<typename Types>
    struct world_ptr_wrapper {
        static CompileWorld<Types>* ptr;
    };

    template<typename Types>
    class CompileWorld {
        private:
            using entities_t = typename Types::Entities;
            using systems_t = typename Types::Systems;
            using entities_tuple = typename EntityTuple<entities_t>::type;
            using systems_tuple = typename SystemsTuple<systems_t>::type;

            using uno_type = decltype(std::tuple_cat(std::declval<entities_tuple>(), std::declval<systems_tuple>()));
            uno_type _uno;
            //constexpr size_type _system_offset = sizeof...(entities_t);

        public:
            template<typename... EC, typename... Sys>
            consteval CompileWorld(std::tuple<EC...>&& entitycomponents, std::tuple<Sys...>&& systems)
                : _uno(std::tuple_cat(std::forward<std::tuple<EC...>>(entitycomponents), std::forward<std::tuple<Sys...>>(systems)))
            {}

            template<Entity entity, IsComponent Cmp>
            std::unique_ptr<Cmp> get_component() const {
                using ec = typename EntityComponent<entity>::type;

                ec inner_tuple = _uno_cache_search<entity>();
                return _get_component_ptr<ec, Cmp>(inner_tuple);
            }

            template<IsComponent Cmp>
            constexpr BoundArray<Entity> get_entities_by() const {
                return _get_entities_by<Cmp>({});
            }

        private:

            #define _M_PVT_GET_COMPONENT_OVERLOAD(name,type,found,null) \
                template<IsTuple Tuple, IsComponent Cmp, size_type Index = 0> \
                constexpr type name(Tuple& t) const { \
                    if constexpr (Index >= std::tuple_size_v<std::remove_reference_t<Tuple>>) { \
                        return null; \
                    } \
                    else { \
                        decltype(auto) element = std::get<Index>(t); \
                        if constexpr (std::is_same_v<std::decay_t<decltype(element)>, Cmp>) { \
                            return found; \
                        } \
                        else { \
                            return _get_component<Tuple, Cmp, Index+1>(t); \
                        } \
                    } \
                }

            _M_PVT_GET_COMPONENT_OVERLOAD(_get_component_ptr, std::unique_ptr<Cmp>, std::make_unique<Cmp>(std::get<Index>(t)), nullptr)

            _M_PVT_GET_COMPONENT_OVERLOAD(_get_component_opt, std::optional<size_type>, std::make_optional(Index), std::nullopt)

            template<IsComponent Cmp, size_type Index=0>
            constexpr BoundArray<Entity> _get_entities_by(std::vector<Entity>&& entities) const {
                // this one iterates the entire _uno tuple

                // TODO need a better way to handle dynamic allocation. I wanted std::vector::release

                if constexpr (Index >= std::tuple_size_v<entities_tuple>) {
                    return make_bound(entities.data(), entities.size());
                }
                else {
                    auto inner_tuple = std::get<Index>(_uno);

                    std::optional<size_type> result = _get_component_opt<
                        //typename EntityComponent<Entity::PLAYER>::type,
                        typename EntityComponent<static_cast<Entity>(Index)>::type,
                        Cmp
                        >(
                        inner_tuple
                        //std::get<Index>(_uno)
                    );

                    if (result.has_value()) {
                        entities.push_back(static_cast<Entity>(Index));
                    }
                    return _get_entities_by<Cmp, Index+1>(std::move(entities));
                }

                //constexpr std::vector<Entity> entities;

                //constexpr auto fn = [&entities, &_uno]<size_type... Ix>(std::index_sequence<Ix...>) {
                //    ([&]{
                //        auto inner_tuple = std::get<Ix>(_uno);
                //        std::optional<size_type> result = _get_component_opt<
                //                typename EntityComponent<static_cast<Entity>(Ix)>::type,
                //                Cmp
                //            >(
                //                inner_tuple
                //                //std::get<Index>(_uno)
                //            );

                //        if (result.has_value()) {
                //            entities.push_back(static_cast<Entity>(Ix));
                //        }
                //    }(), ...);
                //};
                //fn(std::make_index_sequence<std::tuple_size_v<decltype(_uno)>>{});
                //return make_bound(entities.data(), entities.size());
            }

            template<Entity instance>
            constexpr typename EntityComponent<instance>::type _uno_cache_search() const {
                return std::get<
                    // Convert this entity to the respective index in the tuple.
                    static_cast<std::underlying_type_t<Entity>>(instance)
                >(_uno);
            }
    };

} // namespace geoviz
