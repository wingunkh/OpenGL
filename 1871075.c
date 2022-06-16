#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <time.h>
#include <ctime>
#include <math.h>
#include <Windows.h>

int MX = 300;
int MY = 300;
float x = 0; //탱크의 x좌표
float y = 12; //탱크의 z좌표

bool catus_1 = true;
bool catus_2 = true;
bool catus_3 = true;
bool catus_4 = true; //bool 타입의 전역변수. 각각 4개의 선인장.

float timer = 0;
unsigned int seed = (unsigned int)time(NULL);

void Win() {
	if (catus_1 == false && catus_2 == false && catus_3 == false && catus_4 == false) {
		if (x <= -10 && y <= -10) {
			Sleep(500);
			exit(0);
		}
	}
} //모든 선인장이 파괴된 상태에서 탱크가 황금사과에 접근시 프로그램 종료.

void InitLight() {
	GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_shininess[] = { 15.0 };

	GLfloat light_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { -10, 5, 5, 0.0 };

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glEnable(GL_NORMALIZE); // 조명 계산할 때, 법선 벡터를 정확히 다시 계산
}

void MySpecial(int key, int X, int Y) { //x,y는 탱크의 현재 위치
	if (key == GLUT_KEY_UP) {
		if (y <= -15) y += 0.15f;
		y -= 0.15f;
	}
	if (key == GLUT_KEY_DOWN) {
		if (y >= 15) y -= 0.15f;
		y += 0.15f;
	}
	if (key == GLUT_KEY_LEFT) {
		if (x <= -15) x += 0.15f;
		x -= 0.15f;
	}
	if (key == GLUT_KEY_RIGHT) {
		if (x >= 15) x -= 0.15f;
		x += 0.15f;
	}
	glutPostRedisplay();
}


void MyTimer(int v) {
	timer += 4;
	Win();
	glutPostRedisplay();
	glutTimerFunc(10, MyTimer, 0);
}

void MyKeyboard(unsigned char KeyPressed, int X, int Y) { //a d w s로 카메라의 위치를 변경
	if (KeyPressed == 'a') {
		MX = MX - 10;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(MX / 300.0, MY / 300.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glutPostRedisplay();
	}
	if (KeyPressed == 'd') {
		MX = MX + 10;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(MX / 300.0, MY / 300.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glutPostRedisplay();
	}
	if (KeyPressed == 'w') {
		MY = MY + 10;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(MX / 300.0, MY / 300.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glutPostRedisplay();
	}
	if (KeyPressed == 's') {
		MY = MY - 10;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(MX / 300.0, MY / 300.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glutPostRedisplay();
	}
}

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15.0, 15.0, -15.0, 15.0, -100.0, 100.0); // 15가 좋은 view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 0.75, 1,
		0.0, 0.0, 0.0,
		0, 1, 0.0);  //시점변환
}

void DrawCatus() {
	srand(seed);
	int rand_x = 0;
	int rand_z = 0;

	glColor3f(0.0, 0.5, 0);

	glPushMatrix();
		rand_x = rand() % 15;
		rand_z = rand() % 15;
		glTranslatef(-rand_x, 0, -rand_z);
		glRotatef(270, 1, 0, 0);
		if (catus_1 == true) glutWireCone(2, 4, 10, 30); //선인장1

		if ((x >= (-rand_x - 2)) && (x <= (-rand_x + 2))) {
			if ((y >= (-rand_z - 2)) && (y <= (-rand_z + 2))) {
				catus_1 = false;
			}
		}
		//탱크의 좌표가 선인장 밑둥 좌표 범위 안에 들어오면, 전역변수의 값이 false로 바뀜.
		//전역변수의 값이 true가 아니면 선인장이 생성되지 않으므로 '탱크와 선인장이 충돌시 선인장이 사라지는 기능'을 수행.
	glPopMatrix();

	glPushMatrix();
		rand_x = rand() % 15;
		rand_z = rand() % 15;
		glTranslatef(+rand_x, 0, -rand_z);
		glRotatef(270, 1, 0, 0);
		if (catus_2 == true) glutWireCone(2, 4, 10, 30); //선인장2

		if ((x >= (+rand_x - 2)) && (x <= (+rand_x + 2))) {
			if ((y >= (-rand_z - 2)) && (y <= (-rand_z + 2))) {
				catus_2 = false;
			}
		}
	glPopMatrix();

	glPushMatrix();
		rand_x = rand() % 15;
		rand_z = rand() % 15;
		glTranslatef(-rand_x, 0, +rand_z);
		glRotatef(270, 1, 0, 0);
		if (catus_3 == true) glutWireCone(2, 4, 10, 30); //선인장3

		if ((x >= (-rand_x - 2)) && (x <= (-rand_x + 2))) {
			if ((y >= (+rand_z - 2)) && (y <= (+rand_z + 2))) {
				catus_3 = false;
			}
		}
	glPopMatrix();

	glPushMatrix();
		rand_x = rand() % 15;
		rand_z = rand() % 15;
		glTranslatef(+rand_x, 0, +rand_z);
		glRotatef(270, 1, 0, 0);
		if (catus_4 == true) glutWireCone(2, 4, 10, 30); //선인장4

		if ((x >= (+rand_x - 2)) && (x <= (+rand_x + 2))) {
			if ((y >= (+rand_z - 2)) && (y <= (+rand_z + 2))) {
				catus_4 = false;
			}
		}
	glPopMatrix();
}

void DrawTree() {
	glPushMatrix();
		glColor3f(0.6, 0.3, 0);
		glScalef(0.2, 1, 0.2);
		glutSolidCube(4); //나무 본체
		glScalef(5, 1, 5);

		glPushMatrix();
			glTranslatef(-0.75, 2.5, 0);
			glColor3f(0, 5, 0);
			glScalef(1, 0.5, 0.5);
			glutSolidCone(3, 3, 10, 10); //나무 이파리
		glPopMatrix();

		glPushMatrix();
			glColor3f(0.6, 0.3, 0);
			glTranslatef(0.25, 0, 0);
			glRotatef(sin(timer * 0.003) * 15 - 45, 0, 0, 1);
			glTranslatef(0, 1, 0);
			glScalef(0.1, 1, 0.1);
			glutSolidCube(3); //나뭇가지

			glPushMatrix();
				glScalef(10, 1, 10);
				glColor3f(1, 0.8, 0);
				glTranslatef(0.45, 0, 0);
				glTranslatef(0, 1.5, 0);
				glutSolidSphere(0.3, 20, 20); //나무 열매
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void DrawTank() {
	glPushMatrix();
		glColor3f(0.3, 0.3, 0.3);
		glTranslatef(0, 1.5, 0);
		glutSolidCube(1); //본체

		glPushMatrix();
			glTranslated(0, 0, -1);
			glScalef(0.3, 0.3, 2);
			glutSolidCube(1);
		glPopMatrix(); //포신

		glTranslatef(0.5, -0.75, 0);

		glPushMatrix();
			glScalef(0.3, 0.25, 1);
			glutSolidCube(2); //다리
			glTranslatef(0.75, -0.75, 0);

			glPushMatrix();
				glRotatef(timer, 0, 0, 1);
				glScalef(3, 4, 1);
				glutSolidSphere(0.3, 20, 20); //바퀴1
				glTranslatef(0, 0, -1);
				glutSolidSphere(0.3, 20, 20); //바퀴2
				glTranslatef(0, 0, 2);
				glutSolidSphere(0.3, 20, 20); //바퀴3
			glPopMatrix();
		glPopMatrix();

		glTranslatef(-1, 0, 0);

		glPushMatrix();
			glScalef(0.3, 0.25, 1);
			glutSolidCube(2); //다리

			glTranslatef(-0.75, -0.75, 0);

			glPushMatrix();
				glRotatef(timer, 0, 0, 1);
				glScalef(3, 4, 1);
				glutSolidSphere(0.3, 20, 20); //바퀴1
				glTranslatef(0, 0, -1);
				glutSolidSphere(0.3, 20, 20); //바퀴2
				glTranslatef(0, 0, 2);
				glutSolidSphere(0.3, 20, 20); //바퀴3
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		glColor3f(1, 1, 0.8);
		glScalef(30, 0.5, 30);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		DrawCatus();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-12, 1.5, -12);
		glScalef(0.7, 0.7, 0.7);
		DrawTree();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(x, 0, y); //키보드 조작
		glScalef(0.7, 0.7, 0.7);
		DrawTank();
	glPopMatrix();

	glFlush();
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitWindowSize(900, 900);
	glutCreateWindow("1871075 김현근");
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glClearColor(0.4, 0.4, 0.4, 1);
	InitLight();
	glutKeyboardFunc(MyKeyboard);
	glutTimerFunc(10, MyTimer, 0);
	glutSpecialFunc(MySpecial);
	glutMainLoop();
	return 0;
}