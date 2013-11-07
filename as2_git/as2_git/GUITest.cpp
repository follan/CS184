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
//int numDiv;
//
//void setup()
//{
//
//}
//
//
//void renderScene()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the buffers
//	glEnable(GL_DEPTH_TEST);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//	//defines the position of the camera, where we are looking, and the up vector
//
//
//	//glScalef(1.0f, 1.0f, 2.0f);
//	glColor3f(1.0f,0.0f,0.0f);
//	glPushMatrix();
//	glRotatef(-90,1,0,0);
//
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
//	glPopMatrix();
//
//	//we just draw something to make sure the basics work
//	/*glBegin(GL_POLYGON);
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glVertex3f(-0.25f, 0.25f, -1.0f);
//	glVertex3f(-0.25f, -0.25f, -1.0f);
//	glVertex3f(0.25f, -0.25f, -1.0f);
//	glVertex3f(0.25f, 0.25f, -1.0f);
//	glEnd();
//	*/
//	glFlush(); //flush the buffer so things are actually drawn
//	glutSwapBuffers();
//}
//
//void reshapeScene(int width, int height)
//{
//	assert(height > 0);
//	float aspectRatio = (float) width / (float) height;
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(90, aspectRatio, 3.0, 7.0);
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
//
//	//perform subdivision
//	if (subdivision.compare("-a") == 0) //adaptive subdivision
//	{
//		parser.getPoints();
//		cout << "adaptive" << endl;
//	}
//
//	else //uniform subdivision
//	{
//		vector<Point> temp = parser.getPoints();
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
//	setup();
//	glutDisplayFunc(renderScene);
//	glutReshapeFunc(reshapeScene);
//	glutMainLoop();
//}
