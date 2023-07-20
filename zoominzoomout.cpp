#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>

#define	width 			400 // w_wdith 
#define	height			600 // w_height 
#define	PI				3.1415
#define	polygon_num		10

//관심영역의 왼쪽하단
int left = -200;
int bottom =-300;

float zoom = 1;
float	radius = 20.0;

typedef struct _Point {
	float	x;
	float	y;
} Point;

Point	circle_center;

void Modeling_Axis(void) {
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(0, 0);
	glVertex2i(1.0 * width, 0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 1.0 * height);
	glEnd();
}

void	Modeling_Circle(Point CC) {
	float	delta;
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(3.0);
	delta = 2 * PI / polygon_num;
	glBegin(GL_POLYGON);
	for (int i = 0; i < polygon_num; i++)
		glVertex2f(CC.x + radius * cos(delta * i), CC.y + radius * sin(delta * i));
	glEnd();
}

void RenderScene(void) {
	glClearColor(1.0, 1.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(left , p_width, bottom, p_height);
	gluOrtho2D(left*zoom, (left + width)*zoom, bottom*zoom, (bottom + height)*zoom);
	Modeling_Axis();
	Modeling_Circle(circle_center);

	glFlush();
}


void mouseevent(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		zoom *= 0.9;
	};
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		zoom *= 1.1;
	}

	//width/2
	// height/2
	//(x,y)를 중앙으로 
	left = left + (x - width / 2) * zoom;
	bottom = bottom + -(y - height / 2) * zoom;
	//가상공간은 모니터와 y축이 반대 
	glutPostRedisplay();
}




void MySpecial(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:		left += 1.0; break;
	case GLUT_KEY_RIGHT:	left -= 1.0; break;
	case GLUT_KEY_DOWN:		bottom += 1.0; break;
	case GLUT_KEY_UP:		bottom -= 1.0; break;
	default:	break;
	}
	glutPostRedisplay();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Zoom in Zoom out");
	glutDisplayFunc(RenderScene);
	glutMouseFunc(mouseevent);
	glutSpecialFunc(MySpecial);
	glutMainLoop();
}
