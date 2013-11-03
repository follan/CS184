#pragma once
class Point
{
public:
	Point(void);
	Point(float a_x, float a_y, float a_z);
	~Point(void);

	float getX() const;
	float getY() const;
	float getZ() const;

private:
	float m_x, m_y, m_z;
};

