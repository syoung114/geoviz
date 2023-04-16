#ifndef VERTEX_ARRAY_BUFFER_H
#define VERTEX_ARRAY_BUFFER_H

#include <cstddef>

#include <glad/glad.h>

class VertexArrayBuffer {
    private:
		int _id;
        
        float *_verts;
        size_t _size;
        int _num_verts;

		GLuint _varray;
		GLuint _vbuffer;

        void bind();

        void unbind();

	public:
        VertexArrayBuffer(float *verts, std::size_t size, int num_verts);

        ~VertexArrayBuffer();

        void set_vertices(float *verts, std::size_t size, int num_verts);

		void buffer();

        void draw(); 
};

#endif
