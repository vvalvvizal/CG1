#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>

#define PI 3.141592
double	radius = 0.5;

void draw_polygon(int n) {
	glColor3f(1.0, 1.0, 0.0);//����
	glBegin(GL_POLYGON);

	double theta = 2* PI / n;

	for (int i = 0; i < n; i++) {
		double x = radius * cos(theta*i);
		double y = radius * sin(theta*i);
		glVertex2f(x, y);
	}
	glEnd();

}

void draw_points(int n) {

	glColor3f(0.0, 0.0, 1.0);//����
	glPointSize(5);
	glBegin(GL_POINTS);

	double theta = 2 * PI / n;

	for (int i = 0; i < n; i++) {
		double x = radius * cos(theta * i);
		double y = radius * sin(theta * i);
		glVertex2f(x, y);
	}

	glEnd();
}


void RenderScene(void) {
	glClearColor(0.7, 0.7, 0.7, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	draw_polygon(17);//17����
	draw_points(17);//17�� ��
	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowPosition(50, 150);
	glutInitWindowSize(500, 500);
	glutCreateWindow("17-gon");
	glutDisplayFunc(RenderScene);
	glutMainLoop();
	return 0;
}