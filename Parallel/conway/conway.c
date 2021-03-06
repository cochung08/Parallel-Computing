// 
// Jake Shankman 10 Dec 2012
// Conway in Serial
// 
// gcc -lm -lGLU -lglut -o demo demo.c
// 
#include <stdio.h>
#include <math.h>
//#include <dos.h>
// 
#include <GL/glut.h>
#define maxW 400
#define maxH 300
//
//
int grid [(maxW/10)][(maxH/10)];
int flag = 0;
int w, h;
int sleep = 100000;
void mousefunc(int button,int state,int xscr,int yscr)
{
   if(button==GLUT_LEFT_BUTTON)
   {
      if(state==GLUT_DOWN)
      {
	int x, y;
	x = xscr/10;
	y = (maxH - yscr)/10;
	if(grid[x][y] == 0)
	{
	  grid[x][y] = 1;
	  printf("change\n");
	}
	else
	{
	  grid[x][y] = 0;
	}
	glutPostRedisplay();
      }
    }
   else if(button==GLUT_RIGHT_BUTTON)
     if(state ==GLUT_DOWN)
      {
	flag = !flag;
	printf("flag=%i\n", flag);
      }
}
void motionfunc(int xscr,int yscr)
{
   printf("(x,y)=(%d,%d)\n",xscr,yscr);
   mousefunc(GLUT_LEFT_BUTTON, GLUT_DOWN,xscr, yscr);
}
int neighbors(int xpos, int ypos)
{
  int count = 0;
  int i, j;
  
  for(i = -1; i < 2; ++i)
  {
    for(j = -1; j < 2; ++j)
    {
      if( i != 0 || j != 0)
      {
	
	int xnbr=xpos+i;
	int ynbr=ypos+j;
	
	if(xnbr<0) 
	  xnbr=maxW/10-1;
	if(xnbr>maxW/10-1)
	  xnbr=0;
	if(ynbr<0)
	  ynbr = maxH/10 -1;
	if(ynbr>maxH/10 -1)
	  ynbr = 0;
	if(grid[xnbr][ynbr] == 1)
	{
	  printf("h\n");
	  ++count;
	}
      }
    }
  }   
  return count;
}
int alive(int xpos, int ypos)
{
  int n = neighbors(xpos, ypos);
  if(grid[xpos][ypos] == 1)
  {
    if(n == 2 || n == 3)
    {
      return 1;
    }
    else
      return 0;
  }
  else
  {
    if(n == 3)
      return 1;
    else
      return 0;
  }
}
void idlefunc()
{
  if(flag == 0)
  {
   usleep(sleep);
   int i, j;
   int next [(maxW/10)][(maxH/10)];
   for(i = 0; i < maxW/10; ++i)
   {
     for(j = 0; j < maxH/10; ++j)
       next[i][j] = alive(i, j);
   }
    for(i = 0; i < maxW/10; ++i)
   {
     for(j = 0; j < maxH/10; ++j)
       grid[i][j] = next[i][j];
   }
    glutPostRedisplay();
    printf("ok\n");
  }
  }
void displayfunc(void)
{ 
   glClear(GL_COLOR_BUFFER_BIT);
   glutSwapBuffers();
   int i, j;
   for(i = 0; i < maxW/10; ++i)
   {
     for(j = 0; j < maxH/10; ++j)
     {
       if(grid[i][j] == 0)
       {
	 glColor3f(1.0, 1.0, 1.0);
       }
       else
       {
	 glColor3f(0.0, 0.0, 0.0);
       }
       int a, b;
       glBegin(GL_POINTS);
       for(a = i*10; a < i*10 + 10; ++a)
       {
	 for(b = j*10; b < j*10 + 10; ++b)
	 {
	   glVertex2f(a, b);
	 }
       }
       glEnd();
    }
  }
     glutSwapBuffers();
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
  //
  //SET UP GRID HERE!!!!
  //
  int i, j;
  for(i = 0; i < maxW/10; ++i)
    for(j = 0; j< maxH/10; ++j)
    {
    
	grid[i][j] = 0;
    }
    
   grid[3][5] = 1;
   grid[4][6] = 1;
   grid[5][5] = 1;
   grid[5][4] = 1;
   grid[5][6] = 1;
  
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // single buffering
   //
   glutInitWindowSize(400,300);
   glutInitWindowPosition(100,50);
   glutCreateWindow("Jake Shankman's Game of Life");
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
   //CALL IDLE FUNCTION!!!!!
   glutIdleFunc(idlefunc);
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
