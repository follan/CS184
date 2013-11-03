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

Point::~Point(void)
{
}