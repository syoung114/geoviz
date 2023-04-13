#include <glad/glad.h>

#include <string>
#include <vector>

class GLProgram {
    private:
        GLuint _program;
    public:
        /**
        * Creates a openGL program
        * @shaders The final shaders to be used in the program.
        */
        GLProgram(std::vector<GLuint> &shaders) {
            this->_program = glCreateProgram();
            
            //Loop through the shaders and attach them to the program
            for (const auto &shader : shaders) {
                glAttachShader(this->_program, shader);
            }

            glLinkProgram(this->_program);
        }
        ~GLProgram() {
            glDeleteProgram(this->_program);
        }

        GLuint get_program() {
            //Bit of a strange thing to do this because it breaks encapsulation, but it's not like I can pass this class into gl functions. Only other way is to create wrapper functions that substitute when a public reference is needed.
            return this->_program;
        }
};
