#include "Triangle.h"


Triangle::Triangle(void)
{
}

Triangle::Triangle(const Point& a_p1,const Point& a_p2,const Point& a_p3)
{
	m_p1=a_p1;
	m_p2=a_p2;
	m_p3=a_p3;
}


Point Triangle::getP1() const
{
	return m_p1;
}

Point Triangle::getP2() const
{
	return m_p2;
}

Point Triangle::getP3() const
{
	return m_p3;
}


Triangle::~Triangle(void)
{
}
