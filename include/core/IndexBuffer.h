#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <cstddef>

#include <glad/glad.h>

#include "IBindable.h"
#include "../util/ImmutableArray.h"

class IndexBuffer : public IBindable {
    private:
        ImmutableArray<GLuint> _indices;
        size_t _indices_size;
        short _num_indices;
        GLuint _ibuffer;

        void _bind() override;

        void _unbind() override;

	public:
        IndexBuffer();

        ~IndexBuffer();

        template<typename F>
        void binding_call(F fn) {
            _bind();
            fn();
            _unbind();        
        };

        /*
         * Define what this object should render.
         */
        void update(ImmutableArray<GLuint> indices);

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
