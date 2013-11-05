#include "Point.h"


Point::Point(void)
{
}

Point::Point(float a_x, float a_y, float a_z)
{
	m_x = a_x;
	m_y = a_y;
	m_z = a_z;
}

float Point::getX() const
{
	return m_x;
}

float Point::getY() const
{
	return m_y;
}

float Point::getZ() const
{
	return m_z;
}

Point Point::operator+(const Point a_p)const
{
	return Point(m_x+a_p.getX(), m_y+a_p.getY(), m_z+a_p.getZ());
}

Point Point::operator-(const Point a_p) const
{
	return Point(m_x-a_p.getX(), m_y-a_p.getY(), m_z-a_p.getZ());
}


Point Point::operator*(const float a_c) const
{
	return Point(m_x*a_c, m_y*a_c, m_z*a_c);
}



Point::~Point(void)
{
}