#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <glad/glad.h>
#include <vector>

#include "VertexArrayObject.h"
#include "Buffer.h"

class VertexBuffer : public Buffer<VertexBuffer, GLfloat> {
    public:
        VertexBuffer(const VertexArrayObject& vao, const int vertex_length) {
            glVertexArrayVertexBuffer(vao.get_id(), 0, this->_id, 0, vertex_length * sizeof(GLfloat));
        }

        void draw() {
            glDrawElements(GL_TRIANGLES, this->_data->size(), GL_FLOAT, 0);
        }
};

#endif
