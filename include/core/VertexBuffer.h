#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <glad/glad.h>
#include <vector>

#include "VertexArrayObject.h"

class VertexBuffer {
    private:
        GLuint _id;
        const std::vector<GLfloat>* _verts;
	bool _needs_buffer; //see implementation of buffer for further explaination
	//VertexArrayObject* _vao;

    public:
        VertexBuffer(const VertexArrayObject& vao, const int vertex_length);
        ~VertexBuffer();

	void update(const std::vector<GLfloat>& vertices) {
            _verts = &vertices;
	    _needs_buffer = true;
	}

        bool buffer(const bool forceful=false);
};
#endif
