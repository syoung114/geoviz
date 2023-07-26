#ifndef VERTEX_ARRAY_BUFFER_H
#define VERTEX_ARRAY_BUFFER_H

#include <cstddef>
#include <functional>

#include <glad/glad.h>

#include "IBindable.h"
#include "ImmutableArray.h"

class VertexArrayBuffer : public IBindable {
    private:
        ImmutableArray<float> _verts;
  
        int _vertex_length;
        int _attribute_length;
        int _num_attributes;

		GLuint _varray;
		GLuint _vbuffer;

        void _bind() override;

        void _unbind() override;

	public:
        VertexArrayBuffer();

        ~VertexArrayBuffer();

        template<typename F>
        void binding_call(F fn) {
            _bind();
            fn();
            _unbind();
        }
        //void binding_call(F fn) override;

        /*
         * Define what this object should render.
         */
        void update(ImmutableArray<float> verts, int vertex_length, int num_attributes);

        /**
         * Move the data to the GPU
         */
		void buffer();
/*
        **
         * Draws the contents of this object. Assumes a context, program, and a renderer has been created, and you've provided this object some vertices.
         *
        void draw(); 
*/
};

#endif
