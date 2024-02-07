#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <vector>

#include <glad/glad.h>

#include "VertexArrayObject.h"
#include "Buffer.h"

class IndexBuffer : public Buffer<GLuint> {
    public:
        IndexBuffer(const VertexArrayObject& vao) {
            glVertexArrayElementBuffer(vao.get_id(), this->_id);
        }

        /**
         * Draws the contents of this object. Assumes a context, program, and a renderer has been created, and you've provided this object some vertices.
         */
        void draw() override {
            glDrawElements(GL_TRIANGLES, this->_data->size(), GL_UNSIGNED_INT, 0);
        }
};

#endif
