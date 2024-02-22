#include <iostream>
#include <memory>
#include <tuple>

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "include/BoundArray.hpp"
#include "include/entities.hpp"
#include "include/components.hpp"
#include "include/shader.hpp"
#include "include/types.hpp"
#include "include/world.hpp"
#include "types.hpp"
#include "entities.hpp"
#include "world.hpp"
#include "systems.hpp"
#include "compile_init.hpp"

using namespace geoviz;

int main(int argc, char* argv[]) {

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

    GLuint program = glCreateProgram();
    GLuint vs = glCreateShader(basic_vertex_shader.type);
    const char* vsdata = basic_vertex_shader.source.data();
    glShaderSource(vs, 1, &vsdata, NULL);
    glCompileShader(vs);
    glAttachShader(program, vs);

    GLuint fs = glCreateShader(basic_fragment_shader.type);
    const char* fsdata = basic_fragment_shader.source.data();
    glShaderSource(fs, 1, &fsdata, NULL);
    glCompileShader(fs);
    glAttachShader(program, fs);

    glLinkProgram(program);

    constexpr CompileWorld<world_types> w(
        // wrapper for all entities
        std::make_tuple(
            // instance of an entity
            std::make_tuple(
                Mesh(
                    std::array<float_t, 15>({-0.5f, -0.5f, 1.0f, 0.0f, 0.0, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f}),
                    std::array<uint_t, 3>({0, 1, 2})
                )
            )
        ),
        // wrapper for all systems
        std::make_tuple()
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
    BoundArray<Entity> ees = w.template get_entities_by<Mesh>();

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

    glDeleteProgram(program);

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
