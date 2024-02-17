#pragma once

#include <memory>
#include <optional>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

#include "state_components.hpp"
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


    template<Entity... entities>
    class World {
        private:
            std::tuple<typename EntityComponent<entities...>::type> _world;

        public:
            template<typename... EC>
            consteval World(EC&&... entitycomponents)
                : _world(std::make_tuple(std::forward<EC>(entitycomponents)...))
            {
                // prepare searching for any/all elements so it's efficient later on
                //( ..., (void)_world_cache_search<decltype(entities)>(entities) );
            }

            template<Entity entity, IsComponent Cmp>
            constexpr std::unique_ptr<Cmp> get_component() const {
                using ec = typename EntityComponent<entity>::type;

                ec inner_tuple = _world_cache_search<entity>();
                return _get_component<ec, Cmp>(inner_tuple);
            }

        private:

            template<Entity instance>
            constexpr typename EntityComponent<instance>::type _world_cache_search() const {
                return std::get<
                    // Convert this entity to the respective index in the tuple.
                    static_cast<std::underlying_type_t<Entity>>(instance)
                >(_world);
            }

            template<IsTuple Tuple, IsComponent Cmp, size_type Index = 0>
            constexpr std::unique_ptr<Cmp> _get_component(Tuple& t) const {

                // I don't like using "redundant" elses but for `constexpr if` they're actually
                // important for the compiler to understand what I'm doing. Try to "refactor" them
                // away and you'll get an index out of range error because the compiler doesn't see
                // the recursion stopping conditions properly.

                if constexpr (Index >= std::tuple_size_v<std::remove_reference_t<Tuple>>) {
                    return nullptr;
                }
                else {
                    decltype(auto) element = std::get<Index>(t); // returns Cmp&

                    if constexpr (std::is_same_v<std::decay_t<decltype(element)>, Cmp>) {
                        return std::make_unique<Cmp>(element);
                    }
                    else {
                        return _get_component<Tuple, Cmp, Index+1>(t);
                    }
                }
            }
    };

} // namespace geoviz
