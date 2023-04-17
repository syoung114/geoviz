#include "GLProgram.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>

/**
* Creates a openGL program
* @shaders The final shaders to be used in the program.
*/
GLProgram::GLProgram(std::vector<GLuint> &shaders) {
    this->_program = glCreateProgram();
    
    //Loop through the shaders and attach them to the program
    for (const auto &shader : shaders) {
        glAttachShader(this->_program, shader);
    }

    glLinkProgram(this->_program);
}
GLProgram::~GLProgram() {
    glDeleteProgram(this->_program);
}

void GLProgram::use_program() {
    glUseProgram(this->_program);
}

void GLProgram::set_uniform_mat4fv(std::string uniform, glm::mat4 mat) {
    int loc = glGetUniformLocation(this->_program, uniform.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}
