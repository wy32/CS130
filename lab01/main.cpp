// Name: 
// Quarter, Year: 
// Lab:
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#include <GL/glut.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

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

void GL_render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	renderPixel(400,400);
	ddaLine(200,300,235,400);
	ddaLine(400,500,500,600);
	ddaLine(300,100,600,110);
	ddaCircle(400,400,300);
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
	glutDisplayFunc(GL_render);
	// The default view coordinates is (-1.0, -1.0) bottom left & (1.0, 1.0) top right.
	// For the purposes of this lab, this is set to the number of pixels
	// in each dimension.
	glMatrixMode(GL_PROJECTION_MATRIX);
	glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
}

int main(int argc, char** argv)
{	
	GLInit(&argc, argv);
	glutMainLoop();
	
	return 0;
}


