#include "GLProgram.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>

#include <ShaderFile.h>

/**
* Creates a openGL program
* @shaders The final shaders to be used in the program.
*/
GLProgram::GLProgram(std::vector<ShaderFile> shaders) {
    _program = glCreateProgram();
    
    //Loop through the shaders and attach them to the program
    for (const ShaderFile &file : shaders) {
        GLuint shader = _create_shader(file);
        glAttachShader(_program, shader);
    }

    glLinkProgram(_program);
}
GLProgram::~GLProgram() {
    glDeleteProgram(_program);
}

void GLProgram::use_program() {
    glUseProgram(_program);
}

void GLProgram::set_uniform_mat4fv(std::string uniform, glm::mat4 mat) {
    //Get the index of the matrix uniform and knowing it, assign the new value
    int loc = glGetUniformLocation(_program, uniform.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

GLuint GLProgram::_create_shader(const ShaderFile &file) {
    GLuint shader = glCreateShader(file.get_type());
    std::string str = file.get_source();
    const char* shader_source_ptr = str.c_str();
    glShaderSource(shader, 1, &shader_source_ptr, NULL);
    glCompileShader(shader);
    return shader;
}
