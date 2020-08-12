#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>

int no;
float input[10][3],Trans_mat[10][3],tx,ty,xp,yp,angle,sx,sy,xf,yf,shx,shy;
float t[3][3];
int xa,ya,xb,yb;
int flag=0;

void LineDDA(int xa,int ya,int xb,int yb)
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

void get_vert()
{

 printf("\nEnter the number of vertices:");
  scanf("%d",&no);
  int j;
  for(j=0;j<no;j++)
  {
    printf("\nEnter the x coordinate of vertex:");
    scanf("%f",&input[j][0]);
    printf("\nEnter the y cordinate of vertex:");
    scanf("%f",&input[j][1]);
    input[j][2]=1;
  } 
  
} 

void mat_mult(float result[3][1],float trans[3][3],float input_vert[3][1])
 {
	int i,j,k;
	for(i=0;i<3;i++)
	for(j=0;j<1;j++)
		{
		 result[i][j]=0;
		  for(k=0;k<3;k++)
			 result[i][j]+=(trans[i][k]*input_vert[k][j]);
                         //printf("\n%f",result[i][j]);  
		}

 } 

void axis()
{
   int i;
   int x=20; 
   LineDDA(0,240,640,240);
   LineDDA(320,0,320,480);
   for(i=0;i<15;i++)
   {
    LineDDA(320+x,235,320+x,245);
    x=x+20;
   }

   x=20;
   for(i=0;i<15;i++)
   {
    LineDDA(320-x,235,320-x,245);
    x=x+20;
   }

   x=20;
   for(i=0;i<12;i++)
   {
    LineDDA(315,240+x,325,240+x);
    x=x+20;
   }

   x=20;
   for(i=0;i<12;i++)
   {
    LineDDA(315,240-x,325,240-x);
    x=x+20;
   }
}

void translation(float x, float y, float mat[3][3])
{
         
         int i,j; 
	 for(i=0;i<3;i++)
	  for(j=0;j<3;j++)
	   {
	   	 if(i==j)
      
   	 t[i][j]=1;
		 else
       		 t[i][j]=0;
	   }
	 t[0][2]=x;
	 t[1][2]=y;

        for(i=0;i<no;i++)
			   {
				 float mat1[3][1],mat2[3][1];
                                 /* Row is convrted into coloum*/
				 mat1[0][0]=mat[i][0];
				 mat1[1][0]=mat[i][1];
				 mat1[2][0]=mat[i][2];
				 mat_mult(mat2,t,mat1); //call by reference
                                 /* Coloum is converted into Row */
				 Trans_mat[i][0]=mat2[0][0];
				 Trans_mat[i][1]=mat2[1][0]; 
				 Trans_mat[i][2]=mat2[2][0];
			   }
 /*printf("\nTranaslation matrix is:");
       for(i=0;i<3;i++)
        for(j=0;j<3;j++)
         {
          printf("\n%f", Trans_mat[i][j]);
         }*/
}

void rotation(float x, float y, float r_angle,float mat[3][3])
{
         int i,j;
        //float r[3][3];
	t[2][2]=1;
	t[2][0]=t[2][1]=0;
	r_angle=(r_angle*3.14)/180;
        //printf("\nr_angle:%f",r_angle);
	t[0][0]=t[1][1]=cos(r_angle);
	t[0][1]=-sin(r_angle);
	t[1][0]=sin(r_angle);
        t[0][2]=x*(1-cos(r_angle))+y*sin(r_angle);
        t[1][2]=y*(1-cos(r_angle))-x*sin(r_angle);



                        for(i=0;i<no;i++)
			   {
				 float mat1[3][1],mat2[3][1];
                                 /* Row is convrted into coloum*/
				 mat1[0][0]=mat[i][0];
				 mat1[1][0]=mat[i][1];
				 mat1[2][0]=mat[i][2];
				 mat_mult(mat2,t,mat1); //call by reference
                                 /* Coloum is converted into Row */
				 Trans_mat[i][0]=mat2[0][0];
				 Trans_mat[i][1]=mat2[1][0]; 
				 Trans_mat[i][2]=mat2[2][0];
			   }
       /*printf("\nRotation matrix is:");
       for(i=0;i<3;i++)
        for(j=0;j<3;j++)
         {
          printf("\n%f", Trans_mat[i][j]);
         }*/

} 

void scaling(float f_x,float f_y, float x, float y, float mat[3][3])
{

    int i,j; 
	 for(i=0;i<3;i++)
	  for(j=0;j<3;j++)
	   {
	   	 if(i==j)
      
   	 t[i][j]=1;
		 else
       		 t[i][j]=0;
	   }
	 t[0][0]=x;
	 t[1][1]=y;
         t[0][2]=f_x*(1-x);
         t[1][2]=f_y*(1-y);

        for(i=0;i<no;i++)
			   {
				 float mat1[3][1],mat2[3][1];
                                 /* Row is convrted into coloum*/
				 mat1[0][0]=mat[i][0];
				 mat1[1][0]=mat[i][1];
				 mat1[2][0]=mat[i][2];
				 mat_mult(mat2,t,mat1); //call by reference
                                 /* Coloum is converted into Row */
				 Trans_mat[i][0]=mat2[0][0];
				 Trans_mat[i][1]=mat2[1][0]; 
				 Trans_mat[i][2]=mat2[2][0];
			   }
}


void reflection_x(float mat[3][3])
{
         
         int i,j; 
	 for(i=0;i<3;i++)
	  for(j=0;j<3;j++)
	   {
	   	 if(i==j)
      
   	 t[i][j]=1;
		 else
       		 t[i][j]=0;
	   }
	 t[1][1]=-1;


        for(i=0;i<no;i++)
			   {
				 float mat1[3][1],mat2[3][1];
                                 /* Row is convrted into coloum*/
				 mat1[0][0]=mat[i][0];
				 mat1[1][0]=mat[i][1];
				 mat1[2][0]=mat[i][2];
				 mat_mult(mat2,t,mat1); //call by reference
                                 /* Coloum is converted into Row */
				 Trans_mat[i][0]=mat2[0][0];
				 Trans_mat[i][1]=mat2[1][0]; 
				 Trans_mat[i][2]=mat2[2][0];
			   }
       /*printf("\nReflection matrix is:");
       for(i=0;i<3;i++)
        for(j=0;j<3;j++)
         {
          printf("\n%f", Trans_mat[i][j]);
         }*/
}

void reflection_y(float mat[3][3])
{
         
         int i,j; 
	 for(i=0;i<3;i++)
	  for(j=0;j<3;j++)
	   {
	   	 if(i==j)
      
   	 t[i][j]=1;
		 else
       		 t[i][j]=0;
	   }
	 t[0][0]=-1;


        for(i=0;i<no;i++)
			   {
				 float mat1[3][1],mat2[3][1];
                                 /* Row is convrted into coloum*/
				 mat1[0][0]=mat[i][0];
				 mat1[1][0]=mat[i][1];
				 mat1[2][0]=mat[i][2];
				 mat_mult(mat2,t,mat1); //call by reference
                                 /* Coloum is converted into Row */
				 Trans_mat[i][0]=mat2[0][0];
				 Trans_mat[i][1]=mat2[1][0]; 
				 Trans_mat[i][2]=mat2[2][0];
			   }
}

void reflection_origin(float mat[3][3])
{
         
         int i,j; 
	 for(i=0;i<3;i++)
	  for(j=0;j<3;j++)
	   {
	   	 if(i==j)
      
   	 t[i][j]=1;
		 else
       		 t[i][j]=0;
	   }
	 t[0][0]=-1;
         t[1][1]=-1;


        for(i=0;i<no;i++)
			   {
				 float mat1[3][1],mat2[3][1];
                                 /* Row is convrted into coloum*/
				 mat1[0][0]=mat[i][0];
				 mat1[1][0]=mat[i][1];
				 mat1[2][0]=mat[i][2];
				 mat_mult(mat2,t,mat1); //call by reference
                                 /* Coloum is converted into Row */
				 Trans_mat[i][0]=mat2[0][0];
				 Trans_mat[i][1]=mat2[1][0]; 
				 Trans_mat[i][2]=mat2[2][0];
			   }
}

void reflection_yx(float mat[3][3])
{
         
         int i,j; 
	 for(i=0;i<3;i++)
	  for(j=0;j<3;j++)
	   {
	      t[i][j]=0;
	   }
	 t[0][1]=1;
         t[1][0]=1;
         t[2][2]=1; 


        for(i=0;i<no;i++)
			   {
				 float mat1[3][1],mat2[3][1];
				 mat1[0][0]=mat[i][0];
				 mat1[1][0]=mat[i][1];
				 mat1[2][0]=mat[i][2];
				 mat_mult(mat2,t,mat1); //call by reference
				 Trans_mat[i][0]=mat2[0][0];
				 Trans_mat[i][1]=mat2[1][0]; 
				 Trans_mat[i][2]=mat2[2][0];
			   }

}
    
void reflection_ynegativex(float mat[3][3])
{
         
         int i,j; 
	 for(i=0;i<3;i++)
	  for(j=0;j<3;j++)
	   {
	      t[i][j]=0;
	   }
	 t[0][1]=-1;
         t[1][0]=-1;
         t[2][2]=1; 


        for(i=0;i<no;i++)
			   {
				 float mat1[3][1],mat2[3][1];
				 mat1[0][0]=mat[i][0];
				 mat1[1][0]=mat[i][1];
				 mat1[2][0]=mat[i][2];
				 mat_mult(mat2,t,mat1); //call by reference
				 Trans_mat[i][0]=mat2[0][0];
				 Trans_mat[i][1]=mat2[1][0]; 
				 Trans_mat[i][2]=mat2[2][0];
			   }

}

void reflection_a()
{
 translation(-xa,-ya,input);
 float slope=(yb-ya)/(float)(xb-xa);
 angle=atan(slope);
 printf("\nAngle is:%f",angle);
 angle=(angle*180)/3.14;
 rotation(0,0,-angle,Trans_mat);
 reflection_x(Trans_mat);
 rotation(0,0,angle,Trans_mat);
 translation(xa,ya,Trans_mat);
}

void shear_x(float mat[3][3],int x)
{
         
         int i,j; 
	 for(i=0;i<3;i++)
	  for(j=0;j<3;j++)
	   {
	   	 if(i==j)
      
   	 t[i][j]=1;
		 else
       		 t[i][j]=0;
	   }

	 t[0][1]=x;
 
        for(i=0;i<no;i++)
			   {
				 float mat1[3][1],mat2[3][1];
				 mat1[0][0]=mat[i][0];
				 mat1[1][0]=mat[i][1];
				 mat1[2][0]=mat[i][2];
				 mat_mult(mat2,t,mat1); //call by reference
				 Trans_mat[i][0]=mat2[0][0];
				 Trans_mat[i][1]=mat2[1][0]; 
				 Trans_mat[i][2]=mat2[2][0];
			   }

}
 
void shear_y(float mat[3][3],int y)
{
         
         int i,j; 
	 for(i=0;i<3;i++)
	  for(j=0;j<3;j++)
	   {
	   	 if(i==j)
      
   	 t[i][j]=1;
		 else
       		 t[i][j]=0;
	   }
	 t[1][0]=y; 


        for(i=0;i<no;i++)
			   {
				 float mat1[3][1],mat2[3][1];
				 mat1[0][0]=mat[i][0];
				 mat1[1][0]=mat[i][1];
				 mat1[2][0]=mat[i][2];
				 mat_mult(mat2,t,mat1); //call by reference
				 Trans_mat[i][0]=mat2[0][0];
				 Trans_mat[i][1]=mat2[1][0]; 
				 Trans_mat[i][2]=mat2[2][0];
			   }

}

void D_Trans()
{
  glClear(GL_COLOR_BUFFER_BIT);
  
  int i,j;

  axis();

  if(flag==1)
  {
   LineDDA(320+xa,240+ya,320+xb,240+yb);
  } 

  for(i=0,j=1;i<no-1;i++,j++)
  {
   LineDDA(320+input[i][0],240+input[i][1],320+input[j][0],240+input[j][1]);
  }
 
   LineDDA(320+input[i][0],240+input[i][1],320+input[0][0],240+input[0][1]);
 
  //int k;

    //translation(tx,ty);  

		 /*for(i=0;i<no;i++)
			   {
				 float mat1[3][1],mat2[3][1];
                                  Row is convrted into coloum
				 mat1[0][0]=mat[i][0];
				 mat1[1][0]=mat[i][1];
				 mat1[2][0]=mat[i][2];
				 mat_mult(mat2,t,mat1); //call by reference
                                 /* Coloum is converted into Row 
				 mat[i][0]=mat2[0][0];
				 mat[i][1]=mat2[1][0]; 
				 mat[i][2]=mat2[2][0];
			   }*/
  
  //int i,j;
  for(i=0,j=1;i<no-1;i++,j++)
  {
   LineDDA(320+Trans_mat[i][0],240+Trans_mat[i][1],320+Trans_mat[j][0],240+Trans_mat[j][1]);
  }
 
   LineDDA(320+Trans_mat[i][0],240+Trans_mat[i][1],320+Trans_mat[0][0],240+Trans_mat[0][1]);
 }




 

void Init()
{
  /* Set clear color to white */
  glClearColor(1.0,1.0,1.0,0);
  /* Set fill color to black */
  glColor3f(0.0,0.0,0.0);
  /* glViewport(0 , 0 , 640 , 480); */
  /* glMatrixMode(GL_PROJECTION); */
  /* glLoadIdentity(); */
  gluOrtho2D(0 , 640 , 0 , 480);
}


int main(int argc, char **argv)
{
    int ch;
    printf("1:Translation\n2:Rotation\n3:Scaling\n4:Reflection along x axis\n5:Reflection along y axis:\n6:reflection about arbitrarl line:");
    printf("\n7:reflection about origin:\n8:reflection about y=x:\n9:reflection about y=-x\n10:Shear along x direction\n11:Shear along y direction");
    printf("\nEnter the choice:");
    scanf("%d",&ch);
    
    switch(ch)
    {
      case 1:	
              get_vert();
              printf("\nEnter the translational factors tx and ty:");
              scanf("%f%f",&tx,&ty);
              translation(tx,ty,input);      
              break;

      case 2: get_vert();
              printf("\nEnter the pivot point:");
              scanf("%f%f",&xp,&yp);
              printf("\nEnter the angle:");
              scanf("%f",&angle); 
              rotation(xp,yp,angle,input);
              break;
          
      case 3: get_vert();
              printf("\nEnter the fixed point:");
              scanf("%f%f",&xf,&yf);
              printf("\nEnter the scaling factors sx and sy:");
              scanf("%f%f",&sx,&sy);
              scaling(xf,yf,sx,sy,input);    
              break;     

      case 4: get_vert();
              reflection_x(input);
              break;     

      case 5: get_vert();
              reflection_y(input);
              break;               

      case 6: printf("\nEnter the first point:");
              scanf("%d%d",&xa,&ya);
              printf("\nEnter the second point:");
              scanf("%d%d",&xb,&yb);
              get_vert();
              reflection_a(); 
              flag=1;
              break;
      
      case 7: get_vert();
              reflection_origin(input);
              break; 

      case 8: get_vert();
              reflection_yx(input);
              break; 
       
      case 9: get_vert();
              reflection_ynegativex(input);
              break;  

      case 10: get_vert();
	       printf("\nEnter the x shear factor:");
               scanf("%f",&shx);
               shear_x(input,shx);
               break;

      case 11: get_vert();
	       printf("\nEnter the y shear factor:");
               scanf("%f",&shy);
               shear_y(input,shy);
               break;

      default: printf("\nWrong choice:");
    }

  /* Initialise GLUT library */
  glutInit(&argc,argv);
  /* Set the initial display mode */
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  /* Set the initial window position and size */
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  /* Create the window with title "DDA_Line" */
  glutCreateWindow("2-D Transformation");
  /* Initialize drawing colors */
  Init();
  /* Call the displaying function */
  glutDisplayFunc(D_Trans);
  /* Keep displaying untill the program is closed */
  glutMainLoop();
}




