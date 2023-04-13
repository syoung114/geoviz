#include "GLProgram.cpp"
#include "VertexBuffer.cpp"
#include "Color.h"

class Renderer {
    private:
        VertexBuffer *_buffer;
        GLProgram *_program;
        Color *_clear_color;

    public:
        Renderer(GLProgram program, VertexBuffer &vertex_buffer, Color &clear_color = {0.0f, 0.0f, 0.0f, 1.0f}) {
            this->_buffer = vertex_buffer;
            this->_program = program;
            glClearColor(this->_clear_color->red, this->_clear_color->green, this->_clear_color->blue, this->_clear_color->alpha);
        }

        void draw() {
            glClearColor(GL_COLOR_BUFFER_BIT);
            this->_program.use_program();
            this->_buffer.buffer_vertices();
            this->_buffer.draw();
        }
};
