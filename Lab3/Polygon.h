#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "Point.h"
using namespace std;

class Polygon
{
public:
	int n;
	double radius;
	Point center_point;
	Point radius_point;
	vector<Point> points;
	Polygon(Point c, Point r)
	{
		n = 6;
		center_point = c;
		radius_point = r;
		radius = sqrt(pow((c.x - r.x), 2) + pow((c.y - r.y), 2));

		for (int i = 0; i < n; i++)
		{
			auto angle = 2 * M_PI*i / n;
			auto x = radius * cos(angle) + c.x;
			auto y = radius * sin(angle) + c.y;
			points.push_back(Point(x, y));
		}
	}

	Polygon()
	{

	}
};

