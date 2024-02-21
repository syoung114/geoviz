#pragma once

#include <algorithm>
#include <memory>

#include "types.hpp"

namespace geoviz {
    template<typename T>
    struct BoundArray {
        std::unique_ptr<T[]> ptr;
        size_type size;

        T& operator[](size_type n) {
            return (ptr.get())[n];
        }
    };

    template<typename T>
    BoundArray<T> make_bound(const T* data, size_type length) {
        BoundArray<T> temp;
        //temp.ptr = std::make_unique<T>(ptr);
        temp.ptr = std::make_unique<T[]>(length);
        std::copy_n(data, length, temp.ptr.get());
        //temp.ptr.reset(data);
        temp.size = length;
        return temp;
    }
}
