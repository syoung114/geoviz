#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>

#include "GLProgram.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArrayObject.h"
#include "../util/Vec4f.h"

class Renderer {
    private:
        IndexBuffer* _vbuffer;
	VertexBuffer* _vb2;
	VertexArrayObject* _vao;
        //VertexIndexMediator *_vbuffer;
        GLProgram* _program;
        Vec4f* _clear_color;

        float _aspect;
        float _fov;

        glm::mat4 _world;
        glm::mat4 _view;
        glm::mat4 _projection;

        void _update_projection();
    public:
        
        //TODO should have a vector of vertexarraybuffers instead.
        Renderer(GLProgram &program, IndexBuffer &vi_mediator, VertexBuffer& vbuffer, VertexArrayObject& vao, Vec4f &clear_color);
        //Renderer(GLProgram &program, VertexIndexMediator &vi_mediator, Vec4f &clear_color);

        void mult_world_matrix(glm::mat4 other);

        void set_aspect_ratio(int& screen_width, int& screen_height);

        void set_fov(float radians);

        float get_fov();

        /**
         * Updates the transformation matrices and draws all the provided VertexArrayBuffers.
         */
        void draw(int& screen_width, int& screen_height);

};

#endif
