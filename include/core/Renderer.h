#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>

#include "GLProgram.h"
#include "VertexIndexMediator.h"
#include "../util/Vec4f.h"

class Renderer {
    private:
        VertexIndexMediator *_vbuffer;
        GLProgram *_program;
        Vec4f *_clear_color;

        glm::mat4 _world;
        glm::mat4 _view;
        glm::mat4 _projection;

    public:
        Renderer(GLProgram &program, VertexIndexMediator &vi_mediator, Vec4f &clear_color);

        void mult_world_matrix(glm::mat4 other);

        /**
         * Updates the transformation matrices and draws all the provided VertexArrayBuffers.
         */
        void draw(int screen_width, int screen_height);

};

#endif
