#ifndef SDL_CONTEXT_LOGIC_H
#define SDL_CONTEXT_LOGIC_H

#include <string>
#include "Renderer.h"
#include "SDLContext.h"


class SDLContextLogic : public SDLContext<SDLContextLogic> {
    private:
        bool _mouse_down;
        double _mouse_last_x;
        double _mouse_last_y;

    public:
        SDLContextLogic(int width, int height, std::string title);

        ~SDLContextLogic();

        void frame_update(Renderer& renderer);

};

#endif
