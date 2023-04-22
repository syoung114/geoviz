#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <cstddef>

#include <glad/glad.h>

#include "IBindable.h"

class IndexBuffer : public IBindable {
    private:
        GLuint *_indices;
        size_t _indices_size;
        short _num_indices;
        GLuint _ibuffer;

        void _bind() override;

        void _unbind() override;

	public:
        IndexBuffer();

        ~IndexBuffer();

        //IBindable* binding_call(IBindable &b) override;

        template<typename F>
        void binding_call(F fn) {
            _bind();
            fn();
            _unbind();        
        };
        //void binding_call(F fn) override;

        /*
         * Define what this object should render.
         */
        void update(GLuint *indices, size_t indices_size);

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
