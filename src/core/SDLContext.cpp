#include "core/SDLContext.h"

#include <string>
#include <glad/glad.h>
#include <SDL3/SDL.h>

#include "exception/GLInitException.h"

#include "core/Renderer.h"

SDLContext::SDLContext(int width, int height, std::string title) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      throw GLInitException();
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    _window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_OPENGL);
    if (!_window) {
        throw GLInitException();
    }

    _context = SDL_GL_CreateContext(_window);
    if (_context == NULL || _context == nullptr) {
        throw GLInitException();
    }

    _width = width;
    _height = height;

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

int SDLContext::run() {
    //two loops for two functions: the first loop is the program loop and the second is for polling external events from SDL and handling them respectively.
    glViewport(0, 0, _width, _height); 
    while (true) {
        while (SDL_PollEvent(&_wevent)) {
            if (_wevent.type == SDL_EVENT_QUIT) {
                goto done_here; //yeah yeah, 'unga bunga goto bad'. This solution has the least lines if I add more logic in/around these loops. Do you really want to read all those boolean checks and break statements for the 'correct way'?
            }
            //insert more global checks here... else if (bla bla) {}
            else {
                this->frame_update(); //for interactive behaviour, includes draw call
            }
        }
        SDL_GL_SwapWindow(_window);
    }
    done_here:
    return 0;
}
