#ifndef BINDING_H
#define BINDING_H

#include <functional>

class IBindable {
    private:
        virtual void _bind() = 0;
        virtual void _unbind() = 0;
    //public:
        //template<typename F>
        //virtual void binding_call(F fn);
};

#endif
