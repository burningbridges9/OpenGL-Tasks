// OpenGLTasks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GL/glut.h"
#include <vector>
#include "OpenGLTasks.h"
using namespace std;

GLint Width = 512, Height = 512;
GLubyte ColorR = 255, ColorG = 255, ColorB = 255;
struct type_point
{
	GLint x, y;
	type_point(GLint _x, GLint _y)
	{
		x = _x;
		y = _y;
	}
};


vector<vector<type_point>> Points;

vector <type_point> ActivePoints;

/* Функция вывода на экран */
void Display(void)
{
	glClearColor(0.5, 0.5, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(ColorR, ColorG, ColorB);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(6);

	for (size_t j = 0; j < Points.size(); j++)
	{
		glBegin(GL_TRIANGLE_FAN);
		for (int i = 0; i < Points.at(j).size(); i++)
		{
			glVertex2i(Points[j].at(i).x, Points[j].at(i).y);
		}
		glEnd();
	}
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < ActivePoints.size(); i++)
	{
		glVertex2i(ActivePoints[i].x, ActivePoints[i].y);
	}
	glEnd();
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

/* Функция обработки сообщений от клавиатуры */
void Keyboard(unsigned char key, int x, int y)
{
	if (key == '\b')
	{
		DeleteLastPrimitive();
	}
	if (key == ' ')
	{
		EndCurrentPrimitive();
	}
	int i, n = ActivePoints.size();
	/* Изменение RGB-компонент цвета точек */
	ChangeColor(key);
	/* Изменение XY-кординат точек */
	if (key == 'w')
		for (i = 0; i < n; i++)
			ActivePoints[i].y += 9;
	if (key == 's')
		for (i = 0; i < n; i++)
			ActivePoints[i].y -= 9;
	if (key == 'a')
		for (i = 0; i < n; i++)
			ActivePoints[i].x -= 9;
	if (key == 'd')
		for (i = 0; i < n; i++)
			ActivePoints[i].x += 9;
	glutPostRedisplay();
}

void ChangeColor(unsigned char key)
{
	if (key == 'r')
		ColorR += 5;
	if (key == 'g')
		ColorG += 5;
	if (key == 'b')
		ColorB += 5;
}

void ChangeColor(int key)
{
	if (key == 2)
		ColorR += 5;
	if (key == 3)
		ColorG += 5;
	if (key == 4)
		ColorB += 5;
}

void ChangePos(int key)
{
	int i, n = ActivePoints.size();
	if (key == 5)
		for (i = 0; i < n; i++)
			ActivePoints[i].y += 9;
	if (key == 6)
		for (i = 0; i < n; i++)
			ActivePoints[i].y -= 9;
	if (key == 7)
		for (i = 0; i < n; i++)
			ActivePoints[i].x -= 9;
	if (key == 8)
		for (i = 0; i < n; i++)
			ActivePoints[i].x += 9;
}

void EndCurrentPrimitive()
{
	Points.push_back(ActivePoints);
	ActivePoints.clear();
}

void DeleteLastPrimitive()
{
	if (ActivePoints.size() != 0)
		ActivePoints.clear();
	else if (Points.size() != 0)
		Points.at(Points.size() - 1).clear();
}

/* Функция обработки сообщения от мыши */
void Mouse(int button, int state, int x, int y)
{
	/* клавиша была нажата, но не отпущена */
	if (state != GLUT_DOWN) return;
	/* новая точка по левому клику */
	if (button == GLUT_LEFT_BUTTON)
	{
		type_point p(x, Height - y);
		ActivePoints.push_back(p);
	}
	/* удаление последней точки по правому клику */
	if (button == GLUT_MIDDLE_BUTTON) ActivePoints.pop_back();
	glutPostRedisplay();
}

void menu(int num) {
	switch (num)
	{
	case 0:
		DeleteLastPrimitive();
		break;

	case 1:
		EndCurrentPrimitive();
		break;
	case 2:
	case 3:
	case 4:
		ChangeColor(num);
		break;

	case 5:
	case 6:
	case 7:
	case 8:
		ChangePos(num);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}
void createMenu(void) {
	int submenu_id = glutCreateMenu(menu);
	glutAddMenuEntry("удаление последнего примитива", 0);
	glutAddMenuEntry("начало нового примитива", 1);
	glutAddMenuEntry("ColorR += 5", 2);
	glutAddMenuEntry("ColorG += 5", 3);
	glutAddMenuEntry("ColorB += 5", 4);
	glutAddMenuEntry("Up", 5);
	glutAddMenuEntry("Down", 6);
	glutAddMenuEntry("Left", 7);
	glutAddMenuEntry("Right", 8);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Рисуем GL_TRIANGLE_FAN");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse); 
	createMenu();
	glutMainLoop();
}