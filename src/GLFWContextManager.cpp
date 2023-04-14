#include "GLFWContextManager.h"

#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GLFWInitException.h"
#include "GLFWwindowArgs.h"
#include "Color.h"

#include "Renderer.h"

GLFWContextManager::GLFWContextManager(GLFWwindowArgs &window, Renderer &renderer) {
    if (!glfwInit()) {
      throw GLFWInitException();
    }

    this->_renderer = &renderer;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    this->_window = glfwCreateWindow(window.width, window.height, window.title, NULL, NULL);
    if (!this->_window) {
        throw GLFWInitException();
    }
    glViewport(0, 0, window.width, window.height);
    glfwMakeContextCurrent(this->_window); 
}
GLFWContextManager::~GLFWContextManager() {
    glfwDestroyWindow(this->_window);
    glfwTerminate();
}

int GLFWContextManager::run() {
    while (!glfwWindowShouldClose(_window)) { 
        //glUseProgram(this->_program.get_program());
        //glBindVertexArray(this->_program.get_gl_vertex_array());
        this->_renderer->draw();
        glfwSwapBuffers(this->_window);
        glfwPollEvents();
    }
    return 0;
}
