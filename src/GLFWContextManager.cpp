#include "GLFWContextManager.h"

#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLInitException.h"
#include "GLFWwindowArgs.h"

#include "Renderer.h"

GLFWContextManager::GLFWContextManager(GLFWwindowArgs &window) {
    if (!glfwInit()) {
      throw GLInitException();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    _window = glfwCreateWindow(window.width, window.height, window.title, NULL, NULL);
    if (!_window) {
        throw GLInitException();
    }
    glfwMakeContextCurrent(_window);

    _width = window.width;
    _height = window.height;

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        //std::cout << "Glad has failed to init\n";
        throw GLInitException();
    }

    glfwSetWindowUserPointer(_window, this);

    glfwSetMouseButtonCallback(_window, mouse_button_callback);
    glfwSetCursorPosCallback(_window, mouse_position_callback);

}
GLFWContextManager::~GLFWContextManager() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void GLFWContextManager::set_renderer(Renderer &renderer) {
    this->_renderer = &renderer;
}

int GLFWContextManager::run() {
    while (!glfwWindowShouldClose(_window)) {
        glfwGetFramebufferSize(_window, &_width, &_height);
        glViewport(0, 0, _width, _height); 
        _renderer->draw(_width, _height);
        
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
    return 0;
}

void GLFWContextManager::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    GLFWContextManager *instance = static_cast<GLFWContextManager*>((void*)glfwGetWindowUserPointer(window));
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            instance->_mouse_down = true;
            glfwGetCursorPos(instance->_window, &(instance->_mouse_last_x), &(instance->_mouse_last_y));
        }
        else if (action == GLFW_RELEASE) {
            instance->_mouse_down = false;
        }
    }
}

void GLFWContextManager::mouse_position_callback(GLFWwindow* window, double x, double y) {
    GLFWContextManager *instance = static_cast<GLFWContextManager*>((void*)glfwGetWindowUserPointer(window));
    if (instance->_mouse_down) {
        double current_x;
        double current_y;
        glfwGetCursorPos(instance->_window, &current_x, &current_y);

        float delta_x = static_cast<float>(current_x - instance->_mouse_last_x);
        float delta_y = static_cast<float>(current_y - instance->_mouse_last_y);

        
        glm::mat4 rotate_x = glm::mat4(1.0f);
        rotate_x = glm::rotate(rotate_x, glm::radians(delta_x), glm::vec3(0.0, 1.0f, 0.0));
        instance->_renderer->mult_world_matrix(rotate_x);

        glm::mat4 rotate_y = glm::mat4(1.0f);
        rotate_y = glm::rotate(rotate_y, glm::radians(delta_y), glm::vec3(1.0f, 0.0, 0.0));
        instance->_renderer->mult_world_matrix(rotate_y);

        instance->_mouse_last_x = current_x;
        instance->_mouse_last_y = current_y;
    }
}
