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

	polygon(4, 5, 6, 7); //파랑 밑면 J

	glPushMatrix();

	glTranslatef(0, 0, 0.01 * angle); //x로 1 이동, z로 -1 이동 
	polygon(0, 3, 2, 1);//뚜껑, 윗면 이동한 곳에 그리기. 

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, 0.0, -1.0); //x로 1 이동, z로 -1 이동 
	glRotatef(-angle, 0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(1.0, 0.0, 1.0);
	polygon(5, 4, 0, 1);//분홍
	glPopMatrix();
	glPopMatrix(); //기존 좌표계 

	glPushMatrix();
	glTranslatef(1.0, 0.0, -1.0); //x로 1 이동, z로 -1 이동 
	glRotatef(angle, 0.0, 1.0, 0.0); //도는건 x + 1 기준 
	glPushMatrix();
	glTranslatef(-1.0, 0.0, 1.0);
	polygon(2, 3, 7, 6); //노랑 //그리는 건 원래 자리에 
	glPopMatrix();
	glPopMatrix(); //기존 좌표계 

	glPushMatrix();
	glTranslatef(0.0, -1.0, -1.0); //x로 1 이동, z로 -1 이동 
	glRotatef(angle, 1.0, 0.0, 0.0); //도는건 x + 1 기준 
	glPushMatrix();
	glTranslatef(0.0, 1.0, 1.0); //x로 1 이동, z로 -1 이동 
	polygon(3, 0, 4, 7);//흰색 
	glPopMatrix();
	glPopMatrix(); //기존 좌표계 

	glPushMatrix();
	glTranslatef(0.0, 1.0, -1.0);
	glRotatef(-angle, 1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, -1.0, 1.0);
	polygon(1, 2, 6, 5); //초록
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
	//카메라의 위치(3,4,2)에서 보는것 월드좌표계

}

void axis(void) {

	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); // x축 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0); // y축 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);

	glColor3f(0.0, 0.0, 1.0); // z축 
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
	//up은 초기값이 1 
	//z축 중심으로 세워져 있다.
}



void init(void) {
	r = 5.0;
	theta = 0.5;
	phi = 0.6;
	delta_phi = 0.01;
	delta_theta = 0.01;
	//위값

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

	if (phi > 3.0 * PI / 2.0) //각도가 270도를 지나면 
		phi -= 2.0 * PI; // 다시 처음 자리로 
	else if (phi < -3.0 * PI / 2.0) //반대도 마찬가지 
		phi += 2.0 * PI;


	if (phi > PI / 2.0) //각도가 90도를 넘어가면 
		up = -1.0; //카메라의 상향벡터 방향이 -z 중심
	else if (phi < -1.0 * PI / 2.0) //각도가 -90도보다 작으면 
		up = -1.0; //카메라의 상향벡터 방향이 -z = 뒤집어짐.
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
