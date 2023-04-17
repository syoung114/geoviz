#ifndef VERTEX_ARRAY_BUFFER_H
#define VERTEX_ARRAY_BUFFER_H

#include <cstddef>

#include <glad/glad.h>

class VertexArrayBuffer {
    private:
        GLfloat *_verts;
        size_t _verts_size;

        GLuint *_indices;
        size_t _indices_size;
        short _num_indices;
  
        int _shape;
        int _shape_unit;
        int _unit_count;

		GLuint _varray;
		GLuint _vbuffer;
        GLuint _ibuffer;

        void _bind();

        void _unbind();

	public:
        VertexArrayBuffer(float *verts, std::size_t verts_size, int shape, int shape_unit, GLuint *indices, size_t indices_size, short num_indices);

        ~VertexArrayBuffer();

        void set_vertices(float *verts, std::size_t verts_size, int shape, int shape_unit, GLuint *indices, size_t indices_size, short num_indices);

		void buffer();

        void draw(); 
};

#endif
