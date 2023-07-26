#ifndef IMMUTABLE_ARRAY_H
#define IMMUTABLE_ARRAY_H

#include <cstddef>

template<typename T>
class ImmutableArray {
public:
    ImmutableArray() : _ptr(nullptr), _len(0) {}
    ImmutableArray(T* ptr, size_t len) : _ptr(ptr), _len(len) {}
    T* get_pointer() const { return _ptr; }
    size_t get_size() const { return _len; }

private:
    T* _ptr;
    size_t _len;
};

#endif
