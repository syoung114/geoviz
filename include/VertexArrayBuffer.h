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
        int _shape;
        int _shape_unit;
        int _unit_count;

        const int FLOAT_SIZE = 32;

		GLuint _varray;
		GLuint _vbuffer;

        void _bind();

        void _unbind();

	public:
        VertexArrayBuffer(float *verts, std::size_t size, int num_verts, int shape, int shape_unit);

        ~VertexArrayBuffer();

        void set_vertices(float *verts, std::size_t size, int num_verts, int shape, int shape_unit);

		void buffer();

        void draw(); 
};

#endif
