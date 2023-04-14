#ifndef SHADER_FACTORY_H
#define SHADER_FACTORY_H

#include <glad/glad.h>
#include <string>

class ShaderFactory {
    public:
        static std::string read_shader_file(const std::string &filename);
        
        static GLuint create(const std::string &shader_source, GLenum shader_type);

        static GLuint read_and_create(const std::string &filename, GLenum shader_type);
};

#endif
