/*
 * flying bee.c
 *
 *  Created on: 2018Äê4ÔÂ21ÈÕ
 *      Author: 40360
 */

#include<GL/GLUT.h>;
#include<stdlib.h>;
#include<stdio.h>;
#include <math.h>;
#include <stdbool.h>
#include <time.h>;

#define W 500.0
#define H 500.0
#define O_LEFT -10
#define O_RIGHT 10
#define O_BOTTOM -10
#define O_TOP 10
#define O_NEAR -10
#define O_FAR 10

GLUquadricObj *p;
GLint menu_id = 0;
GLint submenu_id = 1;

bool flyingFlag = true;
bool jumpingFlag = true;

bool rotateFlag = false;
bool flyFlag = false;
bool jumpFlag = false;
GLfloat ijumpX = 0;
GLfloat ijumpY = 0;
GLfloat ijumpZ = 0;
GLfloat wingAngle = 0;
GLfloat jumpX = 0;
GLfloat jumpY = 0;
GLfloat jumpZ = 0;
GLfloat angle = 0;
//lights

typedef struct lightingStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
} lightingStruct;

lightingStruct whiteLighting = {
	{ 0.0, 0.0, 0.0, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 }
};

GLfloat light0_pos[4] = { 1.0, 2.0, 3.0, 1.0 };

//materials
typedef struct materialStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
} materialStruct;

materialStruct brassMaterials = {
	{ 0.33, 0.22, 0.03, 1.0 },
	{ 0.78, 0.57, 0.11, 1.0 },
	{ 0.99, 0.91, 0.81, 1.0 },
	27.8
};
//first set
//2nd set
materialStruct coldTailMaterials = { { 0.3, 0.3, 0.7, 1.0 },{ 0.5, 0.5, 0.8, 1.0 },{ 1.0, 1.0, 1.0, 1.0 },50.0 };
materialStruct coldHeadMaterials = { { 0.3, 0.3, 0.7, 1.0 },{ 0.5, 0.5, 0.8, 1.0 },{ 1.0, 1.0, 1.0, 1.0 },50.0 };
materialStruct coldBodyMaterials = { { 0.3, 0.3, 0.7, 1.0 },{ 0.5, 0.5, 0.8, 1.0 },{ 1.0, 1.0, 1.0, 1.0 },50.0 };
materialStruct coldAntenneMaterials = { { 1.0, 0.0, 0.5, 1.0 },{ 1.0, 0.1, 0.5, 1.0 },{ 0.0, 0.0, 0.5, 1.0 },80.0 };
materialStruct coldEyeMaterials = { { 0.0, 0.0, 0.1, 1.0 },{ 0.1, 0.1, 0.1, 1.0 },{ 0.0, 0.0, 0.1, 1.0 },0.0 };
materialStruct coldWingMaterials = { { 0.3, 0.3, 0.7, 1.0 },{ 0.3, 0.5, 0.8, 1.0 },{ 0.0, 1.0, 1.0, 1.0 },30.0 };

//3rd set
materialStruct krbody = {
	{ 0.250000, 0.250000, 0.250000, 1.000000 },
	{ 0.400000, 0.400000, 0.400000, 1.000000 },
	{ 0.774597, 0.774597, 0.774597, 1.000000 },
	76.800003
};
materialStruct brasshead = {
	{ 0.191250, 0.073500, 0.022500, 1.000000 },
	{ 0.703800, 0.270480, 0.082800, 1.000000 },
	{ 0.256777, 0.137622, 0.086014, 1.000000 },
	12.800000
};
materialStruct waxwing = {
	{ 0.105882, 0.058824, 0.113725, 1.000000 },
	{ 0.427451, 0.470588, 0.541176, 1.000000 },
	{ 0.333333, 0.333333, 0.521569, 1.000000 },
	9.846150
};
materialStruct blacktail = {
	{ 0.053750, 0.050000, 0.066250, 0.820000 },
	{ 0.182750, 0.170000, 0.225250, 0.820000 },
	{ 0.332741, 0.328634, 0.346435, 0.820000 },
	38.400002
};




materialStruct redPlasticMaterials = {
	{ 0.3, 0.0, 0.0, 1.0 },
	{ 0.6, 0.0, 0.0, 1.0 },
	{ 0.8, 0.6, 0.6, 1.0 },
	32.0
};

materialStruct whiteShinyMaterials = {
	{ 1.0, 1.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 },
	100.0
};

materialStruct *bodyMaterial;
materialStruct *headMaterial;
materialStruct *wingMaterial;
materialStruct *tailMaterial;
materialStruct *anteMaterial;
materialStruct *eyeMaterial;



materialStruct *currentMaterials;
lightingStruct *currentLighting;

void init()
{
	p = gluNewQuadric();
	glClearColor(0.49f, 0.69f, 0.92f, 1.0f);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	glLoadIdentity();


	currentLighting = &whiteLighting;

	glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting->ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting->diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting->specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);



	headMaterial = &brasshead;
	bodyMaterial = &krbody;
	wingMaterial = &waxwing;
	tailMaterial = &blacktail;
	eyeMaterial = &coldEyeMaterials;
	anteMaterial = &coldAntenneMaterials;
}

void head() {
	glPushMatrix();
	glRotated(12, 1, 0, 0);
	glScaled(0.8, 0.8, 0.8);
	glTranslated(-3, 0.4, 0);
	glutSolidSphere(1, 100, 100);

	glPopMatrix();
}
void eyes() {
	glPushMatrix();
	glTranslated(-3, 0.5, 0.6);
	glutSolidSphere(0.15, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-3, 0.5, -0.6);
	glutSolidSphere(0.15, 100, 100);
	glPopMatrix();
}
void mouth() {
	glPushMatrix();
	glTranslated(-3, 0, 0);
	glutSolidSphere(0.4, 100, 100);
	glPopMatrix();
}
void body() {
	glPushMatrix();
	glRotated(12, 0, 0, -1);
	glScaled(2, 1.2, 1.2);
	glutSolidSphere(1, 100, 100);

	glPopMatrix();
}
void wings() {
	glPushMatrix();
	glRotated(45, 1, 0, 0);
	glScaled(1, 2, 0.01);//main wing
	glTranslated(-0.3, 1, 60);
	glutSolidSphere(1, 100, 100);
	glPopMatrix();


	glPushMatrix();
	glRotated(45, 1, 0, 0);
	glScaled(0.8, 1, 0.01);//side wing
	glTranslated(1, 1.5, 60);
	glutSolidSphere(1, 100, 100);
	glPopMatrix();

}
void wings1() {

	glPushMatrix();
	glRotated(-45, 1, 0, 0);
	glScaled(1, 2, 0.01);//main wing
	glTranslated(-0.3, 1, -60);

	glutSolidSphere(1, 100, 100);
	glPopMatrix();



	glPushMatrix();
	glRotated(-45, 1, 0, 0);
	glScaled(0.8, 1, 0.01);
	glTranslated(1, 1.5, -60);
	glutSolidSphere(1, 100, 100);
	glPopMatrix();
}
void tail() {
	glPushMatrix();
	//glScaled(0.5, 0.5, 0.5);
	glTranslated(1.8, -0.5, 0);
	glRotated(90, 0.5, 1, 0);
	glutSolidCone(0.25, 1, 100, 100);

	//p = gluNewQuadric(); // initialisation
	//gluCylinder (p, 0.5, 0.01, 3.0, 32, 32); /* cylinder of radius 1.0 at its base; radius 1.0 at its top; height of 3.0; 32 slices (subdivisions around the z axis); 32 stacks (subdivisions along the z axis) */
	glPopMatrix();
}
void legs() {
	glPushMatrix();
	//front legs
	glRotated(-30, 1, 0, 0);
	glTranslated(-1, -1.2, 0.4);
	glScaled(0.1, 1, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotated(30, 1, 0, 0);
	glTranslated(-1, -1.2, -0.4);
	glScaled(0.1, 1, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	//middle legs
	glPushMatrix();
	glRotated(-30, 1, 0, 0);
	glTranslated(0, -1.2, 0.6);
	glScaled(0.1, 1, 0.1);//
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotated(30, 1, 0, 0);
	glTranslated(0, -1.2, -0.6);
	glScaled(0.1, 1, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	//end legs
	glPushMatrix();
	glRotated(-30, 1, 0, 0);
	glTranslated(1, -1.2, 0.6);
	glScaled(0.1, 1, 0.1);//
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotated(30, 1, 0, 0);
	glTranslated(1, -1.2, -0.6);
	glScaled(0.1, 1, 0.1);
	glutSolidCube(1);
	glPopMatrix();

}
void antenna() {
	glPushMatrix();
	glTranslated(-2.5, 0.64, 0.54);
	glRotated(-90, 1, 1, 0);

	GLUquadricObj *p; // pointer to quadric object
	p = gluNewQuadric(); // initialisation
	gluCylinder(p, 0.1, 0.1, 2.0, 32, 32);
	/* cylinder of radius 1.0 at its base;
	radius 1.0 at its top;
	height of 3.0;
	32 slices (subdivisions around the z axis);
	32 stacks (subdivisions along the z axis) */
	glPopMatrix();


	glPushMatrix();
	glTranslated(-2.5, 0.64, -0.54);
	glRotated(-90, 1, 1, 0);
	// glScaled(1, -1, -1);
	p = gluNewQuadric(); // initialisation
	gluCylinder(p, 0.1, 0.1, 2.0, 32, 32);

	glPopMatrix();
}

void chooseMaterial(materialStruct *material)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &material->shininess);
}


void animal() //here is the animal
{
	glPushMatrix();
	chooseMaterial(headMaterial);
	glColor3f(0.1, 0.71, 0.35);
	head();
	glPopMatrix();

	glPushMatrix();
	chooseMaterial(bodyMaterial);
	glColor3f(0.8, 0.5, 0.6);
	body();
	glPopMatrix();

	glPushMatrix();
	chooseMaterial(wingMaterial);
	glColor4d(0.9, 0.9, 0.9, 0.9);
	glRotated(wingAngle, 1, 0, 0);
	wings();
	glPopMatrix();

	glPushMatrix();
	chooseMaterial(wingMaterial);
	glColor4d(0.9, 0.9, 0.9, 0.9);
	glRotated(-wingAngle, 1, 0, 0);
	wings1();
	glPopMatrix();

	glPushMatrix();
	chooseMaterial(eyeMaterial);
	glColor3f(0, 0, 0);
	eyes();
	glPopMatrix();

	glPushMatrix();
	chooseMaterial(tailMaterial);
	glColor3f(0.5, 0.4, 0.6);
	tail();
	legs();
	glColor3f(0.1, 0.1, 0.1);
	glPopMatrix();

	glPushMatrix();
	chooseMaterial(tailMaterial);
	glColor3f(0.5, 0.4, 0.6);
	antenna();
	glPopMatrix();
	// mouth();
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-1, 0.25, 0.25, 0.0, 0.0, 0.0, 1, 1, 0);

	glRotatef(angle, 0, 1, 0);
	glTranslated(jumpX, jumpY, jumpZ);

	animal();

	glutSwapBuffers();
}
void reshape(int w, int h)//for reshape
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(O_LEFT, O_RIGHT, O_BOTTOM*(GLfloat)h / (GLfloat)w, O_TOP*(GLfloat)h / (GLfloat)w, O_NEAR, O_FAR);
	else
		glOrtho(O_LEFT*(GLfloat)w / (GLfloat)h, O_RIGHT*(GLfloat)w / (GLfloat)h, O_BOTTOM, O_TOP, O_NEAR, O_FAR);
}

void myidle(void) //for the movement later
{
	if (rotateFlag) {
		angle += 0.5;
		if (angle>360.0)
		{
			angle = 0;
		}
	}

	if (flyFlag) {
		if (flyingFlag) {
			wingAngle += 1;
			if (wingAngle > 20) {
				flyingFlag = false;
			}
		}
		else {
			wingAngle -= 1;
			if (wingAngle < 1) {
				flyingFlag = true;
			}
		}
	}

	if (jumpFlag) {
		/*
		if (abs(ijumpX) <= 9 && abs(ijumpY) <= 9 && abs(ijumpZ) <= 9) {
		srand(time(NULL));
		ijumpX = rand() % 18 - 9;
		ijumpY = rand() % 18 - 9;
		ijumpZ = rand() % 18 - 9;
		}*/
		//use random values
		int i, j;
		srand(time(NULL));
		i = rand() % 5 + 3;

		if (jumpingFlag) {
			jumpX += 0.005;
			jumpY += 0.005;
			jumpZ += 0.005;
			if (jumpY>i | jumpX>i | jumpZ > i) {
				jumpingFlag = false;
			}
		}

		else {
			jumpX -= 0.005;
			jumpY -= 0.005;
			jumpZ -= 0.005;
			if (jumpY<1 | jumpX<1 | jumpZ < 1) {
				jumpingFlag = true;
			}
		}

	}

	display();
}

void mymouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		flyFlag = !flyFlag;
		rotateFlag = !rotateFlag;
		jumpFlag = !jumpFlag;
	}

}



int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(W, H);
	glutCreateWindow("bee");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(myidle);
	glEnable(GL_DEPTH_TEST); /* Enable hidden-surface removal */
	init();

	glutMouseFunc(mymouse);




	glutMainLoop();
}


