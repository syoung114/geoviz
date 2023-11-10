#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <glad/glad.h>
#include <vector>

#include "VertexArrayObject.h"
#include "Buffer.h"

class VertexBuffer : public Buffer<GLfloat> {
    public:
        VertexBuffer(const VertexArrayObject& vao, const int vertex_length) {
            glVertexArrayVertexBuffer(vao.get_id(), 0, _id, 0, vertex_length * sizeof(GLfloat));
        }

        void draw() override {
            glDrawElements(GL_TRIANGLES, _data->size(), GL_FLOAT, 0);
        }
};

#endif
