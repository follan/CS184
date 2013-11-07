#include "GUI.h"
#include "Parser.h"
#include "UniformSub.h"
#include <cassert>
#include <iostream>

GUI::GUI(void)
{

}

GUI::~GUI(void)
{
}
vector<Point> points;

bool keyStatus[256] = {false}; //used to store what keys are pressed

//the amount we rotate
int yAngle = 0;
int xAngle = 0;
int angleDelta = 5; //the amount we increase or decrease the rotation

 //-1 is false, 1 is true
int wireframeMode = -1;
int smoothShadingMode = 1;

int fieldOfView = 90;
int fovDelta = 5; //the amount we zoom

float aspectRatio = 1.0f;

//how much we move in the x and y direction
float moveX = 0.0f;
float moveY = 0.0f;
float moveDelta = 0.2f; //the amount we move

void performRotation()
{
	if (keyStatus[GLUT_KEY_LEFT])
	{
		yAngle += angleDelta;
	}
	else if (keyStatus[GLUT_KEY_RIGHT])
	{
		yAngle -= angleDelta;
	}
	else if (keyStatus[GLUT_KEY_DOWN])
	{
		xAngle += angleDelta;
	}
	else if (keyStatus[GLUT_KEY_UP])
	{
		xAngle -= angleDelta;
	}
}

void performTranslation()
{
	if (keyStatus[GLUT_KEY_LEFT])
	{
		moveX -= moveDelta;
	}
	else if (keyStatus[GLUT_KEY_RIGHT])
	{
		moveX += moveDelta;
	}
	else if (keyStatus[GLUT_KEY_DOWN])
	{
		moveY -= moveDelta;
	}
	else if (keyStatus[GLUT_KEY_UP])
	{
		moveY += moveDelta;
	}
}

/** Used to register which special keys are pressed. */
void keySpecialPressed(int key, int x, int y)
{
	//TODO: add support for what should happen when shift key is pressed

	keyStatus[key] = true;

	if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) //the shift key is pressed
	{
		performTranslation();
	}

	else
	{
		performRotation();
	}

	glutPostRedisplay();
}


/** Unregisters keys that are released */
void keySpecialUp(int key, int x, int y)
{
	keyStatus[key] = false;
}

void keyPressed(unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		wireframeMode *= -1;
	}
	else if (key == 's')
	{
		smoothShadingMode *= -1;
	}

	else if (key == '+') //we zoom in by decreasing the field of view
	{
		if (fieldOfView > fovDelta)
		{
			fieldOfView -= fovDelta;
		}
		//don't let field of view become 0
	}
	else if (key == '-') //we zoom out by increasing the field of view
	{
		if (fieldOfView != 180-fovDelta)
		{
			fieldOfView += fovDelta;
		}
		//don't let field of view become 180
	}

	glutPostRedisplay();
}


void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the buffers
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fieldOfView, aspectRatio, 1.0, 9.0);
	//defines the perspective by setting field of view, aspect ratio, near and far clipping plane 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//defines the position of the camera, where we are looking, and the up vector

	if (wireframeMode == 1)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (smoothShadingMode == 1)
	{
		glShadeModel(GL_SMOOTH);
	}
	else {
		glShadeModel(GL_FLAT);
	}
	
	//set up lighting
	GLfloat light0Position[] = {-1.0, 1.0, 0.0, 0.0}; //since the last element is 0 it's a directional light
	GLfloat light0Diffuse[] = {0.0, 0.0, 1.0, 1.0}; //the last element defines whether or not this light is on
	GLfloat light0Specular[] = {0.0, 0.0, 1.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	//set up material properties
	GLfloat materialDiffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat materialSpecular[] = {0.0, 0.0, 1.0, 1.0};
	GLfloat materialShine = 5.0;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, materialShine);
	glEnable(GL_COLOR_MATERIAL);
	

	glPushMatrix();
	glTranslatef(moveX, moveY, 0.0f); //translate the object
	glRotatef(yAngle, 0, 1, 0); //the amount we rotate around the z-axis
	glRotatef(xAngle, 1, 0, 0); //the amount we rotate around the x-axis

	//we just draw something to make sure the basics work
	//glBegin(GL_POLYGON);
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(-1.0f, 1.0f, 0.0f);
	//glVertex3f(-1.0f, -1.0f, 0.0f);
	//glVertex3f(1.0f, -1.0f, 0.0f);
	//glVertex3f(1.0f, 1.0f, 0.0f);
	//glEnd();

	//draw the input file
	for(unsigned int i =0; i<points.size(); i=i+4)
	{
		glBegin(GL_POLYGON);
		for(int j=0; j<4;j++)
		{
			Point p = points[i+j];
			float normalX = p.getNormal().getX();
			float normalY = p.getNormal().getY();
			float normalZ = p.getNormal().getZ();
			glNormal3f(normalX, normalY, normalZ);
			glVertex3f(p.getX(),p.getY(),p.getZ());
		}
		glEnd();
	}

	glPopMatrix();

	glFlush(); //flush the buffer so things are actually drawn
	glutSwapBuffers();
}

void reshapeScene(int width, int height)
{
	assert(height > 0);
	aspectRatio = (float) width / (float) height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fieldOfView, aspectRatio, 3.0, 7.0);
	//defines the perspective by setting field of view, aspect ratio, near and far clipping plane 

	glViewport(0, 0, width, height);
}


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
	vector<Point> temp = parser.getPoints();

	//perform subdivision
	if (subdivision.compare("-a") == 0) //adaptive subdivision
	{
		
	}

	else //uniform subdivision
	{
		for(int i=0; i<parser.getNumPatches();i++)
		{
			UniformSub::subDividePatch(Patch(temp),stepsize, points);
			temp.erase(temp.begin(), temp.size()>16 ? temp.begin() + 16: temp.end() );
		}
	}

	//OpenGL stuff
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Assignment3");
	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshapeScene);
	glutKeyboardFunc(keyPressed);
	glutSpecialFunc(keySpecialPressed);
	glutSpecialUpFunc(keySpecialUp);
	glutMainLoop();
}

