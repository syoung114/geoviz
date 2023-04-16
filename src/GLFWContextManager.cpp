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
    
    this->_window = glfwCreateWindow(window.width, window.height, window.title, NULL, NULL);
    if (!this->_window) {
        throw GLInitException();
    }
    glfwMakeContextCurrent(this->_window); 

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        //std::cout << "Glad has failed to init\n";
        throw GLInitException();
    }

    glViewport(0, 0, window.width, window.height);
}
GLFWContextManager::~GLFWContextManager() {
    glfwDestroyWindow(this->_window);
    glfwTerminate();
}

void GLFWContextManager::set_renderer(Renderer &renderer) {
    this->_renderer = &renderer;
}

int GLFWContextManager::run() {
    while (!glfwWindowShouldClose(this->_window)) { 
        this->_renderer->draw();
        glfwSwapBuffers(this->_window);
        glfwPollEvents();
    }
    return 0;
}
