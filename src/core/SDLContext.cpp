#include "SDLContext.h"

#include <functional>

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLInitException.h"
#include "GLFWwindowArgs.h"

#include "Renderer.h"

SDLContext::SDLContext(GLFWwindowArgs &window) {
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

}
SDLContext::~SDLContext() {
    SDL_GL_DeleteContext(_context);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void SDLContext::set_renderer(Renderer &renderer) {
    this->_renderer = &renderer;
}

int SDLContext::_run(std::function<void()> fn) {
  //two loops for two functions: the first loop is the program loop and the second is for polling external events from SDL and handling them respectively.
  glViewport(0, 0, _width, _height); 
  while (true) {
        // Check for user quit
        while (SDL_PollEvent(&_wevent)) {
            if (_wevent.type == SDL_EVENT_QUIT) {
                goto run_inf_end;
            }
            else {
                fn();
            }
        }
        _renderer->draw(_width, _height);
        SDL_GL_SwapWindow(_window);
    }
    run_inf_end:
    return 0;
}
