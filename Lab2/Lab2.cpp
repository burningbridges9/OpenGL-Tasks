// OpenGLTasks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "GL/glut.h"
#include <vector>
#include <math.h>
using namespace std;

GLint Width = 1024, Height = 1024;
GLubyte ColorR = 255, ColorG = 255, ColorB = 255;

struct type_point
{
	GLint x, y;
	type_point(GLint _x, GLint _y)
	{
		x = _x;
		y = _y;
	}

	type_point()
	{
		x = 0;
		y = 0;
	}
};

type_point center;
bool centerInit;
type_point radius_point;
bool radiusInit;
bool forActiveOnly;
struct pony_gone
{
	int n;
	int radius;
	type_point center_point;
	type_point radius_point;
	vector <type_point> points;
	pony_gone(type_point c, type_point r)
	{
		n = 6;
		center_point = type_point(c.x, c.y); // to do: override operator =
		radius_point = type_point(r.x, r.y);
		radius = sqrt(pow((c.x - r.x), 2) + pow((c.y - r.y), 2));



		for (int i = 0; i < n; i++)
		{
			auto angle = 2 * M_PI*i / n;
			auto x = radius * cos(angle) + c.x;
			auto y = radius * sin(angle) + c.y;
			points.push_back(type_point(x, y));
		}
	}

	pony_gone()
	{

	}
};


vector<pony_gone> polygons;

/* Функция вывода на экран */
void Display()
{
	glClearColor(0.5, 0.5, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(255, 255, 255);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(6);


	

	if (!polygons.empty())
	{
		for (size_t i = 0; i < polygons.size() - 1; i++)
		{
			glBegin(GL_POLYGON);
			for (int j = 0; j < polygons[i].points.size(); j++)
			{
				glVertex2i(polygons[i].points[j].x, polygons[i].points[j].y);
			}
			glEnd();
		}
		// active
		glColor3ub(ColorR, ColorG, ColorB);
		glBegin(GL_POLYGON);
		for (int j = 0; j < polygons.back().points.size(); j++)
		{
			glVertex2i(polygons.back().points[j].x, polygons.back().points[j].y);
		}
		glEnd();
	}

	glDisable(GL_COLOR_LOGIC_OP);
	glFinish();
}

/* Функция изменения размеров окна */
void Reshape(GLint w, GLint h)
{
	Width = w; Height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


bool ChangeColor(unsigned char key)
{
	if (key == 'r')
	{
		ColorR += 5;
		return true;
	}
	if (key == 'g')
	{
		ColorG += 5;
		return true;
	}
	if (key == 'b')
	{
		ColorB += 5;
		return true;
	}

	return false;
}
/* Функция обработки сообщений от клавиатуры */
void Keyboard(unsigned char key, int x, int y)
{
	if (ChangeColor(key))
	{
		forActiveOnly = true;
		glutPostRedisplay();
		return;
	}

	if (key == 't')
	{
		GLubyte data54[54];
		FILE *file = fopen("C:\\Users\\Rustam\\Documents\\Visual Studio 2017\\Projects\\OpenGLTasks\\Lab2\\Diamond plate4.bmp", "rb");
		fread(data54, 54, 1, file);
		int width = *(data54 + 18);
		int height = *(data54 + 22);
		GLubyte *pixels = new GLubyte[width * height * 3];
		fread(pixels, width * height * 3, 1, file);
		fclose(file);
		GLuint tex;
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height,
			GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_POLYGON);
		for (int j = 0; j < polygons.back().points.size(); j++)
		{
			glTexCoord2f(polygons.back().points[j].x, polygons.back().points[j].y);
			glVertex2i(polygons.back().points[j].x, polygons.back().points[j].y);
		}
		glEnd();
		glutPostRedisplay();
		return;
	}

	glMatrixMode(GL_MODELVIEW);

	switch (key)
	{
	case 'w':
		glTranslatef(0, 5, 0);
		break;
	case 's':
		glTranslatef(0, -5, 0);
		break;
	case 'a':
		glTranslatef(-5, 0, 0);
		break;
	case 'd':
		glTranslatef(5, 0, 0);
		break;
	case 'e':
		glRotatef(1, 0, 0, 1);
		break;
	case 'q':
		glRotatef(-1, 0, 0, 1);
		break;
	case '+':
		glScalef(0.5, 0.5, 0);
		break;
	case '-':
		glScalef(0.5, -0.5, 0);
		break;

	case 'o': // for OR logic
		glColor4d(1, 0, 0, 1);
		glEnable(GL_COLOR_LOGIC_OP);
		glLogicOp(GL_OR);
		glColor4d(0, 1, 0, 0.7);
		break;
	case 'n': // for NOR
		glColor4d(1, 0, 0, 1);
		glEnable(GL_COLOR_LOGIC_OP);
		glLogicOp(GL_NOR);
		glColor4d(0, 1, 0, 0.7);
		//glDisable(GL_COLOR_LOGIC_OP);
		break;
	}

	glutPostRedisplay();
}



/* Функция обработки сообщения от мыши */
void Mouse(int button, int state, int x, int y)
{
	/* клавиша была нажата, но не отпущена */
	if (state != GLUT_DOWN) return;
	/* новая точка по левому клику */
	if (button == GLUT_LEFT_BUTTON)
	{
		/*type_point p(x, Height - y);
		ActivePoints.push_back(p);*/

		if (!centerInit)
		{
			center = type_point(x, Height - y);
			centerInit = true;
		}
		else if (!radiusInit)
		{
			radius_point = type_point(x, Height - y);
			radiusInit = true;
			polygons.push_back(pony_gone(center, radius_point));
		}
	}
	if (radiusInit && centerInit)
	{
		glutPostRedisplay();
		centerInit = !centerInit;
		radiusInit = !radiusInit;
	}

}


void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Рисуем Polygon");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);

	glutMainLoop();
}