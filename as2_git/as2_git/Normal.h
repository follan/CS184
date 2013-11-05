#pragma once
#include <cmath>
#include <cassert>
#include <sstream>
#include <iostream>
using namespace std;
class Normal
{
public:
	Normal(void);
	~Normal(void);
	Normal(float a_x, float a_y, float a_z);

	static Normal crossProduct(const Normal a_n1, const Normal a_n2);
	float getX() const;
	float getY() const;
	float getZ() const;
	string toString() const;
private:
	float m_x;
	float m_y;
	float m_z;
};

