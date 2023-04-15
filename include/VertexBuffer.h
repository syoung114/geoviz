#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <cstddef>

#include <glad/glad.h>

class VertexBuffer {
    private:
		float *_verts;
        size_t _size;
        int _num_verts;

		GLuint _varray;
		GLuint _vbuffer;

        void bind();

        void unbind();

	public:
        VertexBuffer(float *verts, std::size_t size);

        ~VertexBuffer();

        void set_vertices(float *verts, std::size_t size);

		void buffer_vertices();

        void draw(); 
};

#endif
