#ifndef SDL_CONTEXT_MANAGER_H
#define SDL_CONTEXT_MANAGER_H

#include "../exception/GLInitException.h"
#include "Renderer.h"
#include <string>
#include <glad/glad.h>
#include <SDL3/SDL.h>

/**
 * Abstract superclass that manages boring SDL details. User input and runtime logic is delegated to derived classes.
 */
template<typename Derived>
class SDLContext {
    private:
        SDL_Window *_window;
        SDL_GLContext _context;
    
    public:
        int _width;
        int _height;

        SDL_Event _wevent;
        
        SDLContext(int width, int height, std::string title) {
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
        ~SDLContext() {
            SDL_GL_DeleteContext(_context);
            SDL_DestroyWindow(_window);
            SDL_Quit();
        }

        /**
         * Polymorphic interface to the rendering loop.
         */
        int run(Renderer& renderer) {
            //two loops for two functions: the first loop is the program loop and the second is for polling external events from SDL and handling them respectively.
            glViewport(0, 0, _width, _height); 
            while (true) {
                while (SDL_PollEvent(&_wevent)) {
                    switch (_wevent.type) {
                        case SDL_EVENT_QUIT:
                            goto break_all;
                        default:
                            this->frame_update(renderer);
                    }
                }
                SDL_GL_SwapWindow(_window);
            }
            break_all:
            return 0;
        }

        /**
         * The arbitrary logic contained within the render loop.
         */
        void frame_update(Renderer& renderer) {
            static_cast<Derived*>(this)->frame_update(renderer);
        }

};

#endif
