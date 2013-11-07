#pragma once
#include "Patch.h"
#include "Normal.h"
#include <iostream>
#include "Parser.h"
#include <sstream>
class AdaptiveSub
{
public:
	AdaptiveSub(void);
	~AdaptiveSub(void);
	static void subDividePatch(const Patch& a_patch, vector<Point> a_drawPoints);
};

