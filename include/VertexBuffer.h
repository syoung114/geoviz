#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <glad/glad.h>

class VertexBuffer {
    private:
		GLfloat *_verts;
        int _num_verts;

		GLuint _varray;
		GLuint _vbuffer;
	public:
        VertexBuffer(GLfloat *verts);

        ~VertexBuffer();

        void set_vertices(GLfloat *verts);

		void buffer_vertices();

        void draw(); 
};

#endif
