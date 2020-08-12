/**
 *	Koch Snowflake, part of Assignment one
 *  CSCI 4550 - Marcus Young - 9/20/10
 *
 **/

#include <GL/glut.h>
#include <math.h>

GLfloat oldx=-0.7,oldy=0.5;

void drawkoch(GLfloat dir,GLfloat len,GLint iter) {
	GLdouble dirRad = 0.0174533 * dir;  
	GLfloat newX = oldx + len * cos(dirRad);
	GLfloat newY = oldy + len * sin(dirRad);
	if (iter==0) {
		glVertex2f(oldx, oldy);
		glVertex2f(newX, newY);
		oldx = newX;
		oldy = newY;
	}
	else {
		iter--;
		//draw the four parts of the side _/\_ 
		drawkoch(dir, len, iter);
		dir += 60.0;
		drawkoch(dir, len, iter);
		dir -= 120.0;
		drawkoch(dir, len, iter);
		dir += 60.0;
		drawkoch(dir, len, iter);
	}
}

void mydisplay(){
	 glClear( GL_COLOR_BUFFER_BIT );
	 glBegin(GL_LINES);
	 glColor3f(1.0, 0.0, 0.0); // make it red
	 
	 //call drawkoch 3 times, one for each side of the triangle, changing direction each time

	
	 drawkoch(0.0,0.015,4);
	 drawkoch(-120.0, 0.015, 4);
	 drawkoch(120.0,0.015,4);
	 
	/* 
	 glColor3f(0.0, 1.0, 0.0);
	 drawkoch(0.0,0.15,2);
	 drawkoch(-120.0, 0.15, 2);
	 drawkoch(120.0,0.15,2);
	
  	 glColor3f(0.0, 0.0, 1.0);
	 drawkoch(0.0,0.05,3);
	 drawkoch(-120.0, 0.05, 3);
	 drawkoch(120.0,0.05,3);*/
	 
	 glEnd();
	 glFlush(); 
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv); 
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);      
	glutInitWindowSize(500,500);    	
	glutInitWindowPosition(0,0); 
	glutCreateWindow("Koch Snowflake - Marcus Young");     
	glutDisplayFunc(mydisplay);  
	glutMainLoop();
}
