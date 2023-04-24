#include <glad/glad.h>
#include <string>

#include <ShaderFile.h>

ShaderFile::ShaderFile(std::string source, GLenum type) {
    _source = source;
    _type = type;
}

std::string ShaderFile::get_source() const {
    return _source;
}

GLenum ShaderFile::get_type() const {
    return _type;
}
