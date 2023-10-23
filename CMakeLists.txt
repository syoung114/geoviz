cmake_minimum_required(VERSION 3.20)
project(geoviz)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

include_directories(include)

add_subdirectory(lib/glad)
add_subdirectory(lib/glm)
add_subdirectory(lib/SDL)
add_subdirectory(lib/CLI11)

set(
    SRC_FILES
    src/main.cpp
    src/vox-spiral.cpp
    src/core/Geoviz.cpp
    src/core/SDLContext.cpp
    src/core/SDLContextLogic.cpp
    src/core/GLProgram.cpp
    src/core/VertexArrayBuffer.cpp
    src/core/Renderer.cpp
    src/core/ShaderFactory.cpp
    src/core/IndexBuffer.cpp
    src/core/VertexIndexMediator.cpp
    src/core/ShaderFile.cpp
    src/primitives/PrimitiveBuilder.cpp
    src/core/Geomodel.cpp
)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} SDL3::SDL3 glad glm CLI11::CLI11)
