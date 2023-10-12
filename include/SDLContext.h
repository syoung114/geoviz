#ifndef GLFW_CONTEXT_MANAGER_H
#define GLFW_CONTEXT_MANAGER_H

#include "GLFWwindowArgs.h"
#include "Renderer.h"

#include <SDL3/SDL.h>
#include <functional>
class SDLContext {
    private:
        SDL_Window *_window;
        SDL_GLContext _context;
    
        int _width;
        int _height;

    protected:
        SDL_Event _wevent;
        Renderer *_renderer;
        
	SDLContext(GLFWwindowArgs &window);
        
        int _run(std::function<void()> fn);

    public:
        virtual ~SDLContext();
        void set_renderer(Renderer &renderer);
	virtual void frame_update() = 0;

};

#endif
