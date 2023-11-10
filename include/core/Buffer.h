#ifndef BUFFER_H
#define BUFFER_H

#include <cstddef>
#include <vector>
#include <glad/glad.h>

template<typename T>
class Buffer {
    protected:
        GLuint _id;
        const std::vector<T>* _data;
        bool _needs_buffer;
    public:
        Buffer() { //I don't provide the vao here because uncertain whether all possible subclasses will require one
            glCreateBuffers(1, &_id);
            _needs_buffer = false;
	}
	virtual ~Buffer() {
            glDeleteBuffers(1, &_id);
	}

        void update(const std::vector<T>& data) {
            _data = &data;
            _needs_buffer = true;
	}
	
	bool buffer(const bool forceful = false) {
            if (_needs_buffer || forceful) {
                size_t data_size_bytes = _data->size() * sizeof(T);
                glNamedBufferData(_id, data_size_bytes, 0, GL_STATIC_DRAW);
                glNamedBufferSubData(_id, 0, data_size_bytes, _data->data());
        
        	_needs_buffer = false;
        	return true;
            }
            return false;
	}

        virtual void draw() = 0;
};

#endif
