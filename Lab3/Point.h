#pragma once
#include "GL/glut.h"
class Point
{
public:
	GLfloat x, y;
	Point(GLfloat _x, GLfloat _y)
	{
		x = _x;
		y = _y;
	}

	Point()
	{
		x = 0;
		y = 0;
	}
	
	Point operator=(const Point &p)
	{
		x = p.x; 
		y = p.y;

		return *this;
	}
};

