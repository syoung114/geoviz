#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>

#include "GLProgram.h"
#include "VertexArrayBuffer.h"
#include "Vec4f.h"

class Renderer {
    private:
        VertexArrayBuffer *_vbuffer;
        GLProgram *_program;
        Vec4f *_clear_color;

        glm::mat4 _world;
        glm::mat4 _view;
        glm::mat4 _proj;

    public:
        Renderer(GLProgram &program, VertexArrayBuffer &vertex_buffer, Vec4f &clear_color);

        /**
         * Updates the transformation matrices and draws all the provided VertexArrayBuffers.
         */
        void draw(int screen_width, int screen_height);
};

#endif
