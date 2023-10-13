#ifndef SDL_CONTEXT_MANAGER_H
#define SDL_CONTEXT_MANAGER_H

#include "SDLWindowArgs.h"
#include "Renderer.h"

#include <SDL3/SDL.h>

/**
 * Abstract superclass that manages boring SDL details. User input and runtime logic is delegated to derived classes.
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
        
	SDLContext(SDLWindowArgs &window);
        
    public:
        virtual ~SDLContext();

        void set_renderer(Renderer &renderer);

	/**
	 * The arbitrary logic contained within the render loop.
	 */
	virtual void frame_update() = 0;

	/**
	 * Polymorphic interface to the rendering loop.
	 */
	int run(); //not virtual but strongly relies on frame_update.

};

#endif
