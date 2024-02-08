#ifndef SHADER_FACTORY_H
#define SHADER_FACTORY_H

#include <glad/glad.h>
#include <string>

#include "ShaderFile.h"

class ShaderFactory {
    public:
        /**
         * Retuns the GL enum representation of a given shader
         */
        static GLenum get_shader_type(std::string str);

        /**
         * Returns the contents of a shader file
         */
        static ShaderFile read_shader_file(const std::string &filename);
//        static ShaderFile read_shader_file(std::string&& filename);
};

#endif
