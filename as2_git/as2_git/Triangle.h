#pragma once
#include "Point.h"
class Triangle
{
public:
	Triangle(void);
	Triangle(const Point& a_p1,const Point& a_p2,const Point& a_p3);
	~Triangle(void);
private:
	Point m_p1;
	Point m_p2;
	Point m_p3;
};

