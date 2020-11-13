#include <GL/glut.h> 

GLfloat xRotated, yRotated, zRotated;


void redisplayFunc(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
	glColor3f(1, 1, 1.0);
	glRotatef(xRotated, 1.0, 0.0, 0.0);
	glRotatef(yRotated, 0.0, 1.0, 0.0);
	glRotatef(zRotated, 0.0, 0.0, 1.0);
	glScalef(1.0, 1.0, 1.0);
	glutSolidSphere(1.0, 30, 30);
	glFlush();
	glutSwapBuffers();
}

void reshapeFunc(int x, int y)
{
	if (y == 0 || x == 0) return;
	//Set a new projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);  //Use the whole window for rendering
}

void idleFunc(void)
{
	//xRotated += 0.03;
	//yRotated += 0.03;
	zRotated += 0.01;
	redisplayFunc();
}


int main(int argc, char **argv)
{
	xRotated = 100;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(350, 350);
	glutCreateWindow("solid sphere animation");
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	yRotated = zRotated = 0.0;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutDisplayFunc(redisplayFunc);
	glutReshapeFunc(reshapeFunc);
	glutIdleFunc(idleFunc);
	glutMainLoop();
	return 0;
}