#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

#define BODY_WIDTH 3
#define PIECE_LENGTH 0.6
#define HEAD_SIZE 3.5

#define RUN  1
#define SPIN 2

GLboolean jointSPIN = GL_FALSE;
GLfloat jointANGLE[2] = { 0.0, 0.0 };
GLint BIG_LEG_MOVE_DIRECTION = 1;
GLint LITTLE_LEG_MOVE_DIRECTION = 1;

GLboolean Rotate = GL_FALSE;

GLfloat theta[3] = { 0.0, 0.0, 0.0 };
GLint axis = 1;

GLUquadricObj *p;   // pointer to quadric object


GLboolean vertical = GL_FALSE;
GLboolean level = GL_FALSE;
GLfloat currentLocation[2] = { 2.0, 2.0 };
GLfloat targetLocation[2] = { 4.0, 4.0 };
GLfloat RUN_STEP = 0.005;
GLint WHICH_PATH = 1;

GLfloat piece[15] = { 0.52 ,0.7 ,0.8 , 0.9, 1.0,
1.0 ,1.0, 1.0 ,1.0, 1.0 ,
1.0, 1.0 , 0.9 , 0.85 , 0.75 };

void base() {
	glPushMatrix();
	glColor3f(1.0, 0.75, 0.8);
	for (int i = 0; i <= 15; i++) {
		glTranslatef(0.0, 0.0, -PIECE_LENGTH);
		gluCylinder(p, BODY_WIDTH*piece[i + 1], BODY_WIDTH*piece[i], PIECE_LENGTH, 15, 15);
	}
	glPopMatrix();
}


void ear() {
	GLfloat EAR_SIZE = 2;

	//glPushMatrix();
	glScalef(EAR_SIZE, EAR_SIZE, 0.3);
	glColor3f(1.0, 0.75, 0.8);
	glutSolidCube(1.0);
	//glPopMatrix();
}

void head() {

	glPushMatrix();
	glTranslatef(0.0, 0.0, 1.5);
	glRotatef(-10, 1.0, 0.0, 0.0);
	glColor3f(1.0, 0.7, 0.7);
	glutSolidCube(HEAD_SIZE);


	GLfloat EYE_SIZE = 0.3;					//start to draw eyes
	glTranslatef(-HEAD_SIZE / 4, HEAD_SIZE / 4, HEAD_SIZE / 2);
	glColor3f(0.0, 0.0, 0.0);
	glutSolidCube(EYE_SIZE);
	glTranslatef(EYE_SIZE, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(EYE_SIZE);
	glTranslatef(HEAD_SIZE / 2 - EYE_SIZE, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glutSolidCube(EYE_SIZE);
	glTranslatef(-EYE_SIZE, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(EYE_SIZE);
	glTranslatef(EYE_SIZE, 0.0, 0.0);

	GLfloat NOSTRIL_SIZE = 0.15;				//start to draw nose
	GLfloat NOSE_SIZE = HEAD_SIZE / 4;
	glTranslatef(-HEAD_SIZE / 4, -HEAD_SIZE / 4, 0.0);
	glColor3f(1.0, 0.45, 0.45);
	glutSolidCube(NOSE_SIZE);
	glTranslatef(0.2, 0.0, NOSE_SIZE / 2);
	glColor3f(0.0, 0.0, 0.0);
	glutSolidCube(NOSTRIL_SIZE);
	glTranslatef(-0.4, 0.0, 0.0);
	glutSolidCube(NOSTRIL_SIZE);
	glPopMatrix();


	glPushMatrix();								//draw ear
	glTranslatef(HEAD_SIZE / 2, HEAD_SIZE / 2, HEAD_SIZE / 2.5);
	glRotatef(45, 1.0, -1.0, 0.0);
	ear();
	glPopMatrix();

	glPushMatrix();								//draw another ear
	glTranslatef(-HEAD_SIZE / 2, HEAD_SIZE / 2, HEAD_SIZE / 2.5);
	glRotatef(45, 1.0, 1.0, 0.0);
	ear();
	glPopMatrix();
}


void tail() {
	GLfloat TAIL_LENGTH = 2.0;
	glPushMatrix();
	glTranslatef(0.0, -BODY_WIDTH / 2, -(PIECE_LENGTH * 15 + TAIL_LENGTH / 2));
	glRotatef(-30, 1.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	//glutSolidSphere(1, 30, 30);
	gluCylinder(p, 0, 0.1, TAIL_LENGTH, 15, 15);
	glPopMatrix();
}


void leg(int PARA) {

	GLfloat LEG_LENGTH = 1.5;
	GLfloat LEG_LENGTH2 = 0.85;
	GLfloat LEG_THICK = 0.8;


	glRotatef(PARA*jointANGLE[0], 1.0, 0.0, 0.0);
	glTranslatef(0.0, -LEG_LENGTH / 2, 0.0);
	glPushMatrix();
	glScalef(LEG_THICK, LEG_LENGTH, LEG_THICK);
	glColor3f(1.0, 0.75, 0.8);
	glutSolidCube(1.0);
	glPopMatrix();

	glTranslatef(0.0, -(LEG_LENGTH / 2 + LEG_LENGTH2 / 4), 0.0);
	glRotatef(PARA*jointANGLE[1], 1.0, 0.0, 0.0);
	glScalef(LEG_THICK, LEG_LENGTH2, LEG_THICK);
	glColor3f(0.6, 0.5, 0.5);
	glutSolidCube(0.9);

}

void legs() {
	GLfloat corsswise = BODY_WIDTH / 1.98;
	GLfloat LEG_LOC = -BODY_WIDTH / 1.5;
	glPushMatrix();					//left front leg
	glTranslatef(corsswise, LEG_LOC, -(PIECE_LENGTH * 4));
	leg(1);
	glPopMatrix();

	glPushMatrix();					//right front leg
	glTranslatef(-corsswise, LEG_LOC, -(PIECE_LENGTH * 4));
	leg(-1);
	glPopMatrix();

	glPushMatrix();					//left back leg
	glTranslatef(corsswise, LEG_LOC, -(PIECE_LENGTH * 12));
	leg(-1);
	glPopMatrix();

	glPushMatrix();					//right back leg
	glTranslatef(-corsswise, LEG_LOC, -(PIECE_LENGTH * 12));
	leg(1);
	glPopMatrix();
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glTranslatef(currentLocation[0], 0.0, 0.0);
	glTranslatef(0.0, 0.0, currentLocation[1]);
	glRotatef(theta[0], 1.0, 0.0, 0.0);			//rotate by control of keys
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	base();
	head();
	legs();
	tail();

	glutSwapBuffers();
}


void init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.5f);
	p = gluNewQuadric();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-12.0, 12.0, -12.0, 12.0, -10.0, 10.0);
}



void specialkey(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		axis = 0;
		break;
	case GLUT_KEY_UP:
		axis = 1;
		break;
	case GLUT_KEY_RIGHT:
		axis = 2;
		break;
	}
}

/*void key(unsigned char key, int x, int y) {

	if (key == 'd' | key == 'D')
		axis = 0;
	if (key == 'w' | key == 'W')
		axis = 1;
	if (key == 'a' | key == 'A')
		axis = 2;
}*/


void idle()
{
	GLfloat LEG_SPEED = RUN_STEP * 10;
	vertical = GL_FALSE;
	level = GL_FALSE;

	if (jointSPIN) {

		if (WHICH_PATH == 1) {
			if (currentLocation[1] <= -2) {
				WHICH_PATH++;
				jointSPIN = GL_FALSE;
			}
			else {
				vertical = GL_TRUE;
				currentLocation[1] -= RUN_STEP;
			}
		}

		else if (WHICH_PATH == 2) {
			if (currentLocation[0] <= -2) {
				WHICH_PATH++;
				jointSPIN = GL_FALSE;
			}
			else {
				level = GL_TRUE;
				currentLocation[0] -= RUN_STEP;
			}
		}

		else if (WHICH_PATH == 3) {
			if (currentLocation[1] >= 2) {
				WHICH_PATH++;
				jointSPIN = GL_FALSE;
			}
			else {
				vertical = GL_TRUE;
				currentLocation[1] += RUN_STEP;
			}
		}

		else if (WHICH_PATH == 4) {
			if (currentLocation[0] >= 2) {
				WHICH_PATH++;
				jointSPIN = GL_FALSE;
			}
			else {
				level = GL_TRUE;
				currentLocation[0] += RUN_STEP;
			}
		}
		else {
			WHICH_PATH = 1;
		}



		if (BIG_LEG_MOVE_DIRECTION == 1) {
			jointANGLE[0] += LEG_SPEED;
			if (jointANGLE[0] > 30) {
				BIG_LEG_MOVE_DIRECTION = -1;
			}
		}
		if (BIG_LEG_MOVE_DIRECTION == -1) {
			jointANGLE[0] -= LEG_SPEED;
			if (jointANGLE[0] < -30) {
				BIG_LEG_MOVE_DIRECTION = 1;
			}
		}
		if (LITTLE_LEG_MOVE_DIRECTION == -1) {
			jointANGLE[1] += LEG_SPEED;
			if (jointANGLE[1] > 30) {
				LITTLE_LEG_MOVE_DIRECTION = 1;
			}
		}
		else {
			jointANGLE[1] -= LEG_SPEED;
			if (jointANGLE[1] < -30) {
				LITTLE_LEG_MOVE_DIRECTION = -1;
			}
		}
	}

	if (Rotate) {
		theta[axis] += -0.1;
	}

	glutPostRedisplay();
}

void ExecuteMenu(int value) {

	if (value == RUN) {
		jointSPIN = !jointSPIN;
	}
	else if (value == SPIN) {
		Rotate = !Rotate;
	}
}


void MyMenu() {
	glutAddMenuEntry("Running", RUN);
	glutAddMenuEntry("Rotating", SPIN);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("A PIG");
	glutCreateMenu(ExecuteMenu);
	//glutKeyboardFunc(key);
	glutSpecialFunc(specialkey);
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glEnable(GL_DEPTH_TEST); /* Enable hidden-surface removal */
	MyMenu();
	init();
	glutMainLoop();
}

