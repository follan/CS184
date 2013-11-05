#pragma once
#include "Patch.h"
#include "Normal.h"
#define epsilon 0.001

class UniformSub
{
public:
	UniformSub(void);
	~UniformSub(void);
	void subDividePatch(const Patch& a_patch, const float& a_step) const;
	void bezPatchInterp(const Patch& a_patch, const float& a_u, const float& a_v, Point& a_p, Normal& a_n) const;
	void bezCurveInterp(const vector<Point>& a_curve, const float& a_u, Point& a_p, Normal a_dP) const;
};

