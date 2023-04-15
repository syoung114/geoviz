#include "GLProgram.h"

#include <glad/glad.h>

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
