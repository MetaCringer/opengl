#define GLFW_INCLUDE_NONE
#include<stdio.h>
#include<GLFW/glfw3.h>

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

    window_resize_callback(window, width, height)





    /* Bindings callbacks */
    
    glfwSetErrorCallback(error_callback);

    glfwSetKeyCallback(window, key_callback);

    glfwSetFramebufferSizeCallback(window_resize_callback);

    

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