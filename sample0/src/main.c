#define GLFW_INCLUDE_NONE
#include<stdio.h>
#include<GLFW/glfw3.h>
#include <glad/glad.h>
#include<GL/gl.h>

int width=640, height=480;
double time;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    
}

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void window_resize_callback(GLFWwindow* window, int width, int height){
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}


float vertices[] = {
    0.0f,  0.5f, // Vertex 1 (X, Y)
    0.5f, -0.5f, // Vertex 2 (X, Y)
    -0.5f, -0.5f  // Vertex 3 (X, Y)
};

static const char* vertex_shader_text=
"#version 150 core\n"
"in vec2 position;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(position, 0.0, 1.0);\n"
"}";


int main(){
    GLFWwindow* window;
    

    
    /* Initialize the library */
    if (!glfwInit())
        return -1;



    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(!gladLoadGL())
        return -1;

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("Failed to initialize OpenGL context\n");
        return -1;
    }





    //window_resize_callback(window, width, height);





    /* Bindings callbacks */
    
    glfwSetErrorCallback(error_callback);

    glfwSetKeyCallback(window, key_callback);

    glfwSetFramebufferSizeCallback(window, window_resize_callback);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        time = glfwGetTime();
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}