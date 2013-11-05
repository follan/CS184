#include "GUI.h"

GUI::~GUI(void)
{
}

void setup()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 0.0, -1.0); //defines the frustum by left, right, bottom, top, near and far
}


void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the buffers

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//we just draw something to make sure the basics work
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();

	glFlush(); //flush the buffer so things are actually drawn
	glutSwapBuffers();
}

void reshapeScene(int widht, int height)
{
	//do something when the window is resized
}


/*
int main(int argc ,char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Assignment3");
	setup();
	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshapeScene);
	glutMainLoop();
}
*/