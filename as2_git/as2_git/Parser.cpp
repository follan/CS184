#include "Parser.h"
#include <iostream> //cout etc
#include <fstream> //ifstream
#include <sstream> //stingstream
#include <cctype> //isDigit


Parser::Parser(void)
{
}


Parser::~Parser(void)
{
}
vector<Point> Parser::getPoints() const
{
	return m_points;
}

int Parser::getNumPatches() const
{
	return m_numPatches;
}


void Parser::readFile(string a_filename)
{
	ifstream input;
	string line;
	vector<float> coordinates;
	input.open(a_filename);
	getline(input, line); //hack to ignore first line
	m_numPatches = atoi(line.c_str);
	//loop through the input file and retrieve the coordinates of the control points
	while (getline(input, line))
	{
		splitString(line, coordinates);
	}
	createPoints(coordinates);
	input.close();
}

void Parser::splitString(string line, vector<float>& a_coordinates)
{
	stringstream stringStream(line);
	string point;
	char delimeter = ' ';
	while(getline(stringStream, point, delimeter))
	{
		if (isdigit(point[0]))
		{
			a_coordinates.push_back(atof(point.c_str()));
		}
	}
}

void Parser::createPoints(const vector<float>& a_coordinates)
{
	float x;
	float y;
	float z;
	for (int i = 0; i < a_coordinates.size(); i = i + 3)
	{
		x = a_coordinates[i];
		y = a_coordinates[i + 1];
		z = a_coordinates[i + 2];
		m_points.push_back(Point(x, y, z));
	}


}
