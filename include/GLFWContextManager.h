#ifndef GLFW_CONTEXT_MANAGER_H
#define GLFW_CONTEXT_MANAGER_H

#include "GLFWwindowArgs.h"
#include "Renderer.h"

#include <GLFW/glfw3.h>

class GLFWContextManager {
    private:
        GLFWwindow *_window;
        Renderer *_renderer;
    
        int _width;
        int _height;    
    
    public:
        GLFWContextManager(GLFWwindowArgs &window);

        ~GLFWContextManager();
        
        void set_renderer(Renderer &renderer);

        int run();
};

#endif
