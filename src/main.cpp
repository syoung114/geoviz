#include <vector>

#include "GLFWwindowArgs.h"
#include "GLFWContextManager.cpp"
#include "ShaderFactory.cpp"
#include "GLProgram.cpp"
#include "Renderer.cpp"
#include "VertexBuffer.cpp"

int main(int argc, char* argv[]) {
    //Create the shaders
    std::vector<GLuint> shaders;
    shaders.push_back(
        ShaderFactory.read_and_create("./shaders/v.glsl", GL_VERTEX_SHADER)
    );
    shaders.push_back(
        ShaderFactory.read_and_create("./shaders/f.glsl", GL_FRAGMENT_SHADER)
    );
        
    //Buffer some vertices (placeholder vertices)
    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2, 0.0f
    };
    VertexBuffer vbuffer = new VertexBuffer(vertices);
    
    //Create the opengl program using the shaders. Notice this is independent of creating the vertices.
    GLProgram program = new GLProgram(shaders);

    //Give the program and vertex buffer to the renderer
    Renderer renderer = new Renderer(program, vbuffer);
    
    //Create the window (context) and render the vertices inside it.
    GLFWwindowArgs window_args = {800, 800, "test"};
    GLFWContextManager context = new GLFWContextManager(window_args, renderer);
    return context.run();

}
