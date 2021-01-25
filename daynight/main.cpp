#define _USE_MATH_DEFINES
#include <GL/freeglut.h>
#include <math.h>
GLfloat rotationAngle = 0.0f;
GLfloat xSun, ySun, xMoon, yMoon, alpha;

void init() {
	glClearColor(0.3, 0.35, 1.0, 1.0);
}

void drawHouse() {
	glColor3f(0.0f, 0.0f, 0.0f);
	glRectf(-0.25f, -1.0f, 0.25f, -0.55f);

	glBegin(GL_TRIANGLES);
	

	glVertex2f(-0.25f, -0.55f);
	glVertex2f(0.0f, -0.25f);
	glVertex2f(0.25f, -0.55f);

	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(-0.1f, -0.85f, 0.1f, -0.65f);
	
}

void drawSun(float radius, GLfloat xBegin, GLfloat yBegin) {
	glColor3ub(235, 213, 52);
	
	glBegin(GL_POLYGON);
	
	float Segments = 60.f;
	float x, y;
	for (float angle = 0.0f; angle <= (2.0f * M_PI); angle += (2.0f * M_PI / Segments)) {
		x = cos(angle)*radius + xBegin;
			y = sin(angle)*radius + yBegin;
			glVertex2f(x, y);
	}
	glEnd();
	
}

void drawMoon(float radius, GLfloat xBegin, GLfloat yBegin) {
	glColor3ub(196, 202, 207);

	glBegin(GL_POLYGON);

	float Segments = 60.f;
	float x, y;
	for (float angle = 0.0f; angle <= (2.0f * M_PI); angle += (2.0f * M_PI / Segments)) {
		x = cos(angle)*radius + xBegin;
		y = sin(angle)*radius + yBegin;
		glVertex2f(x, y);
	}
	glEnd();

}

void darken(GLfloat rectAlpha) {
	glColor4f(0.0f, 0.0f, 0.0f, rectAlpha);
	glRectf(-1.0f, -1.0f, 1.0f, 1.0f);
}

void timer(int t) {
	float Segments = 360.f;
	float sunRadius = 1.0f;
	float moonRadius = 1.0f;
	float x, y;
	
	if (rotationAngle >= 2.0f * M_PI) {
		rotationAngle = 0.0f;
	}
	else {
		rotationAngle += (2.0f * M_PI / Segments);
	}
		
	if (rotationAngle > M_PI && rotationAngle <= 3 * M_PI / 2) {
		alpha += 0.008;
	}
	if (rotationAngle >= 3 * M_PI / 2 && rotationAngle < 2 * M_PI) {
		alpha -= 0.008;
	}

	if (alpha > 0.7f) {
		alpha = 0.7f;
	}
	if (alpha < 0.0f) {
		alpha = 0.0f;
	}
	xSun = cos(rotationAngle)*sunRadius;
	ySun = sin(rotationAngle)*sunRadius - 0.95f;	
	xMoon = cos(rotationAngle - M_PI)*moonRadius;
	yMoon = sin(rotationAngle - M_PI)*moonRadius - 0.9f;
		

	glutPostRedisplay();
	glutTimerFunc(50, timer, 0);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	drawHouse();
	drawSun(0.2f, xSun, ySun);
	drawMoon(0.15f, xMoon, yMoon);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	darken(alpha);
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(500, 150);
	glutInitWindowSize(500, 500);
	glutCreateWindow("daynight");

	init();
	glutDisplayFunc(display);
	glutTimerFunc(50, timer, 0);
	

	glutMainLoop();

	return 0;
}
