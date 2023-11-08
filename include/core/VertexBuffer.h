#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <cstddef>
#include <functional>

#include <glad/glad.h>

#include "IBindable.h"
#include "VertexArrayObject.h"
#include "../util/ImmutableArray.h"

class VertexBuffer {
    private:
        ImmutableArray<float> _verts;
        GLuint _id;
	//VertexArrayObject* _vao;

    public:
        VertexBuffer(VertexArrayObject& vao);

        ~VertexBuffer();

        void buffer();

	void update(ImmutableArray<float> verts);
};

#endif
