#pragma once
#include <string>
#include <vector>
#include "Point.h"
using namespace std;

class Parser
{
public:
	Parser(void);
	~Parser(void);

	/** Reads from a file of type .bez and adds control points to a vector. */
	void readFile(string a_filename);
	vector<Point> getPoints() const;
	int getNumPatches() const;

private:
	vector<Point> m_points;
	int m_numPatches;

	/** Recognizes numbers in a string and adds them to a vector of flaots. */
	void splitString(string line, vector<float>& a_coordinates);

	/** Creates and adds control points to m_points. */
	void createPoints(const vector<float>& a_coordinates);
};
