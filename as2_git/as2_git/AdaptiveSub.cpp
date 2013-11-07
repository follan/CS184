#include "AdaptiveSub.h"


AdaptiveSub::AdaptiveSub(void)
{
}


AdaptiveSub::~AdaptiveSub(void)
{
}

void AdaptiveSub::subDividePatch(const Patch& a_patch, vector<Point>& a_drawPoints, const float& a_threshold)
{
	vector<Point> corners(4);
	//get the 4 corners of the patch, stored with correct u, v, normal and patchPtr
	//(const Patch& a_patch, const float& a_u, const float& a_v, Point& a_p)
	UniformSub::bezPatchInterp(a_patch,0.f,0.f,corners[0]);
	UniformSub::bezPatchInterp(a_patch,1.f,0.f,corners[1]);
	UniformSub::bezPatchInterp(a_patch,1.f,1.f,corners[2]);
	UniformSub::bezPatchInterp(a_patch,0.f,1.f,corners[3]);
	


	vector<Triangle> correctTriangles(0);
	queue<Triangle> triangleQueue;
	Triangle t1(corners[0], corners[1], corners[2]);
	Triangle t2(corners[3], corners[2], corners[0]);
	triangleQueue.push(t1);
	triangleQueue.push(t2);

	//do work here
	Triangle temp;
	while(!triangleQueue.empty())
	{
		temp = triangleQueue.front();
		triangleQueue.pop();
		midPointTestTriangle(temp, a_patch, triangleQueue, correctTriangles, a_threshold);
	}
	int oldSize = a_drawPoints.size();
	a_drawPoints.resize(oldSize + correctTriangles.size()*3);
	for(unsigned int i=0; i< correctTriangles.size(); i++)
	{
		a_drawPoints[oldSize+i*3] = correctTriangles[i].getP1();
		a_drawPoints[oldSize+i*3+1] = correctTriangles[i].getP2();
		a_drawPoints[oldSize+i*3+2] = correctTriangles[i].getP3();
	} 
}

void AdaptiveSub::midPointTestTriangle(const Triangle& a_triangle, const Patch& a_patch,queue<Triangle>& a_triangleQueue, vector<Triangle>& a_correctTriangles, const float a_tau)
{
	
	Point edgeMidPoint1;
	Point edgeMidPoint2;
	Point edgeMidPoint3;
	Point curveMidPoint1;
	Point curveMidPoint2;
	Point curveMidPoint3;
	float u;
	float v;
	bool e1=0;
	bool e2=0;
	bool e3=0;

	//edge 1:
	edgeMidPoint1 = (a_triangle.getP1()+a_triangle.getP2())/2.0f;
	u = (a_triangle.getP1().getU() + a_triangle.getP2().getU())/2.0f;
	v = (a_triangle.getP1().getV() + a_triangle.getP2().getV())/2.0f;
	UniformSub::bezPatchInterp(a_patch, u,v,curveMidPoint1);
	if((curveMidPoint1-edgeMidPoint1).getLength() >a_tau)
	{
		e1=1;
	}


	//edge 2:
	edgeMidPoint2 = (a_triangle.getP1()+a_triangle.getP3())/2.0f;
	u = (a_triangle.getP1().getU() + a_triangle.getP3().getU())/2.0f;
	v = (a_triangle.getP1().getV() + a_triangle.getP3().getV())/2.0f;
	UniformSub::bezPatchInterp(a_patch, u,v,curveMidPoint2);
	if((curveMidPoint2-edgeMidPoint2).getLength() >a_tau)
	{
		e2=1;
	}
	//edge 3:
	edgeMidPoint3 = (a_triangle.getP2()+a_triangle.getP3())/2.0f;
	u = (a_triangle.getP2().getU() + a_triangle.getP3().getU())/2.0f;
	v = (a_triangle.getP2().getV() + a_triangle.getP3().getV())/2.0f;
	UniformSub::bezPatchInterp(a_patch, u,v,curveMidPoint3);
	if((curveMidPoint3-edgeMidPoint3).getLength() >a_tau)
	{
		e3=1;
	}
	
	if(!e1 && !e2 && !e3)
	{
		a_correctTriangles.push_back(a_triangle);
	}
	else if(!e1 && !e2 && e3)
	{
		//curveMidPoint3 (between p2-p3)
		a_triangleQueue.push(Triangle(a_triangle.getP1(),a_triangle.getP2(),curveMidPoint3));
		a_triangleQueue.push(Triangle(curveMidPoint3, a_triangle.getP3(), a_triangle.getP1()));
	}
	else if(!e1 && e2 && !e3)
	{
		//curveMidPoint2 (between p1-p3)
		a_triangleQueue.push(Triangle(a_triangle.getP1(),a_triangle.getP2(),curveMidPoint2));
		a_triangleQueue.push(Triangle(curveMidPoint3, a_triangle.getP2(), a_triangle.getP3()));
	}
	else if(e1 && !e2 && !e3)
	{
		//curveMidPoint1 (between p1-p2)
		a_triangleQueue.push(Triangle(a_triangle.getP1(),curveMidPoint1,a_triangle.getP3()));
		a_triangleQueue.push(Triangle(curveMidPoint1, a_triangle.getP2(), a_triangle.getP3()));
	}
	else if(e1 && e2 && !e3)
	{
		//between p1-p2 and p1-p3
		a_triangleQueue.push(Triangle(a_triangle.getP1(),curveMidPoint1,curveMidPoint2));
		a_triangleQueue.push(Triangle(curveMidPoint1, a_triangle.getP2(), a_triangle.getP3()));
		a_triangleQueue.push(Triangle(curveMidPoint2, curveMidPoint1, a_triangle.getP3()));
	}
	else if(!e1 && e2 && e3)
	{
		//between p1-p3 and p2-p3
		a_triangleQueue.push(Triangle(a_triangle.getP1(),a_triangle.getP2(),curveMidPoint2));
		a_triangleQueue.push(Triangle(curveMidPoint2, a_triangle.getP2(), curveMidPoint3));
		a_triangleQueue.push(Triangle(curveMidPoint2, curveMidPoint3, a_triangle.getP3()));
	}
	else if(e1 && !e2 && e3)
	{
		//between p1-p2 and p2-p3
		a_triangleQueue.push(Triangle(a_triangle.getP1(),curveMidPoint1,curveMidPoint3));
		a_triangleQueue.push(Triangle(curveMidPoint1, a_triangle.getP2(), curveMidPoint3));
		a_triangleQueue.push(Triangle(a_triangle.getP1(), curveMidPoint3, a_triangle.getP3()));
	}
	else if(e1 && e2 && e3)
	{
		//between p1-p2, p1-p3 and p2-p3
		a_triangleQueue.push(Triangle(a_triangle.getP1(),curveMidPoint1,curveMidPoint2));
		a_triangleQueue.push(Triangle(curveMidPoint1, a_triangle.getP2(), curveMidPoint3));
		a_triangleQueue.push(Triangle(curveMidPoint2, curveMidPoint3, a_triangle.getP3()));
		a_triangleQueue.push(Triangle(curveMidPoint1, curveMidPoint2, curveMidPoint3));		
	}


}
