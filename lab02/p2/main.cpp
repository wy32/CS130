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

//int clicks=0;
//Point2D pt1,pt2,pt3;
vector<Point2D> ctrlPts;
vector<Point2D> pts;
int n=0;
int i=0;
double steps;


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

void computeBezierAt(float i)
{
	/*Point2D bezPt,pt;

	double it = 1.0f-t;

	double b0 = 0;
	double b1 = 0;
	double b2 = t*t;

	if(n>0)
	{	
		b0 = pow(it,n-i);
		b1 = pow(t,i);
	p0 = pt1;
	p0 *= b0;
	p1 = pt2;
	p1 *= b1;
	p2 = pt3;
	p2 *=b2;

	bezPt = p0+p1+p2;	
	}
	return bezPt;

	Point2D bpt;
	if(ctrlPts>2)
	{
		for( float i = 0 ; i < 1 ; i++)
		{
		    bpt = computeBezierAt(i);
			glutPostRedisplay();
		    renderPixel(bpt.x,bpt.y);
		}
	}

	Point2D pt1,pt2;
	
	if(ctrlPts.size()>0 && i==0)
		pt1 = ctrlPts[0];

	for(int j = 0; (unsigned int)j < ctrlPts.size(); j++)
        {
            bx2 += (int)(combination(ctrlPts.size(), j) * pow(1 - t, (float)ctrlPts.size() - j) * pow(t, j) * p[j].x);
            by2 += (int)(combination(ctrlPts.size(), j) * pow(1 - t, (float)ctrlPts.size() - j) * pow(t, j) * p[j].y);
        }

        ddaLine(pt1, pt2);*/
}


double combination(double n,double r)
{
	if(r == 0)
		return 1;
	return ((n*combination(n-1,r-1))/r);
}

unsigned int binomialCoef(unsigned int n, const unsigned int k)
{
    unsigned int r = 1;

    if(k > n)
        return 0;

    for(unsigned int d = 1; d <= k; d++)
    {
        r *= n--;
        r /= d;
    }

    return r;
}

/*
void nBezierCurve(Bitmap* obj, const Point* p, const unsigned int nbPoint)
{
	
    //int bx1 = ctrlPts[0].x;
    //int by1 = ctrlPts[0].y;
    //int bx2;
    //int by2;

    //steps = 1 / ctrlPts.size();

    for(float i = 0; i < 1; i += steps)
    {
        bx2 = by2 = 0;
        for(int j = 0; (unsigned int)j < ctrlPts.size(); j++)
        {
            bx2 += (int)(combination(ctrlPts.size(), j) * pow(1 - t, (float)ctrlPts.size() - j) * pow(t, j) * p[j].x);
            by2 += (int)(combination(ctrlPts.size(), j) * pow(1 - t, (float)ctrlPts.size() - j) * pow(t, j) * p[j].y);
        }

        ddaLine(pt1, pt2);

        bx1 = bx2;
        by1 = by2;
    }

    // curve must end on the last anchor point
    bresenhamLine(obj, bx1, by1, p[nbPoint - 1].x, p[nbPoint - 1].y, red, green, blue);
}	*/

void renderBezier()
{
	Point2D pt1,tmp,pt2;
	double b;
	double c;
	int bx2,by2;
	float steps=0;
	
	if(n>0)
	{
		//cout<<"enter bezier"<<endl;
		pt1 = ctrlPts[0];
		steps = 1.0/(float)n;
		pts.clear();
		for( float i = 0 ; i < 1 ; i+=0.01)
		{
			pt2.x=0;
			pt2.y=0;
			for(int j = 0; (unsigned int)j < n-1; j++)
        		{
				c = (int)combination(n,j);
				cout<<"combination: "<<c<<" ";
				b = ( c * pow(1 - i, (n - j)) * pow(i, j));
				cout<<"Binomial: "<<b<<" ";
				tmp = ctrlPts[j];
				cout<<"ctrlPt: "<<tmp.x<<","<<tmp.y<<" at "<<j<<" ";
				tmp *= b;
				cout<<"b*ctrlPt: "<<tmp.x<<","<<tmp.y<<" at "<<j<<endl;
				pt2 += tmp;	
        		}
			cout<<"pushing: "<<pt2.x<<","<<pt2.y<<endl;
			pts.push_back(pt2);
		}
		//pts.push_back(ctrlPts[n-1]);		
	}
}

void drawBezier()
{

	/*if(ctrlPts.size()>1)
	{
		for(int l=0; l<ctrlPts.size()-1; l++)
			ddaLine(ctrlPts[l],ctrlPts[l+1]);
			//renderPixel(pts[l].x,pts[l].y);
	}*/
	if(pts.size()>1)
	{
		for(int l=0; l<pts.size(); l++)
			cout<<pts[l].x<<","<<pts[l].y<<endl;
		for(int l=0; l<pts.size()-1; l++)
			ddaLine(pts[l],pts[l+1]);
			//renderPixel(pts[l].x,pts[l].y);
	}
}

void mouse(int btn, int state, int x, int y)
{
	Point2D tmp;
	switch (btn)
	{
    		case GLUT_LEFT_BUTTON:
		if(state == GLUT_DOWN)
		{
			tmp.x = x;
			tmp.y = 800-y;
			ctrlPts.push_back(tmp);
			n=ctrlPts.size();
			i=n-1;
			cout<<n<<endl;
			renderBezier();
			glutPostRedisplay();
		}
		break;
	}
}

void GL_render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//Render control lines
	if(n==1)
		renderPixel(ctrlPts[0].x,ctrlPts[0].y);
	/*if(n>1)
	{
		for(int k=0; k<n-1; k++)
			renderPixel(ctrlPts[k].x,ctrlPts[k].y);
	}*/
	//Render Bezier points	
	//renderBezier();	
	drawBezier();
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
