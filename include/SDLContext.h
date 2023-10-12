#ifndef GLFW_CONTEXT_MANAGER_H
#define GLFW_CONTEXT_MANAGER_H

#include "GLFWwindowArgs.h"
#include "Renderer.h"

#include <SDL3/SDL.h>

/**
 * Abstract superclass that manages everything about SDL. User input and runtime logic is delegated to derived classes.
 */
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
        
    public:
        virtual ~SDLContext();

        void set_renderer(Renderer &renderer);

	virtual void frame_update() = 0;
	int run(); //not virtual but strongly relies on frame_update.

};

#endif
