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
#include "point2d.h"

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

int clicks=0;

Point2D pt1,pt2,pt3;

// Renders a quad at cell (x, y) with dimensions CELL_LENGTH
void renderPixel(int x, int y, float r = 1.0, float g = 1.0, float b = 1.0)
{
	glBegin(GL_POINTS);
	glVertex2i(x,y);
    	glEnd();
}

void ddaLine(Point2D pt1, Point2D pt2)
{
	float x,y,xInc,yInc,dx,dy;
	int next;
	
	dx = pt2.x - pt1.x;
	dy = pt2.y - pt1.y;
	
	if(abs(dx)>abs(dy))
		next=abs(dx);
	else
		next=abs(dy);

	xInc = dx / next;
	yInc = dy / next;
	
	x = pt1.x;
	y = pt1.y;
	
	renderPixel(x,y);

	for(int i=1;i<=next;i++)
	{
		x = x + xInc;
		y = y + yInc;
		renderPixel(x,y);
	}
}

void drawBezier()
{
	/*glBegin(GL_LINE_STRIP);

	for(int i=0;i!=LOD;++i) {

		// use the parametric time value 0 to 1
		float t = (float)i/(LOD-1);

		// nice to pre-calculate 1.0f-t because we will need it frequently
		float it = 1.0f-t;

		// calculate blending functions
		float b0 = t*t*t;
		float b1 = 3*t*t*it;
		float b2 = 3*t*it*it;
		float b3 =  it*it*it;

		// calculate the x,y and z of the curve point by summing
		// the Control vertices weighted by their respective blending
		// functions
		//
		float x = b0*Points[0][0] +
				  b1*Points[1][0] +
				  b2*Points[2][0] +
				  b3*Points[3][0] ;

		float y = b0*Points[0][1] +
				  b1*Points[1][1] +
				  b2*Points[2][1] +
				  b3*Points[3][1] ;

		float z = b0*Points[0][2] +
				  b1*Points[1][2] +
				  b2*Points[2][2] +
				  b3*Points[3][2] ;

		// specify the point
		glVertex3f( x,y,z );
	}
	glEnd();*/
}


Point2D computeBezierAt(double t)
{
	Point2D bezPt;
	Point2D p0,p1,p2,p3;

	double it = 1.0f-t;

	double b0 = it*it;
	double b1 = 2*it*t;	
	double b2 = t*t;

	p0 = pt1;
	p0 *= b0;
	p1 = pt2;
	p1 *= b1;
	p2 = pt3;
	p2 *=b2;

	bezPt = p0+p1+p2;	
	
	//cout<<bezPt.x<<" "<<bezPt.y<<endl;
	return bezPt;
	//c = pts.size();
}


double combination(double n,double r)
{
	if(r == 0)
		return 1;
	return ((n*combination(n-1,r-1))/r);
}
	

void renderBezier()
{
	Point2D bpt;
	for( float i = 0 ; i < 1 ; i += 0.001 )
	{
	    bpt = computeBezierAt(i);
		glutPostRedisplay();
	    renderPixel(bpt.x,bpt.y);
	}
	/*computeBezierAt(0.00);
				computeBezierAt(0.02);
				computeBezierAt(0.04);
				computeBezierAt(0.08);
				computeBezierAt(0.10);
				computeBezierAt(0.12);
				computeBezierAt(0.14);
				computeBezierAt(0.16);
				computeBezierAt(0.18);
				computeBezierAt(0.20);
				computeBezierAt(0.22);
				computeBezierAt(0.24);
				computeBezierAt(0.26);
				computeBezierAt(0.28);
				computeBezierAt(0.30);
				computeBezierAt(0.32);
				computeBezierAt(0.34);
				computeBezierAt(0.36);
				computeBezierAt(0.38);
				computeBezierAt(0.40);
				computeBezierAt(0.42);
				computeBezierAt(0.44);
				computeBezierAt(0.46);
				computeBezierAt(0.48);
				computeBezierAt(0.50);
				computeBezierAt(0.52);
				computeBezierAt(0.54);
				computeBezierAt(0.58);
				computeBezierAt(0.60);
				computeBezierAt(0.62);
				computeBezierAt(0.64);
				computeBezierAt(0.66);
				computeBezierAt(0.68);
				computeBezierAt(0.70);
				computeBezierAt(0.72);
				computeBezierAt(0.74);
				computeBezierAt(0.76);
				computeBezierAt(0.78);
				computeBezierAt(0.80);
				computeBezierAt(0.82);
				computeBezierAt(0.84);
				computeBezierAt(0.86);
				computeBezierAt(0.88);
				computeBezierAt(0.90);
				computeBezierAt(0.92);
				computeBezierAt(0.94);
				computeBezierAt(0.96);
				computeBezierAt(0.98);
				computeBezierAt(1.00);*/
}

void mouse(int btn, int state, int x, int y)
{
	Point2D tmp;
	switch (btn)
	{
    		case GLUT_LEFT_BUTTON:
		if(state == GLUT_DOWN)
		{
			if(clicks==0)
			{
				clicks++;
				tmp.x = x;
				tmp.y = 800-y;
				pt1=tmp;	
			}
			else if(clicks==1)
			{
				clicks++;
				tmp.x = x;
				tmp.y = 800-y;
				pt2=tmp;
			}
			else if(clicks==2)
			{
				clicks=0;
				tmp.x = x;
				tmp.y = 800-y;
				pt3=tmp;
				//glutPostRedisplay();
			}
		}
		break;
	}
	
	/*for(int i=0; i<pts.size(); i++)
	{
		cout<<pts[i].x<<" "<<pts[i].y<<" + "<<pts.size()<<endl;
	}*/
}

void GL_render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//Render control lines
	renderPixel(pt1.x,pt1.y);
	ddaLine(pt1,pt2);
	ddaLine(pt2,pt3);
	//Render Bezier points	
	renderBezier();	
	glutSwapBuffers();
}

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("CS 130 - Willy Yong");
	glMatrixMode(GL_PROJECTION_MATRIX);
	glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
}

int main(int argc, char** argv)
{	
	GLInit(&argc, argv);
	glutMouseFunc(mouse);
	glutDisplayFunc(GL_render);
	glutPostRedisplay();
	glutMainLoop();
	
	return 0;
}
