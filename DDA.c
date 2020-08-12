//Program for implementation of DDA LINE ALGORITHM
//SAKET.S.KHOPKAR    SI072
#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>

float X1,Y1,X2,Y2;

void display(void)
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	float dx,dy,step,x,y,k,xinc,yinc;
	dx=X2-X1;
	dy=Y2-Y1;
	
	if(abs(dx)>abs(dy))
	{
		step=abs(dx);
	}
	else
	{
		step=abs(dy);
	}
	xinc=dx/step;
	yinc=dy/step;
	
	x=X1;
	y=Y1;
	
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
	
	for(k=1;k<step;k++)
	{
		x=x+xinc;
		y=y+yinc;
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		glEnd();
	}	
	glFlush();
}

void init(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-100,100,-100,100);
}
int main(int argc, char** argv)
{
	printf("Enter the value of X1:-");
	scanf("%f",&X1);
	printf("Enter the value of X2:-");
	scanf("%f",&X2);
	printf("Enter the value of Y1:-");
	scanf("%f",&Y1);
	printf("Enter the value of Y2:-");
	scanf("%f",&Y2);
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(300,200);
	glutInitWindowPosition(0,0);
	glutCreateWindow("DDA Line Algorithm");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	
	return 0;
}	
	
