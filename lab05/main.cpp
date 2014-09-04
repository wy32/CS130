// Name: 
// Quarter, Year: 
// Lab:
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glut.h>
#include "point3d.h"

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

int numOfFaces = 0;
int numOfVertex = 0;
int view = 0;
vector<Point3D> faces;
vector<Point3D> vertices;

void readFile()
{
	Point3D tempPt;
	ifstream iFile("./samplemeshes/samplecylinder.txt");
 	if (iFile.is_open()) {
		iFile >> numOfVertex;
		iFile >> numOfFaces;
		cout<<numOfVertex<<" , "<<numOfFaces<<endl;
		for(int i=0; i<numOfVertex; i++)
		{	
			iFile >> tempPt.x; 
			iFile >> tempPt.y;
			iFile >> tempPt.z;
			vertices.push_back(tempPt);
		}
		//Show contents of vertices
		for(int j=0; j<vertices.size(); j++)
		{
			tempPt = vertices[j];
			cout<<tempPt.x<<" , "<<tempPt.y<<" , "<<tempPt.z<<endl;
		}

		for(int i=0; i<numOfFaces; i++)
		{	
			iFile >> tempPt.x; 
			iFile >> tempPt.y;
			iFile >> tempPt.z;
			faces.push_back(tempPt);
		}
		//Show contents of faces
		for(int j=0; j<faces.size(); j++)
		{
			tempPt = faces[j];
			cout<<tempPt.x<<" , "<<tempPt.y<<" , "<<tempPt.z<<endl;
		}

		iFile.close();
	}
	else
		cout<<"Unable to Open File";
}

// Renders a quad at cell (x, y) with dimensions CELL_LENGTH
void renderPixel(int x, int y, float r = 1.0, float g = 1.0, float b = 1.0)
{
	glBegin(GL_POINTS);
	//glColor3f(0.0f,0.0f,1.0f); //blue color
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

void sideView()
{
	Point3D pt1,pt2,pt3;
	Point3D face;
	int fp1,fp2,fp3;
	for(int j=0; j<faces.size(); j++)
	{
		face = faces[j];
		pt1 = vertices[face.x];
		pt2 = vertices[face.y];
		pt3 = vertices[face.z];
		pt1*=8;
		pt2*=8;
		pt3*=8;
		ddaLine(pt1.z,pt1.y,pt2.z,pt2.y);
		ddaLine(pt2.z,pt2.y,pt3.z,pt3.y);
		ddaLine(pt3.z,pt3.y,pt1.z,pt1.y);
	}
}

void frontView()
{
	Point3D pt1,pt2,pt3;
	Point3D face;
	int fp1,fp2,fp3;
	for(int j=0; j<faces.size(); j++)
	{
		face = faces[j];
		pt1 = vertices[face.x];
		pt2 = vertices[face.y];
		pt3 = vertices[face.z];
		pt1*=8;
		pt2*=8;
		pt3*=8;
		ddaLine(pt1.x,pt1.y,pt2.x,pt2.y);
		ddaLine(pt2.x,pt2.y,pt3.x,pt3.y);
		ddaLine(pt3.x,pt3.y,pt1.x,pt1.y);
		//cout<<pt1.x<<" , "<<pt1.y<<" , "<<pt2.x<<" , "<<pt2.y<<endl;
	}
		//ddaLine(pt2.x,pt2.y,vertices[0].x,vertices[0].y);
}

void topView()
{
	Point3D pt1,pt2,pt3;
	Point3D face;
	int fp1,fp2,fp3;
	for(int j=0; j<faces.size(); j++)
	{
		face = faces[j];
		pt1 = vertices[face.x];
		pt2 = vertices[face.y];
		pt3 = vertices[face.z];
		pt1*=8;
		pt2*=8;
		pt3*=8;
		ddaLine(pt1.x,pt1.z,pt2.x,pt2.z);
		ddaLine(pt2.x,pt2.z,pt3.x,pt3.z);
		ddaLine(pt3.x,pt3.z,pt1.x,pt1.z);
	}
}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int x, int y) {

	switch(key) {
		case GLUT_KEY_UP :
				view=0;
				//topView();				
				break;
		case GLUT_KEY_DOWN :
				view=1;
				//frontView();
				break;
		case GLUT_KEY_RIGHT :
				view=2;
				//sideView();				
				break;
		case GLUT_KEY_LEFT :
				view=2;
				//sideView();				
				break;
	}
	glutPostRedisplay();
}

void GL_render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	switch(view)
	{
		case 0:
			topView();
			break;
		case 1:
			frontView();
			break;
		case 2:
			sideView();
			break;
		default:
			frontView();
			break;
	}	
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
	readFile();
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMainLoop();
	
	return 0;
}


