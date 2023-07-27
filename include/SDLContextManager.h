#ifndef GLFW_CONTEXT_MANAGER_H
#define GLFW_CONTEXT_MANAGER_H

#include "GLFWwindowArgs.h"
#include "Renderer.h"

#include <SDL3/SDL.h>

class SDLContextManager {
    private:
    // public:
        SDL_Window *_window;
        SDL_GLContext _context;
        SDL_Event _wevent;
    
        int _width;
        int _height;

    public:
        Renderer *_renderer;
        double _mouse_last_x;
        double _mouse_last_y;

        bool _mouse_down;
        
        SDLContextManager(GLFWwindowArgs &window);

        ~SDLContextManager();
        
        void set_renderer(Renderer &renderer);

        int run();
};

#endif
