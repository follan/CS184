#pragma once
#include "Patch.h"
#include "Normal.h"
#include <iostream>
#include "Parser.h"
#include <sstream>
#define epsilon 0.001

class UniformSub
{
public:
	UniformSub(void);
	~UniformSub(void);
	static void subDividePatch(const Patch& a_patch, const float& a_step, vector<Point>& a_drawPoints);
	static string toString(const vector<vector<Point>> a_points);
private:
	static void bezPatchInterp(const Patch& a_patch, const float& a_u, const float& a_v, Point& a_p);
	static void bezCurveInterp(const vector<Point>& a_curve, const float& a_u, Point& a_p, Normal& a_dP);
};

