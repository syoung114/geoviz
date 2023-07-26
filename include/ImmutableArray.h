#ifndef IMMUTABLE_ARRAY_H
#define IMMUTABLE_ARRAY_H

#include <cstddef>

template<typename T>
class ImmutableArray {
public:
    ImmutableArray(T* ptr, size_t len) : _ptr(ptr), _len(len) {}
    const T* get_pointer() const { return _ptr; }
    size_t get_length() const { return _len; }

private:
    T* _ptr;
    size_t _len;
};

#endif
