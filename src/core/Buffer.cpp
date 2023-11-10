#include <glad/glad.h>
#include <vector>
#include <cstddef>
#include "core/Buffer.h"

template <typename T>
Buffer<T>::Buffer() {
    glCreateBuffers(1, &_id);
    _needs_buffer = false;
}

template <typename T>
Buffer<T>::~Buffer() {
    glDeleteBuffers(1, &_id);
}

template <typename T>
void Buffer<T>::update(const std::vector<T>& data) {
    _data = &data;
    _needs_buffer = true;
}

template <typename T>
bool Buffer<T>::buffer(bool forceful) {
    if (_needs_buffer || forceful) {
        size_t data_size_bytes = _data->size() * sizeof(T);
        glNamedBufferData(_id, data_size_bytes, 0, GL_STATIC_DRAW);
        glNamedBufferSubData(_id, 0, data_size_bytes, _data->data());

	_needs_buffer = false;
	return true;
    }
    return false;
}
