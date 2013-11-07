#pragma once
#include "Patch.h"
#include "Normal.h"
#include <iostream>
#include "Parser.h"
#include <sstream>
#include "Triangle.h"
#include "UniformSub.h"
#include <queue>
using namespace std;
class AdaptiveSub
{
public:
	AdaptiveSub(void);
	~AdaptiveSub(void);
	static void subDividePatch(const Patch& a_patch, vector<Point>& a_drawPoints, const float& a_threshold);
private:
	static void midPointTestTriangle(const Triangle& a_triangle, const Patch& a_patch,queue<Triangle>& a_trianglesQueue, vector<Triangle>& a_correctTriengles, const float a_tau);
};

