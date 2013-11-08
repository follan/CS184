#pragma once
#include <string>
#include <vector>
#include "Point.h"
using namespace std;

typedef  vector<Point> Polygon;
class ObjParser
{
public:
	ObjParser(void);
	~ObjParser(void);

	/** Reads from a file of type .bez and adds control points to a vector. */
	void readFile(string a_filename);
	vector<Polygon> getPolygons() const;
	/** Recognizes numbers in a string and adds them to a vector of flaots. */
	
private:
	vector<Polygon> m_polygons;
	vector<Point> m_vertices;
	vector<Normal> m_normals;
	void splitString(string line, vector<float>& a_coordinates);
	/** Creates and adds control points to m_points. */
	void createPoints(const vector<float>& a_coordinates);
	void parseLine(string line);
};

