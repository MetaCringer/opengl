cmake_minimum_required(VERSION 2.8)

project(ogl_program)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCES
    ${SRC_DIR}/main.c
)


add_executable(${PROJECT_NAME} ${SOURCES})

#lib sectons

#opengl
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIR} ${INCLUDE_DIR} )
target_link_libraries(${PROJECT_NAME} ${OPENGL_opengl_LIBRARY} ${OPENGL_glx_LIBRARY} )


#glfw
set(GLFW_DIR ${LIBS_DIR}/glfw)
add_subdirectory(${GLFW_DIR})

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_DIR}/include)
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)


#glad
set(GLAD_DIR ${LIBS_DIR}/glad)
add_library(glad ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PRIVATE ${GLAD_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLAD_DIR}/include)
target_link_libraries(${PROJECT_NAME} glad ${CMAKE_DL_LIBS})


