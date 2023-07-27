#include "SDLContextManager.h"

#include <string.h>

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLInitException.h"
#include "GLFWwindowArgs.h"

#include "Renderer.h"

SDLContextManager::SDLContextManager(GLFWwindowArgs &window) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      throw GLInitException();
    }

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 6 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    
    _window = SDL_CreateWindow(window.title, window.width, window.height, SDL_WINDOW_OPENGL);
    if (!_window) {
        throw GLInitException();
    }

    _context = SDL_GL_CreateContext(_window);
    if (_context == NULL) {
        throw GLInitException();
    }

    _width = window.width;
    _height = window.height;

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        //std::cout << "Glad has failed to init\n";
        throw GLInitException();
    }

    SDL_SetWindowData(_window, "ContextManager", this);

    // glfwSetWindowUserPointer(_window, this);

    // glfwSetMouseButtonCallback(_window, mouse_button_callback);
    // glfwSetCursorPosCallback(_window, mouse_position_callback);

}
SDLContextManager::~SDLContextManager() {
    SDL_GL_DeleteContext(_context);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void SDLContextManager::set_renderer(Renderer &renderer) {
    this->_renderer = &renderer;
}

int SDLContextManager::run() {
    while (true) {
        // Check for user quit
        if (SDL_PollEvent(&_wevent)) {
            if (_wevent.type == SDL_EVENT_QUIT) {
                break;
            }
        }
        glViewport(0, 0, _width, _height); 
        _renderer->draw(_width, _height);
        SDL_GL_SwapWindow(_window);
    }
    return 0;
}

// void SDLContextManager::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
//     SDLContextManager *instance = static_cast<SDLContextManager*>((void*)glfwGetWindowUserPointer(window));
//     if (button == GLFW_MOUSE_BUTTON_LEFT) {
//         if (action == GLFW_PRESS) {
//             instance->_mouse_down = true;
//             glfwGetCursorPos(instance->_window, &(instance->_mouse_last_x), &(instance->_mouse_last_y));
//         }
//         else if (action == GLFW_RELEASE) {
//             instance->_mouse_down = false;
//         }
//     }
// }

// void SDLContextManager::mouse_position_callback(GLFWwindow* window, double x, double y) {
//     SDLContextManager *instance = static_cast<SDLContextManager*>((void*)glfwGetWindowUserPointer(window));
//     if (instance->_mouse_down) {
//         double current_x;
//         double current_y;
//         glfwGetCursorPos(instance->_window, &current_x, &current_y);

//         float delta_x = static_cast<float>(current_x - instance->_mouse_last_x);
//         float delta_y = static_cast<float>(current_y - instance->_mouse_last_y);

        
//         glm::mat4 rotate_x = glm::mat4(1.0f);
//         rotate_x = glm::rotate(rotate_x, glm::radians(delta_x), glm::vec3(0.0, 1.0f, 0.0));
//         instance->_renderer->mult_world_matrix(rotate_x);

//         glm::mat4 rotate_y = glm::mat4(1.0f);
//         rotate_y = glm::rotate(rotate_y, glm::radians(delta_y), glm::vec3(1.0f, 0.0, 0.0));
//         instance->_renderer->mult_world_matrix(rotate_y);

//         instance->_mouse_last_x = current_x;
//         instance->_mouse_last_y = current_y;
//     }
// }
