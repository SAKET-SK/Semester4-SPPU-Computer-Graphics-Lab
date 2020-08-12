#include <math.h>
#include <glut.h>
#include <stdio.h>
#include<windows.h>

int xmin,ymin,xmax,ymax,arr[20],k=0,n,a[20];

void clip_left(int,int,int,int);
void clip_right(int,int,int,int);
void clip_top(int,int,int,int);
void clip_below(int,int,int,int);

void lineDDA(int xa,int ya,int xb,int yb)
{
  int dx=(xb-xa);
  int dy=(yb-ya);
  int steps;
  float xInc,yInc,x=xa,y=ya;
  /* Find out whether to increment x or y */
  steps=(abs(dx)>abs(dy))?(abs(dx)):(abs(dy));
  xInc=dx/(float)steps;
  yInc=dy/(float)steps;

  /* Clears buffers to preset values */
  

  /* Plot the points */
  glBegin(GL_POINTS);
  /* Plot the first point */
  glVertex2i(x,y);
  int k;
  /* For every step, find an intermediate vertex */
  for(k=0;k<steps;k++)
  {
    x+=xInc;
    y+=yInc;
    /* printf("%0.6lf %0.6lf\n",floor(x), floor(y)); */
    glVertex2i(floor(x+0.5),floor(y+0.5));
  }
  glEnd();

  glFlush();
}

void Init()
{
  /* Set clear color to white */
  glClearColor(1.0,1.0,1.0,0);
  /* Set fill color to Black */
  glColor3f(0.0,0.0,0.0);
  /* glViewport(0 , 0 , 640 , 480); */
  /* glMatrixMode(GL_PROJECTION); */
  /* glLoadIdentity(); */
  gluOrtho2D(0 , 640 , 0 , 480);
}

void P_Clip()
{
 
  int i,j;

  glClear(GL_COLOR_BUFFER_BIT);   

  for(i=0,j=0;j<n;i=i+2,j=j+1)
  {
   lineDDA(a[i],a[i+1],a[i+2],a[i+3]);
  }

 lineDDA(xmin,ymin,xmax,ymin);
 lineDDA(xmax,ymin,xmax,ymax);
 lineDDA(xmax,ymax,xmin,ymax);
 lineDDA(xmin,ymax,xmin,ymin);


 for(i=0;i<(2*n);i+=2)
 {
  clip_left(a[i],a[i+1],a[i+2],a[i+3]);
 }

 for(i=0;i<k;i++)
 {
  a[i]=arr[i];
 }

 a[i]=a[0];
 a[i+1]=a[1];
 n=(k/2);
 k=0;

 for(i=0;i<2*n;i+=2)
 {
   clip_right(a[i],a[i+1],a[i+2],a[i+3]);
 }

 for(i=0;i<k;i++)
 {
  a[i]=arr[i];
 }
 a[i]=a[0];
 a[i+1]=a[1];
 n=(k/2);
 k=0;

 for(i=0;i<2*n;i+=2)
 {
  clip_below(a[i],a[i+1],a[i+2],a[i+3]);
 }

 for(i=0;i<k;i++)
 {
  a[i]=arr[i];
 }
 a[i]=a[0];
 a[i+1]=a[1];
 n=(k/2);
 k=0;

 for(i=0;i<2*n;i+=2)
 {
  clip_top(a[i],a[i+1],a[i+2],a[i+3]);
 }

 for(i=0;i<k;i++)
 {
  a[i]=arr[i];
 }
 a[i]=a[0];
 a[i+1]=a[1];

 glColor3f(1.0,0.0,0.0);

 for(i=0,j=0;j<k/2;i=i+2,j=j+1)
  {
   lineDDA(a[i],a[i+1],a[i+2],a[i+3]);
  }

 //printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7]);
}


void clip_left(int x1,int y1,int x2,int y2)
{
 
 
 float m=(y2-y1)/(float)(x2-x1);
 
 
 if(x1>xmin && x2 >xmin)//in->in
 {
  arr[k]=x2;
  arr[k+1]=y2;
  k+=2;
 }

 if(x1<xmin && x2>xmin)//out->in
 {
  arr[k]=xmin;
  arr[k+1]=y1+(m*(float)(xmin-x1));
  arr[k+2]=x2;
  arr[k+3]=y2;
  k+=4;
 }

 if(x2<xmin && x1>xmin)//in->out
 {
 arr[k]=xmin;
 arr[k+1]=y2+(m*(float)(xmin-x2));
 k+=2;
 }
}

void clip_right(int x1,int y1,int x2,int y2)
{
 float m=(y2-y1)/(float)(x2-x1);
 
 if(x1<xmax && x2 <xmax)
 {
  arr[k]=x2;
  arr[k+1]=y2;
  k+=2;
 }

 if(x1>xmax && x2<xmax)
 {
  arr[k]=xmax;
  arr[k+1]=y1+(m*(float)(xmax-x1));
  arr[k+2]=x2;
  arr[k+3]=y2;
  k+=4;
 }

 if(x1<xmax && x2>xmax)
 {
  arr[k]=xmax;
  arr[k+1]=y1+(m*(float)(xmax-x1));
  k+=2;

 }
}

void clip_below(int x1,int y1,int x2,int y2)
{
 float m=(x2-x1)/(float)(y2-y1);
 
 
 if(y1>ymin && y2>ymin)
 {
  arr[k]=x2;
  arr[k+1]=y2;
  k+=2;
 }

 if(y1<ymin && y2>ymin)
 {
  arr[k+1]=ymin;
  arr[k]=x1+(m*(float)(ymin-y1));
  arr[k+2]=x2;
  arr[k+3]=y2;
  k+=4;
 }

 if(y1>ymin && y2<ymin)
 {
  arr[k+1]=ymin;
  arr[k]=x1+(m*(float)(ymin-y1));
  k+=2;
 }
}


void clip_top(int x1,int y1,int x2,int y2)
{
 float m=(x2-x1)/(float)(y2-y1);

 if(y1<ymax && y2 <ymax)
 {
  arr[k]=x2;
  arr[k+1]=y2;
  k+=2;
 }

 if(y1>ymax && y2<ymax)
 {
  arr[k+1]=ymax;
  arr[k]=(float)x1+(m*(float)(ymax-y1));
  arr[k+2]=x2;
  arr[k+3]=y2;
  k+=4;
 }

 if(y1<ymax && y2>ymax)
 {
  arr[k+1]=ymax;
  arr[k]=(float)x1+(m*(float)(ymax-y1));
  k+=2;
 }
}

int main(int argc, char **argv)
{
 printf("\nEnter the xmin and ymin value of a rectangle:");
 scanf("%d%d",&xmin,&ymin);
 printf("\nEnter the xmax and ymax value of a rectangle:");
 scanf("%d%d",&xmax,&ymax);

 printf("\nnumber of vertices of polygon:");
 scanf("%d",&n);

 int i;

 for(i=0;i<2*n;i+=2)
  {
    printf("\nEnter the value of x:");
    scanf("%d",&a[i]);
    printf("\nEnter the value of y:");
    scanf("%d",&a[i+1]);;
  }

  a[2*n]=a[0];
  a[(2*n)+1]=a[1];

/* Initialise GLUT library */
  glutInit(&argc,argv);
  /* Set the initial display mode */
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  /* Set the initial window position and size */
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  /* Create the window with title "DDA_Line" */
  glutCreateWindow("Polygon Filling");
  /* Initialize drawing colors */
  Init();
  /* Call the displaying function */
  glutDisplayFunc(P_Clip);
  /* Keep displaying untill the program is closed */
  glutMainLoop();
}


