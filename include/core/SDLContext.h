#ifndef SDL_CONTEXT_MANAGER_H
#define SDL_CONTEXT_MANAGER_H

#include "Renderer.h"

#include <string>
#include <SDL3/SDL.h>

/**
 * Abstract superclass that manages boring SDL details. User input and runtime logic is delegated to derived classes.
 */
class SDLContext {
    private:
        SDL_Window *_window;
        SDL_GLContext _context;
    
    protected:
        int _width;
        int _height;

        SDL_Event _wevent;
        Renderer *_renderer;
        
        SDLContext(int width, int height, std::string title);
        
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
        int run(); //not virtual but requires frame_update.

};

#endif
