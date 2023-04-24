#ifndef SHADER_FILE_H
#define SHADER_FILE_H

#include <string>

class ShaderFile {
    private:
        std::string _source;
        GLenum _type;
    public:
        ShaderFile(std::string source, GLenum type);
        std::string get_source() const;
        GLenum get_type() const;
};

#endif
