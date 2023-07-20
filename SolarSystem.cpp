#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)

#define		PI	3.1415926

int			Width = 800;
int			Height = 800;

float		sun_radius = 50.0; //태양 반지름
float		earth_radius = 30.0; //지구 반지름
float		moon_radius = 10.0; //달 반지룸


float      sun_distance = 300.0;//태양과 지구사이 거리
float      moon_distance = 70.0;//지구와 달사이 거리

float		earthRotation = 0.0, moonRotation = 0.0;

float		earth_rotation_speed = 0.1; //지구 공전속도
float		moon_rotation_speed = 0.2; //달 공전 속도 


void init(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0 * Width / 2.0, Width / 2.0, -1.0 * Height / 2.0, Height / 2.0);
}


void Draw_Circle(float c_radius) {
	float	delta;
	int		num = 36;

	delta = 2 * PI / num;
	glBegin(GL_POLYGON);
	for (int i = 0; i < num; i++)
		glVertex2f(c_radius * cos(delta * i), c_radius * sin(delta * i));
	glEnd();
}



void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0); // Set display-window color to black.

	earthRotation += earth_rotation_speed; //회전하는 각도 누적
	moonRotation += moon_rotation_speed;

	// 태양 : 빨간색의 구 
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0); //빨강
	Draw_Circle(sun_radius);
	glPopMatrix();

	// 지구 : 초록색의 구 
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0); //초록
	glRotatef(earthRotation, 0.0, 0.0, 1.0); //지구 회전 각도만큼 회전
	glTranslatef(sun_distance, 0.0, 0.0); //이동
	Draw_Circle(earth_radius);

	// 달   : 노랑색의 구 
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0); //노랑
	glRotatef(moonRotation, 0.0, 0.0, 1.0);//달 회전각도만큼 회전  
	glTranslatef(moon_distance, 0.0, 0.0);
	Draw_Circle(moon_radius);

	glPopMatrix();
	glPopMatrix();

	glFlush(); // 버퍼에 쌓인 코드들을 실행 
	glutSwapBuffers(); //버퍼를 바꿈
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Solar System 태양계");
	init();
	glutDisplayFunc(RenderScene);
	glutIdleFunc(RenderScene);
	glutMainLoop();
}

