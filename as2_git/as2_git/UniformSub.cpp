#include "UniformSub.h"


UniformSub::UniformSub(void)
{
}


UniformSub::~UniformSub(void)
{
}

void UniformSub::subDividePatch(const Patch& a_patch,const float& a_step) const
{
	//compute how many subdivisions.
	float u, v;
	Point p;
	Normal n;
	int numDiv = (int)((1+epsilon)/a_step);
	for(int iu = 0; iu<numDiv; iu++)
	{
		u = iu*a_step;

		for(int iv=0; iv<numDiv; iv++)
		{
			v = iv * a_step;

			//evaluate surface
			bezPatchInterp(a_patch, u,v,p,n);
			//do something with the values p and n
		}

	}
}


void UniformSub::bezPatchInterp(const Patch& a_patch, const float& a_u, const float& a_v, Point& a_p, Normal& a_n) const
{
	vector<Point> vcurve(4);
	vector<Point> ucurve(4);
	Normal dummy;
	for(int i=0; i<4; i++)
	{
		bezCurveInterp(a_patch.getRow(i), a_u, vcurve[i],dummy);
		bezCurveInterp(a_patch.getCol(i), a_v, ucurve[i],dummy);
	}
	Normal dPdv;
	Normal dPdu;
	bezCurveInterp(vcurve,a_v, a_p, dPdv);
	bezCurveInterp(ucurve,a_u, a_p, dPdu);

	a_n = Normal::crossProduct(dPdu, dPdv);
	
}

void UniformSub::bezCurveInterp(const vector<Point>& a_curve, const float& a_u, Point& a_p, Normal a_dP) const
{
	Point A = a_curve[0] * (1.0f-a_u)+a_curve[1]*a_u;
	Point B = a_curve[1] * (1.0f-a_u)+a_curve[2]*a_u;
	Point C = a_curve[2] * (1.0f-a_u)+a_curve[3]*a_u;

	Point D = A*(1.0f-a_u)+B*a_u;
	Point E = B*(1.0f-a_u)+C*a_u;

	a_p = D*(1.0f-a_u)+E*a_u;

	//a_dP = 3*(E - D);	written out. dont know a better way right now
	a_dP = Normal(3*(E.getX()-D.getX()), 3*(E.getY()-D.getY()),3*(E.getZ()-D.getZ()));
}


