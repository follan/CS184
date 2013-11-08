#include "GUITest.h"
#include "Parser.h"
#include "ObjParser.h"
#include <cassert>
#include <iostream>
#include "UniformSub.h"
#include "AdaptiveSub.h"

GUITest::GUITest(void)
{
}


GUITest::~GUITest(void)
{
}
vector<Point> points;
vector<Polygon> polygons;
bool isAdaptive = false;
bool isObj = false;

bool keyStatus[256] = {false}; //used to store what keys are pressed

//the amount we rotate
int yAngle = 0;
int xAngle = 0;
int angleDelta = 5; //the amount we increase or decrease the rotation

 //-1 is false, 1 is true
int wireframeMode = -1;
int smoothShadingMode = 1;
int curvatureShadinMode = -1;

int fieldOfView = 90;
int fovDelta = 5; //the amount we zoom

float aspectRatio = 1.0f;

//how much we move in the x and y direction
float moveX = 0.0f;
float moveY = 0.0f;
float moveDelta = 0.2f; //the amount we move

/** Used to register which special keys are pressed. */
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
	else if(key == 'c')//curvature shading
	{
		curvatureShadinMode *= -1;
	}


	glutPostRedisplay();
}
void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the buffers
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fieldOfView, aspectRatio, 1.0, 10.0);
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
	glTranslatef(moveX, moveY, 0.0f); //don't do anything at the moment
	glRotatef(yAngle, 0, 1, 0); //the amount we rotate around the z-axis
	glRotatef(xAngle, 1, 0, 0); //the amount we rotate around the x-axis


	//glScalef(1.0f, 1.0f, 2.0f);
	if(isObj)
	{
		glColor3f(1.0f,0.0f,0.0f);
		for(int i=0; i<polygons.size();i++)
		{
			glBegin(GL_POLYGON);
			for(int j=0; j<polygons[i].size(); j++)
			{
				Point p = polygons[i][j];
				float normalX = p.getNormal().getX();
				float normalY = p.getNormal().getY();
				float normalZ = p.getNormal().getZ();
				glNormal3f(normalX, normalY, normalZ);
				glVertex3f(p.getX(),p.getY(),p.getZ());
			}
			glEnd();
		}

	}
	else
	{
		int numVert = isAdaptive? 3:4;
		if(curvatureShadinMode == 1)
		{
			glDisable(GL_LIGHTING);
			for(unsigned int i=0; i<points.size(); i=i+numVert)
			{
				glBegin(GL_POLYGON);
				for(int j=0; j<numVert;j++)
				{
					Point p = points[i+j];
					Normal dPdu = p.getDu();
					Normal dPdv = p.getDv();
					Point dpdu(dPdu.getX(), dPdu.getY(), dPdu.getZ());
					Point dpdv(dPdv.getX(), dPdv.getY(), dPdv.getZ());
					Point x(1.0f,0.0f,0.0f);
					Point y(0.0f,1.0f,0.0f);
					float red = x.getX()*dPdu.getX();
					float blue =y.getY()*dPdv.getY();
					//float red = dPdu.getX()*dPdv.getX() + dPdu.getY()*dPdv.getY() + dPdu.getZ()*dPdv.getZ();
					glColor3f(fabsf(blue), 0.0f,fabsf(red));
					glVertex3f(p.getX(), p.getY(),p.getZ());
				}
				glEnd();
			}

		}
		else
		{
			for(unsigned int i =0; i<points.size(); i=i+numVert)
			{
				glColor3f(1.0f,1.0f,1.0f);
				glBegin(GL_POLYGON);
				for(int j=0; j<numVert;j++)
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
		}
	}
	

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
	isObj = filename.substr(filename.length()-4,4).compare(".obj") ==0;
	if(isObj)
	{
		ObjParser objparser = ObjParser();
		objparser.readFile(filename);
		polygons = objparser.getPolygons();
	}
	
	else
	{

		float stepsize = atof(argv[2]);
		float threshold = atof(argv[2]);
		string subdivision = "-u";

		if (argc == 4)
		{
			subdivision = argv[3];
		}
		isAdaptive = (subdivision.compare("-a") == 0);
		//parse the input file
		Parser parser = Parser();
		parser.readFile(filename);
		vector<Point> temp = parser.getPoints();
		//perform subdivision
		if (isAdaptive) //adaptive subdivision
		{
			for(int i=0; i<parser.getNumPatches();i++)
			{
				AdaptiveSub::subDividePatch(Patch(temp),points, threshold);
				temp.erase(temp.begin(), temp.size()>16 ? temp.begin() + 16: temp.end() );
			}

		
			cout << "adaptive" << endl;
		}

		else //uniform subdivision
		{
			//cout<<temp.capacity()<<endl;
			for(int i=0; i<parser.getNumPatches();i++)
			{
				UniformSub::subDividePatch(Patch(temp),stepsize, points);
				temp.erase(temp.begin(), temp.size()>16 ? temp.begin() + 16: temp.end() );
			}
	//		v.erase( v.begin(), v.size() > N ?  v.begin() + N : v.end() );

		
			cout << "uniform" << endl;
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
