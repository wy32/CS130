// Name: 
// Quarter, Year: 
// Lab:
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#include <vector>
#include <cmath>
#include <GL/glut.h>
#include <unistd.h>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;


double p1x=0,p1y=0,p1z=0;
double rot_p1x=0,rot_p1y=0,rot_p1z=0,rot_ang_p1=45;

double p2x=0,p2y=0,p2z=0;
double rot_p2x=0,rot_p2y=0,rot_p2z=0,rot_ang_p2=45;

double p3x=0,p3y=0,p3z=0;
double rot_p3x=0,rot_p3y=0,rot_p3z=0,rot_ang_p3=45;

// Good indicators for debugging purposes
void GLdrawAxis()
{
    glDisable(GL_LIGHTING);
    glLineWidth(3.0);

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5); 
    glBegin(GL_LINES);

    // red positive x-axis
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1000.0, 0.0, 0.0);   

    // green positive y-axis
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1000.0, 0.0);

    // blue positive z-axis
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1000.0);
	
    glEnd(); 
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

// A simple wrapper for to store 3D vectors
struct Vector3
{
	float x;
	float y;
	float z;

	Vector3() : x(0.0), y(0.0), z(0.0)
	{}

	Vector3(float x, float y, float z)
		: x(x), y(y), z(z)
	{}

	Vector3(const Vector3 & v)
		: x(v.x), y(v.y), z(v.z)
	{}

	Vector3 operator+(const Vector3 & rhs) const
	{ return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
	Vector3 operator-(const Vector3 & rhs) const
	{ return Vector3(x - rhs.x, y + rhs.y, z - rhs.z); }
	Vector3 operator*(float rhs) const
	{ return Vector3(x * rhs, y * rhs, z * rhs); }
	Vector3 operator/(float rhs) const
	{ return Vector3(x / rhs, y / rhs, z / rhs); }
	Vector3 operator+=(const Vector3 & rhs)
	{ x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
	Vector3 operator-=(const Vector3 & rhs)
	{ x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
	Vector3 operator*=(float rhs)
	{ x *= rhs; y *= rhs; z *= rhs; return *this; }
	Vector3 operator/=(float rhs)
	{ x /= rhs; y /= rhs; z /= rhs; return *this; }

	float magnitude() const
	{ return sqrt(x * x + y * y + z * z); }
	void normalize()
	{ *this /= magnitude(); }
	float dot(const Vector3 & rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}
	Vector3 cross(const Vector3 & rhs) const
	{
		return Vector3(y * rhs.z - z * rhs.y,
					z * rhs.x - x * rhs.z,
					x * rhs.y - y * rhs.x);
	}
};

// A simple wrapper to store colors
struct Color
{
	float r;
	float g;
	float b;
	float a;

	Color() : r(0.0), g(0.0), b(0.0), a(1.0) {}
	Color(float r, float g, float b, float a = 1.0) 
		: r(r), g(g), b(b), a(a) 
	{}
};

// Number of milliseconds between frame updates
const int FRAME_PERIOD = 25;

// Used to appoximate the frame period length between updates
int currentTime = 0;
int previousTime = 0;

// Total time elapsed in the program
float elapsed = 0.0;

void setupScene()
{
	// *** Begin Setup Code ***

	// Set camera where 
	// the first 3 values: define camera position
	// second 3 values: define position to look at
	// third 3 values: define the up-vector for orientation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(100.0, 50.0, 100.0,
		      0.0, 0.0, 0.0,
			  0.0, 1.0, 0.0);

	// Overall ambience color values
	float ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	// Fourth parameter if 0.0: <x,y,z> stand for directional components
	// otherwise, it is <x,y,z> is positional
   float position[] = { 0.0, 15.0, 0.0, 1.0 };			

    // setup the light in the scene
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);	// Light decay rate
	
	// *** End Setup Code ***
}

void GLrender();
void GLupdate();

void GLinit(int argc, char** argv)
{
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Lab 3 - Insert Name Here");
	glutDisplayFunc(GLrender);
	glutIdleFunc(GLupdate);

	// Set the field of view
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(90.0, 
				static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT, 
				1.0, 
				1000.0);
	
	// Enable glColor to assign default ambient & diffuse material
	glEnable(GL_COLOR_MATERIAL);	
	// Enable depth tests for whether pixel is rendered
    glEnable(GL_DEPTH_TEST);		
	// Enable lighting
    glEnable(GL_LIGHTING);
	// Enable a single light source
	glEnable(GL_LIGHT0);
	// Enable auto-normalizing for objects to reflect light properly
    glEnable(GL_NORMALIZE);
	// Set conditions depth conditions for whether pixel is rendered
    glDepthFunc(GL_LEQUAL);
	// Smooth lighting across objects and conceal sharp poly edges
    glShadeModel(GL_SMOOTH);	

	setupScene();
}

int main(int argc, char** argv)
{
	GLinit(argc, argv);
	glutMainLoop();

	return 0;
}

void GLrender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	// *** Begin Draw Code ***
	
	GLdrawAxis();
	//glColor3f(1.0, 1.0, 0.0);
	//glutSolidSphere (50,50,50);
	
	//glTranslated(10,0,0);

	glPushMatrix();
        	glTranslatef(p1x,p1y,p1z);
        	glRotatef(rot_ang_p1, rot_p1x, rot_p1y, rot_p1z);
        	glColor3f(1.0, 1.0, 1.0);
		glutSolidSphere (10,10,10);
    	glPopMatrix();

	glPushMatrix();
		glTranslatef(p2x,p2y,p2z);
        	glRotatef(rot_ang_p2, rot_p2x, rot_p2y, rot_p2z);
        	glColor3f(1.0, 1.0, 0.0);
		glutSolidSphere (10,10,10);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(p3x,p3y,p3z);
        	glRotatef(rot_ang_p3, rot_p3x, rot_p3y, rot_p3z);
        	glColor3f(0.0, 1.0, 1.0);
		glutSolidSphere (10,10,10);
	glPopMatrix();

	// *** End Draw Code ***



	glFlush();	
	glutSwapBuffers();
}

void GLupdate()
{
	// Update time elapsed
	elapsed += (FRAME_PERIOD / 100.0);

	// *** Begin Animation Code ***
	p1x = 50*cos(rot_ang_p1);
	p1y = 50*sin(rot_ang_p1);

	p3x = p1x+20*cos(rot_ang_p1);
	p3y = p1y;
	p3z = p1z+20*sin(rot_ang_p1);

	if(rot_ang_p1 < 360)
		rot_ang_p1+=0.05;
	else
		rot_ang_p1=45; 
	

	// *** End Animation Code ***

	glutPostRedisplay();

	//sleep is not effective in capturing constant time between frames because sleep
	//doesn't consider the time it takes for context-switching. However, this reduces
	//the cpu-usage. If accurate time frames are desire, use a time accumulator
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	int diffTime = currentTime - previousTime;
	previousTime = currentTime;

	usleep(1000 * (FRAME_PERIOD - diffTime > 0 ? FRAME_PERIOD - diffTime : 0));
}
