#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GLFWInitException.h"
#include "GLFWwindowArgs.h"
#include "Color.h"

#include "Renderer.cpp"

class GLFWContextManager {
    private:
        GLFWwindow *_window;
        Renderer *_renderer;
    public:
        GLFWContextManager(const GLFWwindowArgs &window, const Renderer &renderer) {
            if (!glfwInit()) {
              throw GLFWInitException();
            }

            this->_program = program;
            this->_renderer = renderer;

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            
            _window = glfwCreateWindow(window.width, window.height, window.title, NULL, NULL);
            //_process = process;
            if (!_window) {
                throw GLFWInitException();
            }
            glViewport(0, 0, window.width, window.height);
            glfwMakeContextCurrent(this->_window); 
        }
        ~GLFWContextManager() {
            glfwDestroyWindow(this->_window);
            glfwTerminate();
        }

        int run() {
            while (!glfwWindowShouldClose(_window)) { 
                //glUseProgram(this->_program.get_program());
                //glBindVertexArray(this->_program.get_gl_vertex_array());
                this->_renderer->draw();
                glfwSwapBuffers(this->_window);
                glfwPollEvents();
            }
            return 0;
        }

};
