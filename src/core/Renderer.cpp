#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/Renderer.h"
#include "core/GLProgram.h"
#include "util/Vec4f.h"
#include "core/VertexArrayObject.h"

//Renderer::Renderer(GLProgram &program, VertexIndexMediator &vi_mediator, Vec4f &clear_color) {
Renderer::Renderer(GLProgram &program, IndexBuffer &vi_mediator, VertexBuffer& vbuffer, VertexArrayObject& vao, Vec4f &clear_color) {
    _vbuffer = &vi_mediator;
    _vb2 = &vbuffer;
    _program = &program;
    _vao = &vao;
    _clear_color = &clear_color;
    
    //Set the rendering matrices
    _world = glm::mat4(1.0);

    _view = glm::mat4(1.0);
    _view = glm::translate(_view, glm::vec3(0.0, 0.0, -95.0));
   
    //create the perspective matrix assuming default values.
    _aspect = 1.0f;
    this->set_fov(45);
    _projection = glm::mat4(1.0);
    _update_projection();

    //Remove fragments 'behind' other fragments
    glEnable(GL_DEPTH_TEST);
}


void Renderer::_update_projection() {
    _projection = glm::perspective(_fov, _aspect, 0.1f, 1000.0f);
}


void Renderer::set_aspect_ratio(int& screen_width, int& screen_height) {
    _aspect = screen_width / screen_height;
    _update_projection();
}


void Renderer::set_fov(float radians) {
    _fov = radians;
    _update_projection();
}


float Renderer::get_fov() {
    return _fov;
}


void Renderer::draw(const int screen_width, const int screen_height) {
    glClearColor(_clear_color->x, _clear_color->y, _clear_color->z, _clear_color->w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _vb2->buffer();
    _vbuffer->buffer();
    _program->use_program();
    _vao->bind();

   // _world *= glm::rotate(glm::mat4(1.0), glm::radians(0.5f), glm::vec3(1.0f, 0.0f, 1.0f));

    glm::mat4 mvp = _projection * _view * _world;
    
    //Give the transformation matrices to the shaders
    _program->set_uniform_mat4fv("model_view_projection", mvp);

    _vbuffer->draw();
}

void Renderer::mult_world_matrix(glm::mat4 other) {
    _world *= other;
}
