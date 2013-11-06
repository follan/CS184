#include "GUI.h"
#include "Parser.h"
#include <cassert>
#include <iostream>
/*
GUI::~GUI(void)
{
}

void setup()
{
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//defines the position of the camera, where we are looking, and the up vector

	glEnable(GL_DEPTH_TEST);
}


void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the buffers

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(1.0f, 1.0f, 2.0f);

	//we just draw something to make sure the basics work
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.25f, 0.25f, -1.0f);
	glVertex3f(-0.25f, -0.25f, -1.0f);
	glVertex3f(0.25f, -0.25f, -1.0f);
	glVertex3f(0.25f, 0.25f, -1.0f);
	glEnd();

	glFlush(); //flush the buffer so things are actually drawn
	glutSwapBuffers();
}

void reshapeScene(int widht, int height)
{
	glViewport(0, 0, widht, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 0.0, 20.0); //defines the frustum by left, right, bottom, top, near and far

	glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 20.0);
}
*/

/*
int main(int argc ,char* argv[])
{
	//handle the given command line arguments
	assert(argc >= 3);
	string filename = argv[1];
	float stepsize = atof(argv[2]);
	string subdivision = "-u";

	if (argc == 4)
	{
		subdivision = argv[3];
	}

	//parse the input file
	Parser parser = Parser();
	parser.readFile(filename);

	//perform subdivision
	if (subdivision.compare("-a") == 0) //adaptive subdivision
	{
		parser.getPoints();
		cout << "adaptive" << endl;
	}

	else //uniform subdivision
	{
		cout << "uniform" << endl;
	}

	//OpenGL stuff
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