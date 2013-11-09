#pragma once
#include <sstream>
#include "Patch.h"
#include "Normal.h"
using namespace std;
class Patch;
class Point
{
public:
	Point(void);
	Point(float a_x, float a_y, float a_z);
	~Point(void);
	Point(float a_x, float a_y, float a_z, Normal& a_normal, Patch * a_patchPtr, const float& a_u, const float& a_v);
	Point(Point& a_point, Normal& a_normal,const Patch * a_patchPtr, const float& a_u, const float& a_v, const Normal& a_du, const Normal& a_dv);
	Point operator+(const Point a_p) const;
	Point operator*(const float a_c) const;
	Point operator-(const Point a_p) const;
	Point operator/(const float a_c) const;
	Normal getNormal() const;
	Normal getDv() const;
	Normal getDu() const;
	const Patch * getPatchPtr() const;
	
	float getLength() const;
	string toString() const;
	float getX() const;
	float getY() const;
	float getZ() const;
	float getU() const;
	float getV() const;
	bool hasNormal() const;

private:
	float m_x, m_y, m_z, m_u, m_v;
	Normal m_normal, m_du, m_dv;
	bool m_hasNormal;
	const Patch* m_patchPtr;
};



	