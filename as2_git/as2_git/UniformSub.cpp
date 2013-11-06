#include "UniformSub.h"


UniformSub::UniformSub(void)
{
}


UniformSub::~UniformSub(void)
{
}

void UniformSub::subDividePatch(const Patch& a_patch,const float& a_step, vector<Point>& a_returnVec)
{
	
	
	//compute how many subdivisions.
	float u, v;
	Point p;
	Normal n;
	int numDiv = (int)((1+epsilon)/a_step);
	vector<vector<Point>> newPoints(numDiv);
	for(int iu = 0; iu<numDiv; iu++)
	{
		u = iu*a_step;

		for(int iv=0; iv<numDiv; iv++)
		{
			v = iv * a_step;

			//evaluate surface
			bezPatchInterp(a_patch, u,v,p,n);
			//do something with the values p and n
			//not using n for anything, omitting for now
			newPoints[iu].push_back(p);
		}

	}
	cout<<toString(newPoints)<<endl;
	//trying to make a vector where 4 and 4 points make a square, counter clockwise
	a_returnVec.resize((numDiv-1)*(numDiv-1)*4);
	for(int i=0; i<numDiv-1; i++)
	{
		for(int j=0; j<numDiv-1;j++)
		{
			a_returnVec[i*(numDiv-1)*4+j*4] = newPoints[i][j];
			a_returnVec[i*(numDiv-1)*4+j*4+1] = newPoints[i][j+1];
			a_returnVec[i*(numDiv-1)*4+j*4+2] = newPoints[i+1][j+1];
			a_returnVec[i*(numDiv-1)*4+j*4+3] = newPoints[i+1][j];
		}

	}


}


void UniformSub::bezPatchInterp(const Patch& a_patch, const float& a_u, const float& a_v, Point& a_p, Normal& a_n)
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

	//a_n = Normal::crossProduct(dPdu, dPdv);
	
}

void UniformSub::bezCurveInterp(const vector<Point>& a_curve, const float& a_u, Point& a_p, Normal a_dP)
{
	Point A = a_curve[0] * (1.0f-a_u)+a_curve[1]*a_u;
	Point B = a_curve[1] * (1.0f-a_u)+a_curve[2]*a_u;
	Point C = a_curve[2] * (1.0f-a_u)+a_curve[3]*a_u;

	Point D = A*(1.0f-a_u)+B*a_u;
	Point E = B*(1.0f-a_u)+C*a_u;

	a_p = D*(1.0f-a_u)+E*a_u;

	//a_dP = 3*(E - D);	written out. dont know a better way right now
	//a_dP = Normal(3*(E.getX()-D.getX()), 3*(E.getY()-D.getY()),3*(E.getZ()-D.getZ()));
}

string UniformSub::toString(const vector<vector<Point>> a_points)
{
	stringstream ss;
	ss<<"[";
	for(int i=0; i<a_points.size(); i++)
	{
		ss<<"[";
		for(int j=0; j<a_points[0].size(); j++)
		{
			ss<<a_points[i][j].toString()<<" ";
		}
		ss<<"]\n";
	}

	ss<<"]";
	return ss.str();
}

/*
int main(int argc, char* argv[])
{
	Point p(1,3,4);
	cout<<p.toString()<<endl;
	Parser parser = Parser();
	parser.readFile("test.bez");
	vector<Point> points = parser.getPoints();
	Patch patch(points);
	vector<Point> retPoints;
	UniformSub::subDividePatch(patch,0.1f,retPoints);  
	//cout<<patch.toString()<<endl;
}

*/