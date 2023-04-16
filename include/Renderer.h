#ifndef RENDERER_H
#define RENDERER_H

#include "GLProgram.h"
#include "VertexArrayBuffer.h"
#include "Vec4f.h"

class Renderer {
    private:
        VertexArrayBuffer *_vbuffer;
        GLProgram *_program;
        Vec4f *_clear_color;

    public:
        Renderer(GLProgram &program, VertexArrayBuffer &vertex_buffer, Vec4f &clear_color);

        void draw();
};

#endif
