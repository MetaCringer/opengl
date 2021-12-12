cmake_minimum_required(VERSION 2.8)

project(ogl_program)

set(SOURCES
    src/main.c
    src/glad.c
)

add_executable(ogl-_program ${SOURCES})
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIR} include/ )
target_link_libraries(ogl_program ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )