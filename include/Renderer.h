#ifndef RENDERER_H
#define RENDERER_H

#include "GLProgram.h"
#include "VertexBuffer.h"
#include "Color.h"

class Renderer {
    private:
        VertexBuffer *_buffer;
        GLProgram *_program;
        Color *_clear_color;

    public:
        Renderer(GLProgram &program, VertexBuffer &vertex_buffer, Color clear_color = {0.0f, 0.0f, 0.0f, 1.0f});

        void draw();
};

#endif
