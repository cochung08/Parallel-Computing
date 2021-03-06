// 
// Jake Shankman 8 Nov 2012
// Mandelbrot Set
// 
// gcc -lm -lGLU -lglut -o demo demo.c
// 
#include <stdio.h>
#include <math.h>
// 
#include <GL/glut.h>
#define maxW 400.0
#define maxH 300.0
//
#include <complex.h>
//#undef I
//
//
double xMin = -2.0;
double xMax = 2.0;
double yMin = -1.5;
double yMax = 1.5;
int w, h;
double x = 200.0;
double y = 150.0;
int maxLoop = 100;
void mousefunc(int button,int state,int xscr,int yscr)
{
   if(button==GLUT_LEFT_BUTTON)
   {
      if(state==GLUT_DOWN)
      {
         
	double dx, dy;
	dx = (xMax - xMin);
	dy = (yMax - yMin);
	
	double x1 = xMin + dx * xscr/maxW ;
	double y1 = yMin + dy * (yscr)/maxH ;
	
	dx *= 0.5;
	dy *= 0.5;
	
	xMin = x1 - 0.5*dx;
	xMax = x1 + 0.5*dx;
	
	yMin = y1 - 0.5*dy;
	yMax = y1 + 0.5*dy;
	
	glutPostRedisplay();
      }
    }
   else if(button==GLUT_RIGHT_BUTTON)
     if(state ==GLUT_DOWN)
      {
	maxLoop *= 2;
	printf("loop doubled\n\n");
      }
}
void motionfunc(int xscr,int yscr)
{
   printf("(x,y)=(%d,%d)\n",xscr,yscr);
}
complex getColor(int i, int j)
{
  
  double a = (xMax - xMin)*(1.0 *i/maxW) + xMin;
  double b = (yMax - yMin)*(1.0 *(maxH - j)/maxH) + yMin;
  complex c = a + (b*I); 
  return c;

}
void displayfunc(void)
{
  
  printf("xMin=%f\nxMax=%f\nyMin=%f\nyMax=%f\n", xMin, xMax, yMin, yMax);
  
  
   glClear(GL_COLOR_BUFFER_BIT);
   glutSwapBuffers();
   int i = 0;
   int j = 0;
   int loop = 0;
   complex z = 0;
   while(i < maxW)
   {
     j=0;
     while(j < maxH)
     {
       loop = 0;
       double color;
       while(loop < maxLoop)
       {
	 if(cabs(z) > 2.0)
	 {
	   color = 1-  ((1.0*loop)/maxLoop);
	   break;
	 }
	 complex c = getColor(i, j);
	 
	 //
	 z = (z*z) + c;
	 //printf("z=%f\n", z);
	 loop++;
       }
       if(loop == maxLoop)
       {
	 glColor3f(0.0, 0.0, 0.0);
       }
       else
       {
	 //glColor3f(0.0, log(log(cabs(z))/log(2))/log(2), 0.0);
	 glColor3f(2*color, pow(color, 3), color/2 - 1);
       }
       glBegin(GL_POINTS);
       glVertex2f(i, j);
       glEnd();
       loop = 0;
       z = 0;
       //Continue loop
       j++;
     }
     i++;
     glutSwapBuffers();
   }
   // for GLUT_DOUBLE buffering glutSwapBuffers() instead
}
void reshapefunc(int wscr,int hscr)
{
   w=wscr; h=hscr;
   glViewport(0,0,(GLsizei)w,(GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0,1.0*w,0.0,1.0*h);
   glMatrixMode(GL_MODELVIEW);
}
void closefunc(void)
{
   printf("Window closed.\n");
}
int main(int argc,char* argv[])
{  
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // single buffering
   //
   glutInitWindowSize(400,300);
   glutInitWindowPosition(100,50);
   glutCreateWindow("Jake Shankman's Mandelbrot Set");
   //
   glClearColor(1.0,1.0,1.0,0.0); // red, green, blue, alpha
   glShadeModel(GL_SMOOTH);
   //
   glViewport(0,0,(GLsizei)400,(GLsizei)300);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0,400.0,0.0,300.0);
   glMatrixMode(GL_MODELVIEW);
   
   glutDisplayFunc(displayfunc); // register callback function
   glutIdleFunc(NULL);
   //
   glutMouseFunc(mousefunc);
   glutMotionFunc(motionfunc);
   glutReshapeFunc(reshapefunc);
   glutWMCloseFunc(closefunc);
   //
   glutMainLoop();
   //
   return 0;
}
// 
// end of file
// 
