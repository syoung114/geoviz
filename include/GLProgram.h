#ifndef GL_PROGRAM_H
#define GL_PROGRAM_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

class GLProgram {
    private:
        GLuint _program;
    public:
        GLProgram(std::vector<GLuint> &shaders);

        ~GLProgram();

        void use_program();

        void set_uniform_mat4fv(std::string uniform, glm::mat4 mat);
};

#endif
