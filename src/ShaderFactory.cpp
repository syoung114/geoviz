#include "ShaderFactory.h"

#include <glad/glad.h>
#include <fstream>
#include <string>

std::string ShaderFactory::read_shader_file(const std::string &filename) {
    std::string source;
    std::ifstream file(filename.c_str());
    if (!file.good()) {
        throw std::runtime_error("Failed to read file " + filename + "; file.good() returned false");
    }
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
             source += line + '\n';
        }
    }
    file.close();
    source += '\0';
    return source;
}

GLuint ShaderFactory::create(const std::string &shader_source, GLenum shader_type) {
    GLuint shader = glCreateShader(shader_type);
    const char* shader_source_ptr = shader_source.c_str();
    glShaderSource(shader, 1, &shader_source_ptr, NULL);
    glCompileShader(shader);
    return shader;
}

GLuint ShaderFactory::read_and_create(const std::string &filename, GLenum shader_type) {
    const std::string shader_source = ShaderFactory::read_shader_file(filename);
    GLuint shader = ShaderFactory::create(shader_source, shader_type);
    return shader;
}
