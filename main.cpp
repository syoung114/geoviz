#include <iostream>
#include <memory>
#include <tuple>

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "include/entities.hpp"
#include "include/components.hpp"
#include "include/types.hpp"
#include "types.hpp"
#include "entities.hpp"
#include "world.hpp"

using namespace geoviz;

int main(int argc, char* argv[]) {
    constexpr geoviz::CompileWorld<geoviz::Entity::PLAYER> w(
        std::make_tuple(
            geoviz::Mesh(
                std::array<geoviz::float_t, 6>({-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f}),
                std::array<geoviz::uint_t, 3>({0, 1, 2})
            )
        )
    );
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
    w.template get_entities_by<Mesh>();

    int_t width = 512;
    int_t height = 512;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout<<"she no good 1\n";
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    std::string title = "geoviz";
    SDL_Window* window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_OPENGL);
    if (!window) {
        std::cout<<"she no good 2\n";
        return 1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == NULL || context == nullptr) {
        std::cout<<"she no good 3\n";
        return 1;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cout<<"she no good 4\n";
        return 1;
    }

    glViewport(0,0,width,height);
    SDL_Event wevent;
    while (true) {
        while (SDL_PollEvent(&wevent)) {
            switch(wevent.type) {
                case SDL_EVENT_QUIT:
                    goto break_all;
            }
        }
        SDL_GL_SwapWindow(window);
    }
    break_all:

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
