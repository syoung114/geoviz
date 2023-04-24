#ifndef GL_PROGRAM_H
#define GL_PROGRAM_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "ShaderFile.h"

class GLProgram {
    private:
        GLuint _program;

        GLuint _create_shader(const ShaderFile &file);
    public:
        GLProgram(std::vector<ShaderFile> shaders);

        ~GLProgram();

        void use_program();

        void set_uniform_mat4fv(std::string uniform, glm::mat4 mat);
};

#endif
