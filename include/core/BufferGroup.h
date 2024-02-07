#ifndef BUFFER_GROUP_H
#define BUFFER_GROUP_H

#include "containers/partial_map.h"

//TODO need to modify STL unordered_map to decouple values and keys
template <typename K>
class BufferGroup {
    private:
        VertexArrayObject _vao;
        std::partial_map<K, Buffer> _buffers;
    	std::unordered_set<const Buffer*> _drawables;

	    int _vertex_length;

    public:
	    BufferGroup(const std::vector<int>& attribute_layout) {//: _buffers({}), _drawing_ptrs({}) {
            _vao = VertexArrayObject(attribute_layout);
	        _vertex_length = std::accumulate(attribute_layout.begin(), attribute_layout.end(), 0);
	    }

	    template<typename B>
	    std::enable_if_t<std::is_base_of<VertexBuffer, B>::value, void> create_buffer(K& key_ref, bool is_drawable) {
            _buffers.emplace(&key_ref, _vao, _vertex_length);
	        if (is_drawable) {
                _drawables.insert(&(_buffers[&key_ref]));
	        }
	    }

	    template<typename B>
	    std::enable_if_t<std::is_base_of<Buffer, B>::value, void> create_buffer(K& key_ref, bool is_drawable) {
            _buffers.emplace(&key_ref, _vao);
	        if (is_drawable) {
                _drawables.insert(&(_buffers[&key_ref]));
	        }
	    }

	    bool set_drawable(const K& key_ref, const bool is_drawable) {
            //check if we are referncing something that exists
            auto it = _buffers.find(&key_ref);
	        if (it != _buffers.end()) {

                //now do the change.
	            if (is_drawable) {
                    _drawables.insert(&key_ref);
	            }
	            else {
                    _drawables.erase(&key_ref);
	            }
	    	    return true;
	        }
	        return false;
	    }

	    void bind() {
            _vao.bind();
	    }

	    void draw() {
            for (const Buffer* buffer : _drawables) {
                buffer->draw();
	        }
	    }
};

#endif
