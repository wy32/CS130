// Name: 
// Quarter, Year: 
// Lab:
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#include <GL/glut.h>
#include<iostream>
#include <math.h>
#include <vector>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

int clicks=0;
int ptx1,pty1;
int ptx2,pty2;
int ptx3,pty3;
int px,py;
std::vector<int> pts;

// Renders a quad at cell (x, y) with dimensions CELL_LENGTH
void renderPixel(int x, int y, float r = 1.0, float g = 1.0, float b = 1.0)
{
	glBegin(GL_POINTS);
	glVertex2i(x,y);
    	glEnd();
}

void ddaLine(int x1, int y1, int x2, int y2)
{
	float x,y,xInc,yInc,dx,dy;
	int next;
	
	dx = x2 - x1;
	dy = y2 - y1;
	
	if(abs(dx)>abs(dy))
		next=abs(dx);
	else
		next=abs(dy);

	xInc = dx / next;
	yInc = dy / next;
	
	x = x1;
	y = y1;
	
	renderPixel(x,y);

	for(int i=1;i<=next;i++)
	{
		x = x + xInc;
		y = y + yInc;
		renderPixel(x,y);
	}
}

void ddaCircle(int x0, int y0, int r)
{
	int x = r, y = 0;
	int radiusError = 1-x;

	while(x >= y)
	{
		renderPixel(x + x0, y + y0); 		//1st octant
		renderPixel(y + x0, x + y0);		//2nd octant
		renderPixel(-x + x0, y + y0);		//4th octant
		renderPixel(-y + x0, x + y0);		//3rd octant
		renderPixel(-x + x0, -y + y0);		//5th octant
		renderPixel(-y + x0, -x + y0);		//6th octant
		renderPixel(x + x0, -y + y0);		//8th octant
		renderPixel(y + x0, -x + y0); 		//7th octant           
		y++;

		if(radiusError<0)
			radiusError+=2*y+1;
		else
		{
			x--;
			radiusError+=2*(y-x+1);
		}
	}

}

int getPt( int n1 , int n2 , float perc )
{
    int diff = n2 - n1;

    return n1 + ( diff * perc );
}   

int drawBezier()
{
	int xa,ya,xb,yb,px,py;

	for( float i = 0 ; i < 1 ; i += 0.001 )
	{
	    xa = getPt( ptx1 , ptx2 , i );
	    ya = getPt( pty1 , pty2 , i );
	    xb = getPt( ptx2 , ptx3 , i );
	    yb = getPt( pty2 , pty3 , i );

	    px = getPt( xa , xb , i );
	    py = getPt( ya , yb , i );
		glutPostRedisplay();
	    renderPixel(px,py);
	}
}

void mouse(int btn, int state, int x, int y)
{
	switch (btn)
	{
    		case GLUT_LEFT_BUTTON:
		if(state == GLUT_DOWN)
		{
			if(clicks==0)
			{
				ptx1=x;
				pty1=800-y;
				clicks++;		
			}
			else if(clicks==1)
			{
				ptx2=x;
				pty2=800-y;
				clicks++;
				//glutPostRedisplay();
			}
			else if(clicks==2)
			{
				ptx3=x;
				pty3=800-y;
				//glutPostRedisplay();
				clicks=0;
			}
		}
		cout<<ptx1<<" "<<pty1<<" , "<<pty1<<" "<<pty2<<" , "<<ptx3<<" "<<pty3<<"+"<<clicks<<endl;
		break;
	}
	
}	



void GL_render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	ddaLine(ptx1,pty1,ptx2,pty2);
	ddaLine(ptx2,pty2,ptx3,pty3);
	drawBezier();		
	glutSwapBuffers();
}

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	// ...
	// Complete this function
	// ...

	glutCreateWindow("CS 130 - Willy Yong");
	
	// The default view coordinates is (-1.0, -1.0) bottom left & (1.0, 1.0) top right.
	// For the purposes of this lab, this is set to the number of pixels
	// in each dimension.
	glMatrixMode(GL_PROJECTION_MATRIX);
	glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
}

int main(int argc, char** argv)
{	
	GLInit(&argc, argv);
	glutMouseFunc(mouse);
	glutDisplayFunc(GL_render);
	glutMainLoop();
	
	return 0;
}

/*
public void Bezier(double[] b, int cpts, double[] p)
{
    int npts = (b.Length) / 2;
    int icount, jcount;
    double step, t;

    // Calculate points on curve

    icount = 0;
    t = 0;
    step = (double)1.0 / (cpts - 1);

    for (int i1 = 0; i1 != cpts; i1++)
    { 
        if ((1.0 - t) < 5e-6) 
            t = 1.0;

        jcount = 0;
        p[icount] = 0.0;
        p[icount + 1] = 0.0;
        for (int i = 0; i != npts; i++)
        {
            double basis = Bernstein(npts - 1, i, t);
            p[icount] += basis * b[jcount];
            p[icount + 1] += basis * b[jcount + 1];
            jcount = jcount +2;
        }

        icount += 2;
        t += step;
    }
}
*/

