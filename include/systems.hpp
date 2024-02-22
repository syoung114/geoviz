#pragma once

#include <glad/glad.h>
#include <memory>
#include <type_traits>
#include <any>

#include "BoundArray.hpp"
#include "types.hpp"
#include "world.hpp"
#include "components.hpp"

namespace geoviz {
    
    //template<typename Derived>
    //struct System {
    //    using t = Derived;
    //    //constexpr System() = default;

    //    //constexpr ~System() = default;

    //    //template<typename world_t>
    //    //void runtime_init(const world_t& world) {
    //    //    static_cast<Derived*>(this)->runtime_init(world);
    //    //}

    //    //void update(float_t dt) {
    //    //    static_cast<Derived*>(this)->update(dt);
    //    //}
    //};

    class Renderer {
        //public:
        //    Renderer() = default;

        //    void runtime_init() {
        //        // TODO consider different semantics about casting to pointer/reference/value
        //        BoundArray<Entity> render_ents = world_ptr_wrapper<world_types>::ptr->get_entities_by<Render>();

        //        for (size_type i = 0; i < render_ents.size; ++i) {

        //            Render& current_component = world_ptr_wrapper<world_types>::ptr->get_component<render_ents[i], Render>();
        //            GLuint& vao = current_component.vao;

        //            glCreateVertexArrays(1, &vao);

        //            glEnableVertexArrayAttrib(vao, 0);
        //            glVertexArrayAttribBinding(vao, 0, 0);
        //            glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float_t));

        //            glEnableVertexArrayAttrib(vao, 1);
        //            glVertexArrayAttribBinding(vao, 1, 0);
        //            glVertexArrayAttribFormat(vao, 1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float_t));

        //            // buffers
        //            glCreateBuffers(1, &(render_ents[i].vbo));
        //            glCreateBuffers(1, &(render_ents[i].ebo));
        //        }
        //    }

        //    ~Renderer() {
        //        BoundArray<Entity> render_ents = world_ptr_wrapper<world_types>::ptr->get_entities_by<Render>();
        //        for (size_type i = 0; i < render_ents.size; ++i) {
        //            Render& current_component = world_ptr_wrapper<world_types>::ptr->get_component<render_ents[i], Render>();
        //            glDeleteVertexArrays(1, &(current_component.vao));
        //            glDeleteBuffers(1, &(current_component.vbo));
        //            glDeleteBuffers(1, &(current_component.ebo));
        //        }
        //    }

        //    void update(float_t dt) {
        //        // "le functional" call of glClearColor
        //        std::apply(glClearColor, *(world.get_component<Entity::RENDER_PROPERTIES, ClearColor>()));
        //        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //        BoundArray<Entity> render_ents = world.get_entities_by<Render>();
        //        for (size_type i = 0; i < render_ents.size; ++i) {
        //            //
        //        }
        //    }

        //private:

        ////constexpr Render() {
        ////    //vao
        ////}

        //    void dothing(Entity& e) {
        //        #define M_BUFFER(id,type,data) \
        //            size_type bytes = data.size() * sizeof(type); \
        //            glNamedBufferData(id, bytes, 0, GL_STATIC_DRAW); \
        //            glNamedBufferSubData(id, 0, bytes, data); \

        //        Render r = world.get_component<std::decay_t<decltype(e)>, Render>();
        //        Mesh m = world.get_component<std::decay_t<decltype(e)>, Mesh>();

        //        glBindVertexArray(r.vao);
        //        M_BUFFER(r.vbo, float_t, m.vertices.data())
        //        M_BUFFER(r.ebo, uint_t, m.indices.data())
        //    }
    };

    //template<typename T>
    //concept IsSystem = IsCRTP<System<T>, T>;
    //concept IsSystem = std::is_same<System<T>, T>::value;
    //template<typename T>
    //concept IsSystem = true;

}
