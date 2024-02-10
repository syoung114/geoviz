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
    main.cpp
)
#src/core/Buffer.cpp

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG_WITH_GDB)
endif()

#src/core/VertexIndexMediator.cpp
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} SDL3::SDL3 glad glm CLI11::CLI11)
