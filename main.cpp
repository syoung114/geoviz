#include <iostream>
#include <SDL3/SDL.h>
#include <memory>
#include <tuple>

#include "include/entities.hpp"
#include "include/state_components.hpp"
#include "include/types.hpp"
#include "types.hpp"
#include "entities.hpp"
#include "world.hpp"

using namespace geoviz;

int main(int argc, char* argv[]) {
    constexpr geoviz::World<geoviz::Entity::PLAYER> w(
        std::make_tuple(
            geoviz::Mesh(
                std::array<geoviz::float_t, 6>({-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f}),
                std::array<geoviz::uint_t, 3>({0, 1, 2})
            )
        )
    );
    std::cout<<"slkdfjdslk\n";

    std::unique_ptr<Mesh> a = w.template get_component<Entity::PLAYER, Mesh>();
    if (a) {
        for (size_type i = 0; i < a->vertices.size(); i++) {
            a->vertices[i] += 1.0f;
            std::cout<<std::to_string(a->vertices[i])<<'\n';
        }
    }
    else {
        std::cout<<"pee\n";
    }
}
