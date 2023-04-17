cmake_minimum_required(VERSION 3.20)
project(geoviz)
#set_property(TARGET ${PROJECT_NAME}_cxx17 CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

include_directories(include)

add_subdirectory(lib/glad)
add_subdirectory(lib/glm)

set(GLFW_BUILD_DOCS_OFF CACHE BOOL "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")

add_subdirectory(lib/glfw)

#if (MSVC)
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS /ENTRY:mainCRTStartup")
#endif()

set(SRC_FILES src/main.cpp src/GLFWContextManager.cpp src/GLProgram.cpp src/VertexArrayBuffer.cpp src/Renderer.cpp src/ShaderFactory.cpp src/VertexBuilder.cpp)
#add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})
add_executable(${PROJECT_NAME} ${SRC_FILES})
#add_library(glad glad.c glad.h)

#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw)
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/glm)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw glad glm)

#if (MSVC)
#    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
#endif()
