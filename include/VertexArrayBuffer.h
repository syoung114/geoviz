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
        int _num_attributes;

		GLuint _varray;
		GLuint _vbuffer;
        GLuint _ibuffer;

        void _bind();

        void _unbind();

	public:
        VertexArrayBuffer();

        ~VertexArrayBuffer();

        /*
         * Define what this object should render.
         */
        void set_vertices(float *verts, std::size_t verts_size, int shape, int shape_unit, GLuint *indices, size_t indices_size);

        /**
         * Move the data to the GPU
         */
		void buffer();

        /**
         * Draws the contents of this object. Assumes a context, program, and a renderer has been created, and you've provided this object some vertices.
         */
        void draw(); 
};

#endif
