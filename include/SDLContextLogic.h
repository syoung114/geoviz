#ifndef GLFW_CONTEXT_LOGICH
#define GLFW_CONTEXT_LOGIC_H

#include "GLFWwindowArgs.h"
#include "SDLContext.h"

#include <SDL3/SDL.h>

class SDLContextLogic : public SDLContext {
    private:
	bool _mouse_down;
	double _mouse_last_x;
	double _mouse_last_y;
    public:
	~SDLContextLogic(){}
        SDLContextLogic(GLFWwindowArgs &window) : SDLContext(window) {
	    _mouse_down = false;
	    _mouse_last_x = 0.0;
	    _mouse_last_y = 0.0;
	}
	void frame_update() override;

};

#endif
