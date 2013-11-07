#pragma once
#include "Point.h"
#include <vector>
#include <tuple>
#include <cassert>
#include <sstream>
using namespace std;
class Point;
class Patch
{
public:
	Patch(void);
	Patch(vector<Point> a_points);
	vector<Point> getRow(const int a_index) const;
	vector<Point> getCol(const int a_index) const;
	string toString() const;
	vector<Point> getCorners() const;
	~Patch(void);
private:
	vector<vector<Point>> m_points;
};

