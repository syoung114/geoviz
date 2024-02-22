#pragma once

#include "entities.hpp"
#include "components.hpp"
#include "systems.hpp"

namespace geoviz {
    template<typename T>
    concept IsSystem = true;

    template<Entity...entities_t>
    struct EntitiesWrap {};

    template<typename Entity>
    struct EntityTuple;

    template<Entity...entities_t>
    struct EntityTuple<EntitiesWrap<entities_t...>> {
        using type = std::tuple<typename EntityComponent<entities_t>::type...>;
    };

    template<IsSystem...systems_t>
    struct SystemsWrap {};

    template<typename System>
    struct SystemsTuple;

    template<IsSystem...systems_t>
    struct SystemsTuple<SystemsWrap<systems_t...>> {
        using type = std::tuple<systems_t...>;
    };

    template<typename Entities, typename Systems>
    class CompileWorldTypes;

    template<Entity...entities_t, IsSystem...systems_t>
    struct CompileWorldTypes<EntitiesWrap<entities_t...>, SystemsWrap<systems_t...>> {
        using Entities = EntitiesWrap<entities_t...>;
        using Systems = SystemsWrap<systems_t...>;
    };

    using world_types = CompileWorldTypes<EntitiesWrap<Entity::PLAYER>, SystemsWrap<>>;
}
