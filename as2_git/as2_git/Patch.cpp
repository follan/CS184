#include "Patch.h"


Patch::Patch(void)
{
}

Patch::Patch(const vector<Point> a_points)
{
	assert(a_points.size() >= 16);
	m_points.resize(4);
	for(int i=0; i<4; i++)
	{
		m_points[i].resize(4);
		for(int j=0; j<4; j++)
		{
			m_points[i][j] = a_points[i*4+j];
		}
	}

}

vector<Point> Patch::getRow(int a_index) const
{
	return m_points[a_index];
}

vector<Point> Patch::getCol(int a_index) const
{
	vector<Point> retVec(4);
	for(int i=0; i<4; i++)
	{
		retVec[i] = m_points[i][a_index];
	}
	return retVec;
}

string Patch::toString() const
{
	stringstream ss;
	ss<<"[";
	for(int i=0; i<4; i++)
	{
		ss<<"[";
		for(int j=0; j<4; j++)
		{
			ss<<m_points[i][j].toString()<<" ";
		}
		ss<<"]\n";
	}

	ss<<"]";
	return ss.str();
}

vector<Point> Patch::getCorners() const
{
	vector<Point> retVec(4);
	retVec[0]=m_points[0][0];
	retVec[1]=m_points[0][3];
	retVec[1]=m_points[3][0];
	retVec[1]=m_points[3][3];
	return retVec;
}


Patch::~Patch(void)
{
}
