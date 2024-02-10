#pragma once

#include "types.hpp"

namespace geoviz {
    
    template<typename Derived>
    class System {
        public:
            void update(float_t dt) {
                static_cast<Derived*>(this)->update(dt);
            }
    };
}
