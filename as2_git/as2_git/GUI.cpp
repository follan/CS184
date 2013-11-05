#include "GUI.h"

GUI::~GUI(void)
{
}

void setup()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the buffers

	glMatrixMode(GL_PROJECTION);
}


void customDisplayFunc()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//we just draw something to make sure the basics work
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-1.0f, 1.0f);
	glVertex2f(-1.0f, -1.0f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(1.0f, 1.0f);
	glEnd();

	glFlush(); //flush the buffer so things are actually drawn
}


int main(int argc ,char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Assignment3");
	glutDisplayFunc(customDisplayFunc);
	//glutReshapeFunc(myReshape);
	glutMainLoop();
}