#ifndef GL_PROGRAM_H
#define GL_PROGRAM_H

#include <glad/glad.h>

#include <string>
#include <vector>

class GLProgram {
    private:
        GLuint _program;
    public:
        GLProgram(std::vector<GLuint> &shaders);

        ~GLProgram();

        void use_program();
};

#endif
