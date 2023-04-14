#ifndef GLFW_CONTEXT_MANAGER_H
#define GLFW_CONTEXT_MANAGER_H

#include "GLFWwindowArgs.h"
#include "Renderer.h"

#include <GLFW/glfw3.h>

class GLFWContextManager {
    private:
        GLFWwindow *_window;
        Renderer *_renderer;
    public:
        GLFWContextManager(GLFWwindowArgs &window, Renderer &renderer);

        ~GLFWContextManager();

        int run();
};

#endif
