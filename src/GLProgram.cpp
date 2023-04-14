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
    //Not sure how I feel about not returning anything here. The only way to return the program is by its GLuint representation, which some other code can use to modify the program, breaking encapsulation. But by not returning anything, there is no message back to the calling code, and I lose track of state if I wanted multiple programs concurrently and wanted to control when to use what program. Adding external logic to manage it defeats the purpose of encapsulating this class. Something to think about. OOP is not a perfect paradigm.
    glUseProgram(this->_program);
}
