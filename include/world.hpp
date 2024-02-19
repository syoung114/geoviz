#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

#include "BoundArray.hpp"
#include "components.hpp"
#include "types.hpp"
#include "entities.hpp"

namespace geoviz {

    template<typename T>
    struct is_tuple : std::false_type {};

    template<typename... Args>
    struct is_tuple<std::tuple<Args...>> : std::true_type {};

    template<typename T>
    inline constexpr bool is_tuple_v = is_tuple<T>::value;

    template<typename T>
    concept IsTuple = is_tuple_v<T>;


    template<Entity... entities_t>
    class CompileWorld {
        private:
            //constexpr uint_t entity_count = sizeof...(entities);
            std::tuple<typename EntityComponent<entities_t>::type...> _world;

        public:
            template<typename... EC>
            consteval CompileWorld(EC&&... entitycomponents)
                : _world(std::make_tuple(std::forward<EC>(entitycomponents)...))
            {
                // prepare searching for any/all elements so it's efficient later on
                //( ..., (void)_world_cache_search<decltype(entities)>(entities) );
            }

            template<Entity entity, IsComponent Cmp>
            std::unique_ptr<Cmp> get_component() const {
                using ec = typename EntityComponent<entity>::type;

                ec inner_tuple = _world_cache_search<entity>();
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
                // this one iterates the entire _world tuple

                if constexpr (Index >= std::tuple_size_v<decltype(_world)>) {
                    return make_bound(entities.data(), entities.size());
                }
                else {
                    auto inner_tuple = std::get<Index>(_world);

                    std::optional<size_type> result = _get_component_opt<
                            typename EntityComponent<static_cast<Entity>(Index)>::type,
                            Cmp
                        >(
                            inner_tuple
                            //std::get<Index>(_world)
                        );

                    if (result.has_value()) {
                        entities.push_back(static_cast<Entity>(Index));
                    }
                    return _get_entities_by<Cmp, Index+1>(std::move(entities));
                }
            }

            template<Entity instance>
            constexpr typename EntityComponent<instance>::type _world_cache_search() const {
                return std::get<
                    // Convert this entity to the respective index in the tuple.
                    static_cast<std::underlying_type_t<Entity>>(instance)
                >(_world);
            }
    };

} // namespace geoviz
