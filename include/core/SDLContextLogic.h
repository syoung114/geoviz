#ifndef SDL_CONTEXT_LOGIC_H
#define SDL_CONTEXT_LOGIC_H

#include <string>
#include "SDLContext.h"

#include <SDL3/SDL.h>

class SDLContextLogic : public SDLContext {
    private:
	bool _mouse_down;
	double _mouse_last_x;
	double _mouse_last_y;
    public:
	~SDLContextLogic(){}
        SDLContextLogic(int width, int height, std::string title) : SDLContext(width, height, title) {
	    _mouse_down = false;
	    _mouse_last_x = 0.0;
	    _mouse_last_y = 0.0;
	}
	void frame_update() override;

};

#endif
