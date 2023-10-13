#ifndef VERTEX_INDEX_MEDIATOR_H
#define VERTEX_INDEX_MEDIATOR_H

#include "IBindable.h"
#include "VertexArrayBuffer.h"
#include "IndexBuffer.h"

class VertexIndexMediator {
    private:
        //IBindable *_vertex_array_buffer;
        //IBindable *_index_buffer;
        VertexArrayBuffer *_vertex_array_buffer;
        IndexBuffer *_index_buffer;

        void _draw();
    public:
        VertexIndexMediator(VertexArrayBuffer &vab, IndexBuffer &ib);

        void buffer();

        void draw();
};

#endif
