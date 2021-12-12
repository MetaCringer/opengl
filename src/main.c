#include<stdio.h>
#include<stdlib.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<GL/gl.h>

int width=640, height=480;
const int webHeight=6,webWidth=webHeight*2 ;
double time;
GLFWwindow* window;
double windowRatio;
int * VertexBuffer;
int sizeVertexBuffer;
double x1, x2, y1, y2;



double dx(int x){
    return ((double)x+1)/webWidth;
}

double dy(int y){
    return ((double)y+1)/webHeight;
}
void pushVertex(int x, int y){
    glVertex3f(dx(x),dy(y),0.0);
}

void drawWeb(){
    glColor3f(0.4,0.4,0.4);
    glLineWidth(1);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1,0x00ff);
    glBegin(GL_LINES);
    for (int i = 1; i < webWidth; i++)
    {
        glVertex3f(((double)i)/webWidth,0.0,0.0);
        glVertex3f(((double)i)/webWidth,1.0,0.0);
    }
    for (int i = 1; i < height; i++)
    {
        glVertex3f(0.0,((double)i)/((double)webHeight),0.0);
        glVertex3f(1.0,((double)i)/((double)webHeight),0.0);
    }
    
    glEnd();
    glDisable(GL_LINE_STIPPLE);
}

void display(){
      // clear all pixels
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //  draw white polygon with corners at (0.25,0.25,0.0) and (0.75,0.75,0.0)    
    
    
    drawWeb();
    glColor3f(1.0,1.0,1.0);
    glLineWidth(4);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < sizeVertexBuffer; i++)
    {
        pushVertex(VertexBuffer[i*2],VertexBuffer[i*2+1]);
    }
    pushVertex(VertexBuffer[0],VertexBuffer[1]);
    glEnd();

    glPointSize(10.0);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_NOTEQUAL, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    
    glBegin(GL_POINTS);
    for (int i = 0; i < sizeVertexBuffer; i++)
    {
        pushVertex(VertexBuffer[i*2]+webHeight,VertexBuffer[i*2+1]);
    }
    glEnd();
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
    glViewport(0, 0, width, height);
    glClearColor(0.2, 0.2, 0.2, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //float aspect = (float)width / (float)height;
    glOrtho(0,1,0,1.0,-1.0,1.0);
    glfwSetWindowAspectRatio(window, 16, 9);
    glfwSetWindowOpacity(window, 0.8f);

    loadConfig("config.txt");
}


GLvoid OnResize(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
   
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
    glfwSetWindowSizeCallback(window, OnResize);
    while (!glfwWindowShouldClose(window))
    {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}