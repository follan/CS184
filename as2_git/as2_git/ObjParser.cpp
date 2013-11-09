#include "ObjParser.h"
#include <iostream> //cout etc
#include <fstream> //ifstream
#include <sstream> //stingstream
#include <cctype> //isDigit


ObjParser::ObjParser(void)
{
}


ObjParser::~ObjParser(void)
{
}

vector<Polygon> ObjParser::getPolygons() const
{
	return m_polygons;
}
int counter =0;
void ObjParser::readFile(string a_filename)
{
	ifstream input;
	string line;
	input.open(a_filename);

	//loop through the input file and retrieve the coordinates of the control points
	while (getline(input, line))
	{
		parseLine(line);
	}
	
	input.close();
}

void ObjParser::parseLine(string line)
{
	stringstream ss(line);
	string point;
	char delimeter = ' ';
	vector<float> coordinates;
	getline(ss, point, delimeter);
	if(line[0] =='#' || line.compare("")==0)
	{
		return;
	}
	if(point.compare("v")==0)
	{
		counter++;
		while(getline(ss, point, delimeter))
		{
			if(point.compare("")==0)
			{
				continue;
			}
			coordinates.push_back(atof(point.c_str()));
		}
		m_vertices.push_back(Point(coordinates[0], coordinates[1], coordinates[2]));
	}
	else if(point.compare("vn") ==0)
	{
		
		while(getline(ss, point, delimeter))
		{
			if(point.compare("")==0)
			{
				continue;
			}
			coordinates.push_back(atof(point.c_str()));
		}
		m_normals.push_back(Normal(coordinates[0], coordinates[1], coordinates[2]));
	}
	else if(point.compare("f") ==0)
	{
		vector<int> vertexNumbers;
		vector<int> normalNumbers;
		stringstream ps(point);
		int numV =0;
		while(getline(ss, point, delimeter))
		{
			if(point.compare("")==0)
			{
				continue;
			}
			numV++;
			string vNumber = point.substr(0,point.find("//"));
			string nNumber = point.substr(point.find("//")+2,point.length());
			vertexNumbers.push_back(atoi(vNumber.c_str()));
			normalNumbers.push_back(atoi(nNumber.c_str()));
		}
		Polygon polygon(0);
		for(int i=0; i<numV; i++)
		{
			//m_points.push_back(Point(m_vertices[vertexNumbers[i]-1],m_normals[normalNumbers[i]-1],0,0,0));
			if(m_normals.size() !=0)
			{
				polygon.push_back(Point(m_vertices[vertexNumbers[i]-1],m_normals[normalNumbers[i]-1],0,0,0,Normal(),Normal()));
			}
			else
			{
				polygon.push_back(m_vertices[vertexNumbers[i]-1]);
			}
		}
		m_polygons.push_back(polygon);
	}

}



//void ObjParser::splitString(string line, vector<float>& a_coordinates)
//{
//	
//	stringstream stringStream(line);
//	string point;
//	char delimeter = ' ';
//	while(getline(stringStream, point, delimeter))
//	{
//		if (isdigit(point[0])|| point[0]=='-')
//		{
//			a_coordinates.push_back(atof(point.c_str()));
//		}
//	}
//}
//
//void ObjParser::createPoints(const vector<float>& a_coordinates)
//{
//	float x;
//	float y;
//	float z;
//	for (int i = 0; i < a_coordinates.size(); i = i + 3)
//	{
//		x = a_coordinates[i];
//		y = a_coordinates[i + 1];
//		z = a_coordinates[i + 2];
//		m_points.push_back(Point(x, y, z));
//	}
//
//
//}