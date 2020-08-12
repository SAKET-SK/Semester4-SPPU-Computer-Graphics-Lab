 
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
 
#define  RADDEG  57.29577951f
 
float XUP[3] = {1,0,0}, XUN[3] = {-1, 0, 0},
      YUP[3] = {0,1,0}, YUN[3] = { 0,-1, 0},
      ZUP[3] = {0,0,1}, ZUN[3] = { 0, 0,-1},
      ORG[3] = {0,0,0};
 
GLfloat viewangle = 0, tippangle = 0, traj[120][3];
 
GLfloat d[3] = {0.1, 0.1, 0.1};
 
GLfloat  xAngle = 0.0, yAngle = 0.0, zAngle = 0.0;
 
 
//---+----3----+----2----+----1----+---<>---+----1----+----2----+----3----+----4
 
//  Use arrow keys to rotate entire scene !!!
 
void Special_Keys (int key, int x, int y)
{
    switch (key) {
 
       case GLUT_KEY_LEFT :  viewangle -= 5;  break;
       case GLUT_KEY_RIGHT:  viewangle += 5;  break;
       case GLUT_KEY_UP   :  tippangle -= 5;  break;
       case GLUT_KEY_DOWN :  tippangle += 5;  break;
 
       default: printf ("   Special key %c == %d\n", key, key);
    }
 
    glutPostRedisplay();
}
 
//---+----3----+----2----+----1----+---<>---+----1----+----2----+----3----+----4
 
void Keyboard (unsigned char key, int x, int y)
{
    switch (key) {
 
       case 'j' : d[0] += 0.1;  break;
       case 'k' : d[1] += 0.1;  break;
       case 'l' : d[2] += 0.1;  break;
       
       case 'b' : d[0] += 0.1;  break;
       case 'n' : d[1] += 0.1;  break;
       case 'm' : d[2] += 0.1;  break;
       
       case 'x' : xAngle += 5;  break;
       case 'y' : yAngle += 5;  break;
       case 'z' : zAngle += 5;  break;
 
       default: printf ("   Keyboard %c == %d\n", key, key);
    }
 
    glutPostRedisplay();
}
 
//---+----3----+----2----+----1----+---<>---+----1----+----2----+----3----+----4
 
void Triad (void)
{
    glColor3f (1.0, 1.0, 1.0);
 
    glBegin (GL_LINES);
       glVertex3fv (ORG); glVertex3fv (XUP);
       glVertex3fv (ORG); glVertex3fv (YUP);
       glVertex3fv (ORG); glVertex3fv (ZUP);
    glEnd ();
 
    glRasterPos3f (1.1, 0.0, 0.0);
    glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, 'X');
 
    glRasterPos3f (0.0, 1.1, 0.0);
    glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, 'Y');
 
    glRasterPos3f (0.0, 0.0, 1.1);
    glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, 'Z');
}
 
//---+----3----+----2----+----1----+---<>---+----1----+----2----+----3----+----4
 
void Draw_Box (void)
{
    glBegin (GL_QUADS);
 
      glColor3f  ( 0.0,  0.7, 0.1);     // Front - green
      glVertex3f (-1.0,  1.0, 1.0);
      glVertex3f ( 1.0,  1.0, 1.0);
      glVertex3f ( 1.0, -1.0, 1.0);
      glVertex3f (-1.0, -1.0, 1.0);
 
      glColor3f  ( 0.9,  1.0,  0.0);    // Back  - yellow
      glVertex3f (-1.0,  1.0, -1.0);
      glVertex3f ( 1.0,  1.0, -1.0);
      glVertex3f ( 1.0, -1.0, -1.0);
      glVertex3f (-1.0, -1.0, -1.0);
 
      glColor3f  ( 0.2, 0.2,  1.0);     // Top - blue 
      glVertex3f (-1.0, 1.0,  1.0);
      glVertex3f ( 1.0, 1.0,  1.0);
      glVertex3f ( 1.0, 1.0, -1.0);
      glVertex3f (-1.0, 1.0, -1.0);
 
      glColor3f  ( 0.7,  0.0,  0.1);    // Bottom - red
      glVertex3f (-1.0, -1.0,  1.0);
      glVertex3f ( 1.0, -1.0,  1.0);
      glVertex3f ( 1.0, -1.0, -1.0);
      glVertex3f (-1.0, -1.0, -1.0);
 
    glEnd();
}
 
//---+----3----+----2----+----1----+---<>---+----1----+----2----+----3----+----4
 
void redraw (void)
{
    int v;
 
    glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable (GL_DEPTH_TEST);
 
    glLoadIdentity ();
 
    glTranslatef (0, 0, -3);
    glRotatef (tippangle, 1,0,0);  // Up and down arrow keys 'tip' view.
    glRotatef (viewangle, 0,1,0);  // Right/left arrow keys 'turn' view.
 
    glDisable (GL_LIGHTING);
 
    Triad ();
 
    glPushMatrix ();
       glTranslatef (d[0], d[1], d[2]);    // Move box down X axis.
       glScalef (0.2, 0.2, 0.2);
       glRotatef (zAngle, 0,0,1);
       glRotatef (yAngle, 0,1,0);
       glRotatef (xAngle, 1,0,0);
       Draw_Box ();
    glPopMatrix ();
 
    glutSwapBuffers();
}
 
//---+----3----+----2----+----1----+---<>---+----1----+----2----+----3----+----4
 
int main (int argc, char **argv)
{
    glutInit               (&argc, argv);
    glutInitWindowSize     (900, 600);
    glutInitWindowPosition (300, 300);
    glutInitDisplayMode    (GLUT_DEPTH | GLUT_DOUBLE);
 
    glutCreateWindow ("Orbital Font Demo");
    glutDisplayFunc  (   redraw   );
    glutKeyboardFunc (  Keyboard  );
    glutSpecialFunc  (Special_Keys);
 
    glClearColor (0.1, 0.0, 0.1, 1.0);
 
    glMatrixMode   (GL_PROJECTION);
    gluPerspective (60, 1.5, 1, 10);
    glMatrixMode   (GL_MODELVIEW);
    glutMainLoop   ();
 
    return 1;
}
 	
