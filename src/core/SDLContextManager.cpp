#include "SDLContextManager.h"

#include <string.h>

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLInitException.h"
#include "GLFWwindowArgs.h"

#include "Renderer.h"

SDLContextManager::SDLContextManager(GLFWwindowArgs &window) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      throw GLInitException();
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    _window = SDL_CreateWindow(window.title, window.width, window.height, SDL_WINDOW_OPENGL);
    if (!_window) {
        throw GLInitException();
    }

    _context = SDL_GL_CreateContext(_window);
    if (_context == NULL) {
        throw GLInitException();
    }

    _width = window.width;
    _height = window.height;

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        throw GLInitException();
    }

    // SDL_SetWindowData(_window, "ContextManager", this);

}
SDLContextManager::~SDLContextManager() {
    SDL_GL_DeleteContext(_context);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void SDLContextManager::set_renderer(Renderer &renderer) {
    this->_renderer = &renderer;
}

int SDLContextManager::run() {
    while (true) {
        // Check for user quit
        while (SDL_PollEvent(&_wevent)) {
            if (_wevent.type == SDL_EVENT_QUIT) {
                goto run_inf_end;
            }
            else if (_wevent.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                if (_wevent.button.button == SDL_BUTTON_LEFT) {
                    _mouse_down = true;
                    _mouse_last_x = _wevent.button.x;
                    _mouse_last_y = _wevent.button.y;
                }
            }
            else if (_wevent.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                if (_wevent.button.button == SDL_BUTTON_LEFT) {
                    _mouse_down = false;
                }
            }
            else if (_wevent.type == SDL_EVENT_MOUSE_MOTION) {
                if (_mouse_down) {
                    float delta_x = static_cast<float>(_wevent.motion.x - _mouse_last_x);
                    float delta_y = static_cast<float>(_wevent.motion.y - _mouse_last_y);

                    glm::mat4 rotate_x = glm::mat4(1.0f);
                    rotate_x = glm::rotate(rotate_x, glm::radians(delta_x), glm::vec3(0.0, 1.0f, 0.0));
                    _renderer->mult_world_matrix(rotate_x);

                    glm::mat4 rotate_y = glm::mat4(1.0f);
                    rotate_y = glm::rotate(rotate_y, glm::radians(delta_y), glm::vec3(1.0f, 0.0, 0.0));
                    _renderer->mult_world_matrix(rotate_y);

                    _mouse_last_x = _wevent.motion.x;
                    _mouse_last_y = _wevent.motion.y;
                }
            }
        }
        glViewport(0, 0, _width, _height); 
        _renderer->draw(_width, _height);
        SDL_GL_SwapWindow(_window);
    }
    run_inf_end:
    return 0;
}