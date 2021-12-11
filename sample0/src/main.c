#define GLFW_INCLUDE_NONE
#include<stdio.h>
#include <GL/glut.h>
#include<GL/gl.h>

int width=640, height=480;
double time;


void init(void)
{
    // select clearing (background) color   
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // initialize viewing values
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
}

void display(){
      // clear all pixels
    glClear(GL_COLOR_BUFFER_BIT);

    //  draw white polygon with corners at (0.25,0.25,0.0) and (0.75,0.75,0.0)    
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
        glVertex3f(0.25,0.25,0.0);
        glVertex3f(0.75,0.25,0.0);
        glVertex3f(0.75,0.75,0.0);
        glVertex3f(0.25,0.75,0.0);
    glEnd();   

    // don't wait, start processing buffered OpenGL routines
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(250,250);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Hello");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}