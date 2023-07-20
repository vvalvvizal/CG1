#include <gl/glut.h>
#include <gl/gl.h>
#include <stdio.h>
#include <math.h>

#define	PI	3.1415926

float r;
float phi;
float theta;
float delta_theta, delta_phi;
float	up = 1.0;
float angle = 0.0;

GLfloat		vertices[][3] = {
		{ -1.0, -1.0,  1.0 },		// 0 
		{ -1.0,  1.0,  1.0 },		// 1
		{ 1.0,  1.0,  1.0 },		// 2
		{ 1.0, -1.0,  1.0 },		// 3
		{ -1.0, -1.0, -1.0 },		// 4
		{ -1.0,  1.0, -1.0 },		// 5
		{ 1.0,  1.0, -1.0 },		// 6
		{ 1.0, -1.0, -1.0 } };		// 7

GLfloat		colors[][3] = {
		{ 1.0, 0.0, 0.0 },			// red
		{ 0.0, 1.0, 0.0 },			// green 
		{ 1.0, 1.0, 0.0 },			// yellow
		{ 1.0, 1.0, 1.0 },			// white
		{ 0.0, 0.0, 1.0 },			// blue
		{ 1.0, 0.0, 1.0 } };		// magenta



void polygon(int a, int b, int c, int d) {
	glColor3fv(colors[a]);
	glBegin(GL_POLYGON);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glEnd();
}


void cube(void) {

	polygon(4, 5, 6, 7); //�Ķ� �ظ� J

	glPushMatrix();

	glTranslatef(0, 0, 0.01 * angle); //x�� 1 �̵�, z�� -1 �̵� 
	polygon(0, 3, 2, 1);//�Ѳ�, ���� �̵��� ���� �׸���. 

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, 0.0, -1.0); //x�� 1 �̵�, z�� -1 �̵� 
	glRotatef(-angle, 0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(1.0, 0.0, 1.0);
	polygon(5, 4, 0, 1);//��ȫ
	glPopMatrix();
	glPopMatrix(); //���� ��ǥ�� 

	glPushMatrix();
	glTranslatef(1.0, 0.0, -1.0); //x�� 1 �̵�, z�� -1 �̵� 
	glRotatef(angle, 0.0, 1.0, 0.0); //���°� x + 1 ���� 
	glPushMatrix();
	glTranslatef(-1.0, 0.0, 1.0);
	polygon(2, 3, 7, 6); //��� //�׸��� �� ���� �ڸ��� 
	glPopMatrix();
	glPopMatrix(); //���� ��ǥ�� 

	glPushMatrix();
	glTranslatef(0.0, -1.0, -1.0); //x�� 1 �̵�, z�� -1 �̵� 
	glRotatef(angle, 1.0, 0.0, 0.0); //���°� x + 1 ���� 
	glPushMatrix();
	glTranslatef(0.0, 1.0, 1.0); //x�� 1 �̵�, z�� -1 �̵� 
	polygon(3, 0, 4, 7);//��� 
	glPopMatrix();
	glPopMatrix(); //���� ��ǥ�� 

	glPushMatrix();
	glTranslatef(0.0, 1.0, -1.0);
	glRotatef(-angle, 1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, -1.0, 1.0);
	polygon(1, 2, 6, 5); //�ʷ�
	glPopMatrix();
	glPopMatrix();

}


void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100.0, 1.0, 1.0, 20.0);
	//glOrtho(-5.0, 5.0, -5.0, 5.0, -10.0, 10.0);
	//ī�޶��� ��ġ(3,4,2)���� ���°� ������ǥ��

}

void axis(void) {

	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); // x�� 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0); // y�� 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);

	glColor3f(0.0, 0.0, 1.0); // z�� 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();
}


void frame_reset(void) {
	glClearColor(0.6, 0.6, 0.6, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void camera(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float x = r * cos(phi) * cos(theta);
	float y = r * cos(phi) * sin(theta);
	float  z = r * sin(phi);


	gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, up);
	//up�� �ʱⰪ�� 1 
	//z�� �߽����� ������ �ִ�.
}



void init(void) {
	r = 5.0;
	theta = 0.5;
	phi = 0.6;
	delta_phi = 0.01;
	delta_theta = 0.01;
	//����

	glEnable(GL_DEPTH_TEST);
}

void display(void)
{
	frame_reset();

	camera();
	axis();
	cube();

	glFlush();
	glutSwapBuffers();
}

void Mykey(unsigned char key, int x, int y) {
	switch (key)
	{

	case 't':
		angle += 90;
		break;
	case 'r':
		angle -= 90;
	default:
		break;
	}
	glutPostRedisplay();
}

void MySpecial(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		theta -= delta_theta; break;

	case GLUT_KEY_RIGHT:
		theta += delta_theta;	 break;

	case GLUT_KEY_DOWN:
		phi -= delta_phi; break;

	case GLUT_KEY_UP:
		phi += delta_phi; break;

	defalut: break;
	}

	if (phi > 3.0 * PI / 2.0) //������ 270���� ������ 
		phi -= 2.0 * PI; // �ٽ� ó�� �ڸ��� 
	else if (phi < -3.0 * PI / 2.0) //�ݴ뵵 �������� 
		phi += 2.0 * PI;


	if (phi > PI / 2.0) //������ 90���� �Ѿ�� 
		up = -1.0; //ī�޶��� ���⺤�� ������ -z �߽�
	else if (phi < -1.0 * PI / 2.0) //������ -90������ ������ 
		up = -1.0; //ī�޶��� ���⺤�� ������ -z = ��������.
	else
		up = 1.0;
	glutPostRedisplay();

}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("cube");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(MySpecial);
	glutKeyboardFunc(Mykey);
	glutMainLoop();
	glutSpecialFunc;
}
