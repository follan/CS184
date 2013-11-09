#include "Point.h"


Point::Point(void)
{
}

Point::Point(float a_x, float a_y, float a_z)
{
	m_x = a_x;
	m_y = a_y;
	m_z = a_z;
	m_normal = Normal();
	m_patchPtr =0;
	m_v=0;
	m_u=0;
	m_hasNormal=false;
}

Point::Point(Point& a_point, Normal& a_normal,const Patch* a_patchPtr, const float& a_u, const float& a_v,const Normal& a_du, const Normal& a_dv)
{
	m_x=a_point.getX();
	m_y=a_point.getY();
	m_z=a_point.getZ();
	m_normal = a_normal;
	m_patchPtr = a_patchPtr;
	m_u=a_u;
	m_v=a_v;
	m_du = a_du;
	m_dv=a_dv;
	m_hasNormal = true;
}


Point::Point(float a_x, float a_y, float a_z, Normal& a_normal, Patch* a_patchPtr, const float& a_u, const float& a_v)
{
	m_x = a_x;
	m_y = a_y;
	m_z = a_z;
	m_normal = a_normal;
	m_patchPtr = a_patchPtr;
	m_u=a_u;
	m_v=a_v;
	m_hasNormal = true;

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

Normal Point::getNormal() const
{
	return m_normal;
}

bool Point::hasNormal() const
{
	return m_hasNormal;
}


float Point::getU() const
{
	return m_u;
}

float Point::getV() const
{
	return m_v;
}

Normal Point::getDu() const
{
	return m_du;
}

Normal Point::getDv() const
{
	return m_dv;
}


const Patch* Point::getPatchPtr() const
{
	return m_patchPtr;
}


string Point::toString() const
{
	stringstream ss;
	ss<<"["<<m_x<<","<<m_y<<","<<m_z<<"]";
	return ss.str();
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

Point Point::operator/(const float a_c) const
{
	assert(a_c != 0);
	return Point(m_x/a_c, m_y/a_c, m_z/a_c);
}

float Point::getLength() const
{
	return sqrt(m_x*m_x+m_y*m_y + m_z*m_z);
}


Point::~Point(void)
{
}