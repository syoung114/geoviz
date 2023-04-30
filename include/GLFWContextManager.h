#ifndef GLFW_CONTEXT_MANAGER_H
#define GLFW_CONTEXT_MANAGER_H

#include "GLFWwindowArgs.h"
#include "Renderer.h"

#include <GLFW/glfw3.h>

class GLFWContextManager {
    //private:
    public:
        GLFWwindow *_window;
    
        int _width;
        int _height;

    //public:
        Renderer *_renderer;
        double _mouse_last_x;
        double _mouse_last_y;

        bool _mouse_down;
        
        GLFWContextManager(GLFWwindowArgs &window);

        ~GLFWContextManager();
        
        void set_renderer(Renderer &renderer);

        int run();

        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

        static void mouse_position_callback(GLFWwindow* window, double x, double y);
};

#endif
