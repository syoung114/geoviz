#include "GLFWContextManager.h"

#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
