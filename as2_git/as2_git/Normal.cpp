#include "Normal.h"


Normal::Normal(void)
{
}

Normal::Normal(float a_x, float a_y, float a_z)
{
	float length = sqrtf(a_x*a_x +a_y*a_y+a_z*a_z);
	//float length = 1;
	assert(length != 0);
	m_x = a_x/length;
	m_y = a_y/length;
	m_z = a_z/length;
}

Normal Normal::crossProduct(const Normal a_n1, const Normal a_n2)
{
	return Normal(
		a_n1.getY()*a_n2.getZ()-a_n1.getZ()*a_n2.getY(),
		-(a_n1.getX()*a_n2.getZ()-a_n1.getZ()*a_n2.getX()),
		a_n1.getX()*a_n2.getY()-a_n1.getY()*a_n2.getX());
}

string Normal::toString() const
{
	stringstream ss;
	ss<<"["<<m_x<<","<<m_y<<","<<m_z<<"]";
	return ss.str();
}


float Normal::getX() const
{
	return m_x;
}

float Normal::getY() const
{
	return m_y;
}

float Normal::getZ() const
{
	return m_z;
}


Normal::~Normal(void)
{
}
