#ifndef GL_INIT_EXCEPTION_H
#define GL_INIT_EXCEPTION_H

#include <exception>
#include <string>

class GLInitException : public std::exception {
    public:
        GLInitException() noexcept {}
        virtual const char* what() const noexcept override {
            return "Failed to init GL";
        }
};

#endif
