#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <cstddef>
#include <vector>

#include <glad/glad.h>

#include "VertexArrayObject.h"

class IndexBuffer {
    private:
        GLuint _id;
        const std::vector<GLuint>* _indices;
	bool _needs_buffer;

    public:
        IndexBuffer(const VertexArrayObject& vao);
        ~IndexBuffer();

        void update(const std::vector<GLuint>& indices) {
            _indices = &indices;
	    _needs_buffer = true;
	}

        /**
         * Move the data to the GPU
         */
        bool buffer(const bool forceful=false);

        /**
         * Draws the contents of this object. Assumes a context, program, and a renderer has been created, and you've provided this object some vertices.
         */
        void draw(); 
};

#endif
