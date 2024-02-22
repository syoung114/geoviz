#pragma once

#include <glad/glad.h>
#include <fstream>
#include <string>
#include <type_traits>
#include  <string_view>

namespace geoviz {

    struct CmpTimeShader {
        std::string_view source;
        GLenum type;
    };

    constexpr CmpTimeShader basic_vertex_shader{R"GLSL(
        #version 460 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aColor;
        
        uniform mat4 model_view_projection;
        
        out vec3 vertex_color;
        
        void main() {
            gl_Position = model_view_projection * vec4(aPos, 1.0);
            vertex_color = aColor;
        }
    )GLSL", GL_VERTEX_SHADER};

    constexpr CmpTimeShader basic_fragment_shader{R"GLSL(
        #version 460 core
        in vec3 vertex_color;
        
        out vec4 FragColor;
        
        void main() {
            FragColor = vec4(vertex_color, 1.0f);
        }
    )GLSL", GL_FRAGMENT_SHADER};
}
