//#include "GUITest.h"
//#include "Parser.h"
//#include <cassert>
//#include <iostream>
//#include "UniformSub.h"
//
//GUITest::GUITest(void)
//{
//}
//
//
//GUITest::~GUITest(void)
//{
//}
//vector<Point> points;
//
//bool keyStatus[256] = {false};
//
////the amount we rotate
//int yAngle = 0;
//int xAngle = 0;
//int angleDelta = 5; //the amount we increase or decrease the rotation
//
//int wireframeMode = -1; //-1 is false, 1 is true
//
//int fieldOfView = 90;
//int fovDelta = 5; //the amount we zoom
//
//float aspectRatio = 1.0f;
//
///** Used to register which special keys are pressed. */
//void keySpecialPressed(int key, int x, int y)
//{
//	//TODO: add support for what should happen when shift key is pressed
//
//	keyStatus[key] = true;
//
//	if (keyStatus[GLUT_KEY_LEFT])
//	{
//		yAngle += angleDelta;
//	}
//	else if (keyStatus[GLUT_KEY_RIGHT])
//	{
//		yAngle -= angleDelta;
//	}
//	else if (keyStatus[GLUT_KEY_DOWN])
//	{
//		xAngle += angleDelta;
//	}
//	else if (keyStatus[GLUT_KEY_UP])
//	{
//		xAngle -= angleDelta;
//	}
//
//	glutPostRedisplay();
//}
//
///** Unregisters keys that are released */
//void keySpecialUp(int key, int x, int y)
//{
//	keyStatus[key] = false;
//}
//
//
//void keyPressed(unsigned char key, int x, int y)
//{
//	if (key == 'w')
//	{
//		wireframeMode *= -1;
//	}
//	else if (key == '+') //we zoom in by decreasing the field of view
//	{
//		if (fieldOfView > fovDelta)
//		{
//			fieldOfView -= fovDelta;
//		}
//		//don't let field of view become 0
//	}
//	else if (key == '-') //we zoom out by increasing the field of view
//	{
//		if (fieldOfView != 180-fovDelta)
//		{
//			fieldOfView += fovDelta;
//		}
//		//don't let field of view become 180
//	}
//
//	glutPostRedisplay();
//}
//
//void renderScene()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the buffers
//	glEnable(GL_DEPTH_TEST);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(fieldOfView, aspectRatio, 1.0, 10.0);
//	//defines the perspective by setting field of view, aspect ratio, near and far clipping plane 
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//	//defines the position of the camera, where we are looking, and the up vector
//
//	if (wireframeMode == 1)
//	{
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	}
//	else
//	{
//		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//	}
//
//
//	glPushMatrix();
//	glTranslatef(0.0f, 0.0f, 0.0f); //don't do anything at the moment
//	glRotatef(yAngle, 0, 1, 0); //the amount we rotate around the z-axis
//	glRotatef(xAngle, 1, 0, 0); //the amount we rotate around the x-axis
//
//
//	//glScalef(1.0f, 1.0f, 2.0f);
//	glColor3f(1.0f,0.0f,0.0f);
//	for(unsigned int i =0; i<points.size(); i=i+4)
//	{
//		//if(i==324) 
//		//{glColor3f(0.0f,1.0f,0.0f);}
//		glBegin(GL_POLYGON);
//		for(int j=0; j<4;j++)
//		{
//			glVertex3f(points[i+j].getX(),points[i+j].getY(),points[i+j].getZ());
//		}
//		glEnd();
//	}
//
//	glFlush(); //flush the buffer so things are actually drawn
//	glutSwapBuffers();
//}
//
//void reshapeScene(int width, int height)
//{
//	assert(height > 0);
//	aspectRatio = (float) width / (float) height;
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(fieldOfView, aspectRatio, 3.0, 7.0);
//	//defines the perspective by setting field of view, aspect ratio, near and far clipping plane 
//
//	glViewport(0, 0, width, height);
//}
//
//
//
//int main(int argc ,char* argv[])
//{
//	//handle the given command line arguments
//	assert(argc >= 3);
//	string filename = argv[1];
//	float stepsize = atof(argv[2]);
//	string subdivision = "-u";
//
//	if (argc == 4)
//	{
//		subdivision = argv[3];
//	}
//
//	//parse the input file
//	Parser parser = Parser();
//	parser.readFile(filename);
//	vector<Point> temp = parser.getPoints();
//	//perform subdivision
//	if (subdivision.compare("-a") == 0) //adaptive subdivision
//	{
//		points = Patch(temp).getCorners();
//		cout << "adaptive" << endl;
//	}
//
//	else //uniform subdivision
//	{
//		//cout<<temp.capacity()<<endl;
//		for(int i=0; i<parser.getNumPatches();i++)
//		{
//			UniformSub::subDividePatch(Patch(temp),stepsize, points);
//			temp.erase(temp.begin(), temp.size()>16 ? temp.begin() + 16: temp.end() );
//		}
////		v.erase( v.begin(), v.size() > N ?  v.begin() + N : v.end() );
//
//		
//		cout << "uniform" << endl;
//	}
//
//
//	//OpenGL stuff
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowSize(400, 400);
//	glutInitWindowPosition(0, 0);
//	glutCreateWindow("Assignment3");
//	glutDisplayFunc(renderScene);
//	glutReshapeFunc(reshapeScene);
//	glutKeyboardFunc(keyPressed);
//	glutSpecialFunc(keySpecialPressed);
//	glutSpecialUpFunc(keySpecialUp);
//	glutMainLoop();
//}
