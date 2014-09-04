// Name: 
// Quarter, Year: 
// Lab:
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <complex>
#include "color.h"

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

const int MAX_ITERS=100;

// Renders a quad at cell (x, y) with dimensions CELL_LENGTH
void renderPixel(float x, float y, float r = 1.0, float g = 1.0, float b = 1.0)
{
	glBegin(GL_POINTS);
	//glColor3f(0.0f,0.0f,1.0f); //blue color
	glVertex2f(x,y);
    	glEnd();
}

void renderJuliaSet(double xmin, double xmax, double ymin, double ymax)
{
	

	double dx=(xmax-xmin)/WINDOW_WIDTH;
	double dy=(ymax-ymin)/WINDOW_HEIGHT;
	double X=0;
	double Y=0;
	complex<double> val(-0.7796,0.134);

	for(double xi=xmin; xi<xmax; xi+=dx)
	{
		for(double yi=ymin; yi<ymax; yi+=dy)
		{
			int iters=0;
			complex<double> x(xi,yi);
			while(abs(x) < 2.0 && iters < MAX_ITERS)
			{
				x = (pow(x,2)+val);
				++iters;
			}
			Color3d c(0.0,1.0,1.0);
			c.rotateHue(((120)/MAX_ITERS)*iters);
			glColor3f(c.r,c.g,c.b);
			//cout<<x.real()<<","<<x.imag()<<endl;
cout<<iters<<endl;
			renderPixel(X,Y);
			Y++;		
		}
		X++;
		Y=0;
	}	
} 

void GL_render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	renderJuliaSet(-2.0,2.0,-2.0,2.0);
	glutSwapBuffers();
}

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("CS 130 - Willy Yong");
	glutDisplayFunc(GL_render);
	glMatrixMode(GL_PROJECTION_MATRIX);
	glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
}

int main(int argc, char** argv)
{	
	GLInit(&argc, argv);
	glutMainLoop();
	
	return 0;
}


