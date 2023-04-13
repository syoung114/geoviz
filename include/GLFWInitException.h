#ifndef GLFW_INIT_EXCEPTION_H
#define GLFW_INIT_EXCEPTION_H

#include <exception>
#include <string>

class GLFWInitException : public std::exception {
    public:
        GLFWInitException() noexcept {}
        virtual const char* what() const noexcept override {
            return "Failed to init GLFW";
        }
};

#endif
