#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
int R,r,xc,yc,m,x,y;
float b_col[3], f_col[3];


int Round(float a)
{
  return (int)(a+0.5);
}

void dda(int X1,int Y1, int X2,int Y2)
{
  
  glColor3f(1.0,0.0,0.0);
  glBegin(GL_POINTS);
   int dx=X2-X1;
   int dy=Y2-Y1;
   int steps,i;
   float xinc,yinc,x=X1,y=Y1;
   if(abs(dx)>abs(dy))
   {
      steps=abs(dx);
   }
   else
   {
      steps=abs(dy);
   }
    xinc=dx/(float)steps;
    yinc=dy/(float)steps;
   
   glVertex2i(Round (x),Round (y));
   for(i=0;i<steps;i++)
   {
     x=x+xinc;
     y=y+yinc;
     glVertex2i(Round (x),Round (y));
   }
   glEnd();
   glFlush();
}

void plot_point(int x, int y)
{
  glBegin(GL_POINTS);
  glVertex2i(xc+x, yc+y);
  glVertex2i(xc+x, yc-y);
  glVertex2i(xc+y, yc+x);
  glVertex2i(xc+y, yc-x);
  glVertex2i(xc-x, yc-y);
  glVertex2i(xc-y, yc-x);
  glVertex2i(xc-x, yc+y);
  glVertex2i(xc-y, yc+x);
  glEnd();
}

void traingle()
 {
   dda(xc-m,yc-r,xc+m,yc-r);
   dda(xc-m,yc-r,xc,yc+R);
   dda(xc,yc+R,xc+m,yc-r);
 }
void cdraw1()
{
  int x=0,y=R;
  float pk=3-(2*R);
   /* Plot the points */
  /* Plot the first point */
  
  plot_point(x,y);
  int k;
  /* Find all vertices till x=y */
  while(x < y)
  {
    x = x + 1;
    if(pk < 0)
      pk = pk + 4*x+6;
    else
    {
      y = y - 1;
      pk = pk + 4*(x - y) + 10;
    }
    plot_point(x,y);
  }
  glFlush();
  
  traingle();
 
}
void cdraw()
{
  int x=0,y=r;
  float pk=3-(2*r);
   /* Plot the points */
  /* Plot the first point */
  
  plot_point(x,y);
  int k;
  /* Find all vertices till x=y */
  while(x < y)
  {
    x = x + 1;
    if(pk < 0)
      pk = pk + 4*x+6;
    else
    {
      y = y - 1;
      pk = pk + 4*(x - y) + 10;
    }
    plot_point(x,y);
  }
  glFlush();
  
  cdraw1();
}



void Init()
{
  /* Set clear color to white */
  glClearColor(1.0,1.0,1.0,0);
  /* Set fill color to black */
  glColor3f(1.0,0.0,0.0);
  /* glViewport(0 , 0 , 640 , 480); */
  /* glMatrixMode(GL_PROJECTION); */
  /* glLoadIdentity(); */
  gluOrtho2D(0 , 640 , 0 , 480);
}

void main(int argc, char **argv)
{
  
  int i;
  printf("\n Radius of circle");
   scanf("%d",&r);
   R=2*r;
   xc=x=320;
   yc=y=240;
   m=sqrt(R*R-r*r);
  printf("\nBoundry color");
  for(i=0;i<3;i++)
  {
   scanf("%f",&b_col[i]);
  }
   printf("\nFill color");
  for(i=0;i<3;i++)
  {
    scanf("%f",&f_col[i]);
  }
  /* Initialise GLUT library */
  glutInit(&argc,argv);
  /* Set the initial display mode */
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  /* Set the initial window position and size */
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  /* Create the window with title "DDA_Line" */
  glutCreateWindow("bresenham_circle");
  /* Initialize drawing colors */
  Init();
  /* Call the displaying function */
  glutDisplayFunc(cdraw);
  /* Keep displaying untill the program is closed */
  glutMainLoop();
}
