#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)

#define		PI				3.1415926

int	Window_Width = 500;
int	Window_Height = 500;
//������ ���� �ʺ� ���� (���->����)
int			model_type = GL_POLYGON;
int			num = 10;
float		radius = 100; //�ʱ� ������ 100 
float		start_angle = 0.0;
float newx, newy = 0; //clipping ���� ��ȭ��Ű�� ���� ����, ���ҽ�ų ��

void MyReshape(int w, int h) {
	glViewport(0, 0, w, h);
	Window_Width = w;
	Window_Height = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-w / 2.0, w / 2.0, -h / 2.0, h / 2.0); //���ɿ���
}

void Modeling_Circle(void) {
	float	delta, theta;
	float	x, y;

	glColor3f(1.0, 1.0, 0.0);
	glPointSize(3.0);
	delta = 2 * PI / num;

	glBegin(model_type);
	for (int i = 0; i < num; i++) {
		theta = start_angle + delta * i;
		x = radius * cos(theta);
		y = radius * sin(theta);
		glVertex2f(x, y);
	}
	glEnd();
}

void Modeling_Axis(void) {
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-250.0, 0.0);
	glVertex2f(250.0, 0.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0, -250.0);
	glVertex2f(0, 250.0);
	glEnd();
}

void Modeling_Rectangle(void) {
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2i(100, 100);
	glVertex2i(150, 100);
	glVertex2i(150, 150);
	glVertex2i(100, 150);
	glEnd();
}

void Modeling_Ground(void) {
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2i(250, 250);
	glVertex2i(-250, 250);
	glVertex2i(-250, -250);
	glVertex2i(250, -250);
	glEnd();
}

void RenderScene(void) {
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0 + newx, 0 + newy, Window_Width, Window_Height);

	Modeling_Rectangle();	// 1��и鿡 �ִ� ���簢�� 
	Modeling_Axis();		// x��� y�� 
	Modeling_Circle();		// �������� ũ�Ⱑ 100�� ��

	glFlush();
}


void MyKey(unsigned char key, int x, int y) {

	switch (key) {
	case 'n': //���� �����ϴ� ���� ����
		num += 1;
		break;
	case 'm': //���� �����ϴ� ���� ���� 
		num -= 1;
		break;
	case 'h':  //���� ũ�� ����
		radius += 50;
		break;
	case 'l': //���� ũ�� ����
		radius -= 50;
		break;

	default:	break;
	}
	glutPostRedisplay();
}

void SpecialKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_F1:	model_type = GL_POINTS;		break; //������ ����
	case GLUT_KEY_F2:	model_type = GL_POLYGON;	break; //��
	case GLUT_KEY_F3:	model_type = GL_LINE_LOOP; break; //���η���
	case GLUT_KEY_F4:	model_type = GL_LINES; break; //������ ���� 


	case GLUT_KEY_UP: newy += 10; break;
	case GLUT_KEY_DOWN: newy -= 10; break;
	case GLUT_KEY_RIGHT:  newx += 10; break;
	case GLUT_KEY_LEFT: newx -= 10; break;

	default:	break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Window_Width, Window_Height);
	glutCreateWindow("Keyboard_event & SpecialKey_event");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKey);
	glutSpecialFunc(SpecialKey);
	glutMainLoop();
	return 0;
}