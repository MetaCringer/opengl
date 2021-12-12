#include<stdio.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<GL/gl.h>

int width=640, height=480;
double time;
GLFWwindow* window;

void init(void)
{
    // select clearing (background) color 
      
    glClearColor(0.0, 0.0, 0.0, 0.0);
    printf("glClearColor(0.0, 0.0, 0.0, 0.0);\n");
    // initialize viewing values
    glMatrixMode(GL_PROJECTION);
    printf("glMatrixMode(GL_PROJECTION);\n");
    glLoadIdentity();
    printf("glLoadIdentity();\n");
    glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
    printf("glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);\n");
}

double dx(int x){
    return (x + (width/2)) / width;
}

double dy(int y){
    return (y + (height/2)) / height;
}

void display(){
      // clear all pixels
    glClear(GL_COLOR_BUFFER_BIT);

    //  draw white polygon with corners at (0.25,0.25,0.0) and (0.75,0.75,0.0)    
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.25,0.25,0.0);
        glVertex3f(0.75,0.25,0.0);
        glVertex3f(0.75,0.75,0.0);
        glVertex3f(0.25,0.75,0.0);
    glEnd();
    glBegin(GL_POINT);
        glVertex3f(0.25,0.25,0.0);
        glVertex3f(0.75,0.25,0.0);
        glVertex3f(0.75,0.75,0.0);
        glVertex3f(0.25,0.75,0.0);
    glEnd();
    // don't wait, start processing buffered OpenGL routines
    glFlush();
}

int main(int argc, char** argv){
    printf("GLFW init ...'\n");
    if (!glfwInit()){
        return -1;
    }
    printf("GLFW init done\n");
    

    printf("Creating window ...\n");
    window = glfwCreateWindow(640, 480, "Окно", NULL, NULL);
    if (!window)
    {
        printf("window wasnt created\n");
        glfwTerminate();
        return -1;
    }
    printf("window was created\n");
    printf("Bind GL context to window ...");
    glfwMakeContextCurrent(window);
    printf("Successfull\n");
    printf("GLAD init ...'\n");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }
    printf("GLAD init done\n");
    printf("Init ...\n");
    init();
    printf("Init done\n");
    while (!glfwWindowShouldClose(window))
    {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}