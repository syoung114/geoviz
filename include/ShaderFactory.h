#ifndef SHADER_FACTORY_H
#define SHADER_FACTORY_H

#include <glad/glad.h>
#include <string>

class ShaderFactory {
    public:
        /**
         * Returns the contents of a shader file
         */
        static std::string read_shader_file(const std::string &filename);
        
        /**
         * Returns a id to a compiled gl shader
         */
        static GLuint create(const std::string &shader_source, GLenum shader_type);

        /**
         * Reads a shader file and immediately compiles it, returning the id
         */
        static GLuint read_and_create(const std::string &filename, GLenum shader_type);
};

#endif
