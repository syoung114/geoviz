
#include "core/SDLContext.h"
#include "core/SDLContextLogic.h"

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "exception/GLInitException.h"
#include "core/SDLWindowArgs.h"

#include "core/Renderer.h"
#define GLM_FORCE_RADIANS

void SDLContextLogic::frame_update() {
    if (_wevent.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (_wevent.button.button == SDL_BUTTON_LEFT) {
            _mouse_down = true;
            _mouse_last_x = _wevent.button.x;
            _mouse_last_y = _wevent.button.y;
        }
    }
    else if (_wevent.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        if (_wevent.button.button == SDL_BUTTON_LEFT) {
            _mouse_down = false;
        }
    }
    else if (_wevent.type == SDL_EVENT_MOUSE_WHEEL) {
        //Adjust the FOV to create a zoom effect when using the scroll wheel.
	// * Scroll up = higher FOV = zoom out
	// * Scroll down = lower FOV = zoom in
	float fov = _renderer->get_fov();
        if (_wevent.wheel.y > 0 && fov > 0) {
            _renderer->set_fov(fov - glm::radians(1.0f));
	}
	else if (_wevent.wheel.y < 0) {
            _renderer->set_fov(fov + glm::radians(1.0f));
	}
    }
    else if (_wevent.type == SDL_EVENT_MOUSE_MOTION) {
        if (_mouse_down) {
            float delta_x = static_cast<float>(_wevent.motion.x - _mouse_last_x);
            float delta_y = static_cast<float>(_wevent.motion.y - _mouse_last_y);

            glm::mat4 rotate_x = glm::mat4(1.0f);
            rotate_x = glm::rotate(rotate_x, glm::radians(delta_x), glm::vec3(0.0, 1.0f, 0.0));
            _renderer->mult_world_matrix(rotate_x);

            glm::mat4 rotate_y = glm::mat4(1.0f);
            rotate_y = glm::rotate(rotate_y, glm::radians(delta_y), glm::vec3(1.0f, 0.0, 0.0));
            _renderer->mult_world_matrix(rotate_y);

            _mouse_last_x = _wevent.motion.x;
            _mouse_last_y = _wevent.motion.y;
        }
    }    
}
