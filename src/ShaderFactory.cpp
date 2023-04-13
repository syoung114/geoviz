#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>

class ShaderFactory {
    public:
        static std::string read_shader_file(const std::string filename) {
           std::ifstream file(filename);
            if (!file.good()) {
                std::cout<<"File \""<<filename<<"\" failed to load.";
                exit(1);
            }
            return std::string(
                std::istreambuf_iterator<char>(file),
                std::istreambuf_iterator<char>()
            );
        }

        static GLuint create(std::string shader_source, GLenum shader_type) {
            GLuint shader = glCreateShader(shader_type);
            glShaderSource(shader, 1, shader_source, NULL);
            glCompileShader(shader);
            return shader;
        }

        static GLuint read_and_create(const std::string filename, GLenum shader_type) {
            std::string shader_source = ShaderFactory.read_shader_file(filename);
            GLuint shader = ShaderFactory.create(shader_source, GLenum);
            return shader;
        }
};
