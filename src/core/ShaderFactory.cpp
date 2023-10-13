#include "core/ShaderFactory.h"

#include <glad/glad.h>
#include <fstream>
#include <string>

GLenum ShaderFactory::get_shader_type(std::string str) {
    if (str == "GL_VERTEX_SHADER") {
        return GL_VERTEX_SHADER;
    }
    else if (str == "GL_FRAGMENT_SHADER") {
        return GL_FRAGMENT_SHADER;
    }
    else if (str == "GL_GEOMETRY_SHADER") {
        return GL_GEOMETRY_SHADER;
    }
    else if (str == "GL_COMPUTE_SHADER") {
        return GL_COMPUTE_SHADER;
    }
    //TODO Implement other shader types as needed
    else {
        throw std::runtime_error("Invalid shader type");
    }
}

ShaderFile ShaderFactory::read_shader_file(const std::string &filename) {
    std::string source;
    std::ifstream file(filename.c_str());
    if (!file.good()) {
        throw std::runtime_error("Failed to read file " + filename + "; file.good() returned false");
    }
    std::string line;
    bool first_line = true;
    GLenum type;
    while (std::getline(file, line)) {
        if (first_line) {
            type = get_shader_type(line);
            first_line = false;
        }
        else {
            source += line + '\n';
        }
    }
    file.close();
    source += '\0';
    ShaderFile sf(source, type);
    return sf;
}
