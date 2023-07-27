cmake_minimum_required(VERSION 3.5)
project(geoviz)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

include_directories(include)

add_subdirectory(lib/glad)
add_subdirectory(lib/glm)
add_subdirectory(lib/SDL)

set(
    SRC_FILES
    src/main.cpp
    src/SDLContextManager.cpp
    src/GLProgram.cpp
    src/VertexArrayBuffer.cpp
    src/Renderer.cpp
    src/ShaderFactory.cpp
    src/VertexBuilder.cpp
    src/IndexBuffer.cpp
    src/VertexIndexMediator.cpp
    src/ShaderFile.cpp
    src/GeomodelPool.cpp
)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} SDL3::SDL3 glad glm)