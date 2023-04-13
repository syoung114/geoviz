class VertexBuffer {
    private:
		GLfloat *_verts;
        int _num_verts;

		GLuint _varray;
		GLuint _vbuffer;
	public:
        VertexBuffer(GLfloat *verts) {
            this->set_vertices(verts);
        }
        ~VertexBuffer() {
            //varray and vbuffer could be null so check first before deleting
            if (this->_varray) {
                glDeleteVertexArrays(1, &this->_varray);
            }
            if (this->_vbuffer) {
                glDeleteBuffers(1, &this->_vbuffer);
            } 
        }

        void set_vertices(GLfloat *verts) { 
			this->_verts = verts;
            this->_num_verts = sizeof(this->_verts)/sizeof(GLfloat);
		}

        /*
        GLuint get_gl_vertex_array() {
            return this->_varray;
        }

        GLUint get_gl_vertex_buffer() {
            return this->_vbuffer;
        }
        */

		void buffer_vertices() {
            //TODO: probably not dynamic enough
            glGenVertexArrays(1, &this->_varray);
            glGenBuffers(1, &this->_vbuffer);

            glBindVertexArray(this->_varray)

            glBindBuffer(GL_ARRAY_BUFFER, this->_varray);
            glBufferData(GL_ARRAY_BUFFER, sizeof(this->_verts), this->_verts, GL_STATIC_DRAW);

            glVertexAttribPointer(0, this->_num_verts, GL_FLOAT, GL_FALSE, this->_num_verts*sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        /**
        * Do not use directly
        */
        void draw() {
            glDrawArrays(GL_TRIANGLES, 0, this->_num_verts);
        }
};
