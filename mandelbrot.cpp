
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

#define SLEEP_TIME 500

const int SIZE = 1024;
const int NUMBER = 142;
const float ORTH = 100;

// Init function for OpenGL
void init()
{
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1*ORTH, ORTH, -1*ORTH, ORTH, -1*ORTH, ORTH);
}

struct pointyboi {
  float x;
  float y;
  int num;
};

pointyboi arr[SIZE];

void drawer(int size) {
   glColor3f(1.0, 1.0, 1.0);
   glPointSize(9);
   glBegin(GL_POINTS);
   for(int i = 0; i < SIZE; ++i) {
     float sign = sin(i/(1.0*SIZE)*2*M_PI);
     float cosign = cos(i/(1.0*SIZE)*2*M_PI);

      glVertex2d(sign * size, cosign * size);

      arr[i].num = i;

      arr[i].x = sign * size;
      arr[i].y = cosign * size;
   }
   glEnd();
}

void drawline(int multiplier) {

  float startX, startY, endX, endY = 0.0;

  for(int i = 0; i < SIZE; i++) {

    startX = arr[i].x;
    startY = arr[i].y;

    endX = arr[(i + 1) * multiplier % SIZE].x;
    endY = arr[(i + 1) * multiplier % SIZE].y;

    glColor3f(0.0, 0.0, 1.0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex3f(startX, startY, 0);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(endX, endY, 0);
    glEnd();
  }
}

float multi = 2;
void display2()
{
     glClear(GL_COLOR_BUFFER_BIT);
     drawer(NUMBER);
     drawline(multi);
     glFlush();
}

void timer(int value)
{
   multi = multi + 1;
   if(multi >= SIZE)
      multi = 0;

   glutPostRedisplay();
   glutTimerFunc(SLEEP_TIME, timer, 0);
}

void keyboard(unsigned char key, int x, int y){

  if(key == 'r')
    multi = multi + 1;

  if(key == 's') {
    multi = multi - 1;
  }

  if(multi >= SIZE)
    multi = 0;
  else if(multi <= 0)
    multi = SIZE - 1;

    drawline(multi);

  glutPostRedisplay();
}

int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitWindowSize(1500, 1500);
   glutInitWindowPosition(250, 250);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
   glutCreateWindow("trippy");
   glutDisplayFunc(display2);

   glutKeyboardFunc(keyboard);
   glutTimerFunc(SLEEP_TIME, timer, 0);

   init();
   glutMainLoop();
   return 0;
}
