#include<stdio.h>
//#include<stdlib.h>
#include<math.h>
//#include<GL/gl.h>
//#include<GL/glu.h>
#include<GL/glut.h>
float mat[3][24],trans[3][3],res[3][24];
//float bgCol[3] = {0.2, 0.4,0.0};   
float intCol[3] = {1.0,1.0,1.0};   
float fillCol[3] = {0.0,0.0,0.0}; 
  int ww = 600, wh = 500;  
/*struct Color 
{
	GLfloat red;
	GLfloat green;
	GLfloat blue;
};*/
void Init()
{
	glClear(GL_COLOR_BUFFER_BIT);
  	glClearColor(1,1,1,0);
  	glClear(GL_COLOR_BUFFER_BIT );
  	glColor3ub(0,0,0);
  	gluOrtho2D(0 , 1020 , 0 , 660);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

/*Color getPixelColor(GLint x, GLint y) 
{
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}

void setPixelColor(GLint x, GLint y, Color color) 
{
	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}*/
  
      void setPixel(int pointx, int pointy, float f[3])   
      {   
             glBegin(GL_POINTS);   
                  glColor3fv(f);   
                  glVertex2i(pointx,pointy);   
             glEnd();   
             glFlush();   
      }   
      void getPixel(int x, int y, float pixels[3])   
      {   
           glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,pixels);   
      }   
      
      
void floodFill(GLint x, GLint y, float oldColor[3], float newColor[3]) 
{
	float color[3];
	getPixel(x, y,color);

	if(color[0]== oldColor[0] && (color[1]) == oldColor[1] && color[2] == oldColor[2])
	{
		setPixel(x, y, newColor);
		floodFill(x+1, y, oldColor, newColor);
		floodFill(x, y+1, oldColor, newColor);
		floodFill(x-1, y, oldColor, newColor);
		floodFill(x, y-1, oldColor, newColor);
	}
	return;
}

void mult()
{
 	int i,j,k;
 	for(i=0;i<3;i++)
 	{
  		for(j=0;j<24;j++)
  		{
   			res[i][j]=0;
   			for(k=0;k<3;k++)
   			{
    				res[i][j]+=trans[i][k]*mat[k][j];
   			}
  		}	
 	}

}

 int sign(int a)
 {
 	if(a>=0)
		return 1;
 	else
 		return -1;
 }

void breshnam(int xp1,int yp1,int xp2,int yp2)
{
 int x,y,dx,dy,dx2,dy2,sdx,sdy,steps,pk,i;
 char str[10];
 dx=xp2-xp1;
 dy=yp2-yp1;
 if(abs(dy)>abs(dx))
 {
  	steps=abs(dy);
  	if(yp1<yp2)
  	{
   		x=xp1;y=yp1;
  	}
  	else
  	{
   		x=xp2;y=yp2;
  	 dx=xp1-xp2;dy=yp1-yp2;
  	}

   dx2=2*abs(dx);
   dy2=2*abs(dy);
   sdx=sign(dx);
   sdy=sign(dy);

  pk=dx2-abs(dy);
  glBegin(GL_POINTS);
  glVertex2i(x,y);

  for(i=0;i<steps;i++)
  {
   	if(pk<0)
   	{
   		 y++;
    		pk=pk+dx2;
   	}
  	else
   	{
    		y++;x=x+sdx;
    		pk=pk+dx2-dy2;
   	}
   	glVertex2i(x,y);
  }

  glEnd();
  glFlush();
 }

 else
 {
  	steps=abs(dx);
  	if(xp1<xp2)
  	{
  		 x=xp1;y=yp1;
  	}
  	else
  	{
   		x=xp2;y=yp2;
   		dx=xp1-xp2;dy=yp1-yp2;
  	}

   dx2=2*abs(dx);
   dy2=2*abs(dy);
   sdx=sign(dx);
   sdy=sign(dy);

  pk=dy2-abs(dx);
  glBegin(GL_POINTS);
  glVertex2i(x,y);

  for(i=0;i<steps;i++)
  {
  	if(pk<0)
   	{
    		x++;
   		pk=pk+dy2;
   	}
   	else
   	{
   		y=y+sdy;x++;
    		pk=pk+dy2-dx2;
   	}
  	 glVertex2i(x,y);
  }

  glEnd();
  glFlush();
 }
}

void initmat()
{
int ymax=glutGet(GLUT_WINDOW_HEIGHT),xmax=glutGet(GLUT_WINDOW_WIDTH);
 int a=xmax/2+100,b=100,i;
//printf("%d\n",xmax);
 for(i=0;i<5;i++)
 {
  mat[0][i]=a;
  mat[1][i]=b;
  mat[2][i]=1;
  a+=30;
 }
 a=xmax/2+220;b=130;
 for(i=5;i<9;i++)
 {
  mat[0][i]=a;
  mat[1][i]=b;
  mat[2][i]=1;
  b+=30;
 }
 a=xmax/2+190;b=220;
 for(i=9;i<13;i++)
 {
  mat[0][i]=a;
  mat[1][i]=b;
  mat[2][i]=1;
  a-=30;
 }
 a=xmax/2+100;b=190;
 for(i=13;i<16;i++)
 {
  mat[0][i]=a;
  mat[1][i]=b;
  mat[2][i]=1;
  b-=30;
 }
a=xmax/2+115,b=115;
for(i=16;i<20;i++)
 {
  mat[0][i]=a;
  mat[1][i]=b;
  mat[2][i]=1;
  a+=60;
if(i==17)
{
  b+=60;
  a=xmax/2+115;
}
  
 }
a=xmax/2+145,b=145;
for(i=20;i<24;i++)
 {
  mat[0][i]=a;
  mat[1][i]=b;
  mat[2][i]=1;
  a+=60;
if(i==21)
{
  b+=60;
  a=xmax/2+145;
 }
}

for(i=16;i<24;i++)
		printf("\n%f   %f", mat[0][i],mat[1][i]);

 trans[0][0]=0.707;
 trans[0][1]=-0.707;
 trans[0][2]=0;
 trans[1][0]=0.707;
 trans[1][1]=0.707;
 trans[1][2]=0;
 trans[2][0]=0;
 trans[2][1]=0;
 trans[2][2]=1;

}

void drawcb(float mat[3][24])
{
int i;

breshnam(mat[0][0],mat[1][0],mat[0][4],mat[1][4]);
 for(i=0;i<5;i++)
 {
  breshnam(mat[0][i],mat[1][i],mat[0][12-i],mat[1][12-i]);

 }

 for(i=5;i<9;i++)
 {
  breshnam(mat[0][i],mat[1][i],mat[0][20-i],mat[1][20-i]);
 }

  

for(i=16;i<24;i++)
 {
printf("\nFILLING");
floodFill(mat[0][i],mat[1][i],intCol,fillCol);   

  /*void mouse(int btn, int state, int x, int y)   
       {   
             if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)    
            {   
                     int xi = x;   
                     int yi = (wh-y);   
                     
             }   
       } */  
 }

}

void draw()
{
	initmat();
	drawcb(mat);
	mult();
	drawcb(res);
}

int main(int argc,char ** argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(1020,660);
  glutCreateWindow("chess board");
  Init();
  glutDisplayFunc(draw);
  glutMainLoop();
  return 0;
}
