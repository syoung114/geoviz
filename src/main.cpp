#include <vector>
#include <cmath>

#include "GLFWwindowArgs.h"
#include "GLFWContextManager.h"
#include "ShaderFactory.h"
#include "GLProgram.h"
#include "Renderer.h"
#include "VertexBuffer.h"

int main(int argc, char* argv[]) {
    //Create the shaders
    std::vector<GLuint> shaders;
    std::string wd = "/home/steven/desktop/geoviz/src";
    shaders.push_back(
        ShaderFactory::read_and_create(wd + "/shaders/v.glsl", GL_VERTEX_SHADER)
    );
    shaders.push_back(
        ShaderFactory::read_and_create(wd + "./shaders/f.glsl", GL_FRAGMENT_SHADER)
    );
        
    //Buffer some vertices (placeholder vertices)
    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2, 0.0f
    };
    VertexBuffer *vbuffer = new VertexBuffer(vertices);
    
    //Create the opengl program using the shaders. Notice this is independent of creating the vertices.
    GLProgram *program = new GLProgram(shaders);

    //Give the program and vertex buffer to the renderer
    Renderer *renderer = new Renderer(*program, *vbuffer);
    
    //Create the window (context) and render the vertices inside it.
    GLFWwindowArgs window_args = {800, 800, "test"};
    GLFWContextManager *context = new GLFWContextManager(window_args, *renderer);
    context->run();

    //We created pointers to object instances. In this case we must manually clean them up. Out of good practice the order matters: LIFO
    delete context;
    delete renderer;
    delete program;
    delete vbuffer;

    return 0;

}
