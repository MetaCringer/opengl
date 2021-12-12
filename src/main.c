#include<stdio.h>
#include<stdlib.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<GL/gl.h>

int width=640, height=480;
const int webHeight=5,webWidth=webHeight*2 ;
double time;
GLFWwindow* window;
double windowRatio;
int * VertexBuffer;
int sizeVertexBuffer;
double x1, x2, y1, y2;



double dx(int x){
    printf("%lf\n",(((double)x+1)/webWidth));
    return (x+1)/webWidth;
}

double dy(int y){
    printf("%lf\n",(((double)y+1)/webHeight));
    return (y+1)/webHeight;
}
void pushVertex(int x, int y){
    
    glVertex3f(dx(x),dy(y),0.0);
}

void display(){
      // clear all pixels
    glClear(GL_COLOR_BUFFER_BIT);

    //  draw white polygon with corners at (0.25,0.25,0.0) and (0.75,0.75,0.0)    
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < sizeVertexBuffer; i++)
    {
        pushVertex(VertexBuffer[i*2],VertexBuffer[i*2+1]);
    }
    glEnd();
    
    glBegin(GL_POINT);
    for (int i = 0; i < sizeVertexBuffer; i++)
    {
        pushVertex(VertexBuffer[i*2]+webHeight,VertexBuffer[i*2+1]);
    }
    glEnd();

    // don't wait, start processing buffered OpenGL routines
    glFlush();
}

void loadConfig(char * filename){
    FILE *config = fopen(filename, "r");
    fscanf(config, "x1=%lf\nx2=%lf\ny1=%lf\ny2=%lf\n", &x1, &x2, &y1, &y2);
    fscanf(config, "size=%d\n",&sizeVertexBuffer);
    VertexBuffer = malloc(2 * (sizeVertexBuffer) * sizeof(int)); 
    for (int i = 0; i < sizeVertexBuffer; i++)
    {
        fscanf(config,"%d %d\n",&VertexBuffer[i*2],&VertexBuffer[i*2+1]);
        
    }
    
    fclose(config);
}
void init(void)
{
    // select clearing (background) color 
    glViewport(0, 0, width, height);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    // initialize viewing values
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
    glTranslatef(-1.5f,0.0f,-6.0f);  
    windowRatio = width/height;


    loadConfig("config.txt");


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