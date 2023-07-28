#include "VertexIndexMediator.h"
#include "VertexArrayBuffer.h"
#include "IndexBuffer.h"

VertexIndexMediator::VertexIndexMediator(VertexArrayBuffer &vab, IndexBuffer &ib) {
    _vertex_array_buffer = &vab;
    _index_buffer = &ib;
}

void VertexIndexMediator::buffer() {
    _vertex_array_buffer->buffer();
    _index_buffer->buffer();
}

void VertexIndexMediator::_draw() {
    //glDrawElements(GL_TRIANGLES, _index_buffer.get_num_elements(), GL_UNSIGNED_INT, 0);
    _index_buffer->draw();
}

void VertexIndexMediator::draw() {
    //Here I use a combination of lambda functions and the call stack to bind the vertex and index buffer before drawing and unbind them in the order they were bound.
    _vertex_array_buffer->binding_call([&]() {
        _index_buffer->binding_call([&]() {
            this->_draw();
        });
    });
}
