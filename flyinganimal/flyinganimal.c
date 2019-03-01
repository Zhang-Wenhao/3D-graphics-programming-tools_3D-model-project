/*
 * flyinganimal.c
 *
 *  Created on: 2018Äê4ÔÂ21ÈÕ
 *      Author: 40360
 */
#include <GL/glut.h>
#include <math.h>

#define W 500.0
#define H 500.0
#define PI 3.1415926536

#define BODY_RADIUS 0.3
#define BODY_HEIGHT 6.0
#define TAIL_RADIUS 0.3
#define HEAD_RADIUS 0.3
#define WING_UPPER_RADIUS 2.0
#define WING_LOWER_RADIUS 1.3
#define FEELER_BASE_RADIUS 0.05
#define FEELER_TOP_RADIUS 0.03
#define FEELER_HEIGHT 1.5
#define EYE_RADIUS 0.07

#define MOVING_SPEED 0.03
#define MOVING_RADIUS 6.0

#define O_LEFT -10
#define O_RIGHT 10
#define O_BOTTOM -10
#define O_TOP 10
#define O_NEAR -10
#define O_FAR 10

#define WHITE 0
#define BLACK 1
#define BLUE 2
#define RED 3
#define GREEN 4

GLfloat colors[][3] = { { 1.0,1.0,1.0 },{ 0.0,0.0,0.0 },{ 0.0,0.0,1.0 },{ 1.0,0.0,0.0 },{ 0.0,1.0,0.0 } };

GLfloat theta[] = { 0.0,0.0,0.0 };

GLint wl_direction = 1;
GLint wr_direction = 1;

GLfloat x;
GLfloat z;

GLUquadricObj *p;   // pointer to quadric object

GLboolean fly_state = GL_FALSE;

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

lightingStruct noonLighting = { { 0.9, 1.0, 0.9, 1.0 },{ 0.9, 1.0, 0.9, 1.0 },{ 0.9, 1.0, 0.9, 1.0 } };
lightingStruct earlyEveningLighting = { { 0.4, 0.4, 0.5, 1.0 },{ 0.4, 0.4, 0.5, 1.0 },{ 0.4, 0.4, 0.5, 1.0 } };
lightingStruct lateEveningLighting = { { 0.1, 0.1, 0.1, 1.0 },{ 0.1, 0.1, 0.1, 1.0 },{ 0.1, 0.1, 0.1, 1.0 } };

GLfloat light0_pos[4] = { 1.0, 2.0, 3.0, 1.0 };

lightingStruct *currentLighting;

typedef struct materialStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
} materialStruct;

materialStruct goldTailMaterials = { { 0.1, 0.7, 0.3, 1.0 },{ 0.1, 0.57, 0.2, 1.0 },{ 0.3, 0.91, 0.52, 1.0 },30.0 };
materialStruct goldHeadMaterials = { { 0.1, 0.7, 0.3, 1.0 },{ 0.1, 0.57, 0.2, 1.0 },{ 0.3, 0.91, 0.52, 1.0 },30.0 };
materialStruct goldBodyMaterials = { { 0.1, 0.7, 0.3, 1.0 },{ 0.1, 0.57, 0.2, 1.0 },{ 0.3, 0.91, 0.52, 1.0 },30.0 };
materialStruct goldFeelerMaterials = { { 0.0, 0.0, 0.1, 1.0 },{ 0.1, 0.1, 0.1, 1.0 },{ 0.0, 0.0, 0.1, 1.0 },0.0 };
materialStruct goldEyeMaterials = { { 0.0, 0.0, 0.1, 1.0 },{ 0.1, 0.1, 0.1, 1.0 },{ 0.0, 0.0, 0.1, 1.0 },0.0 };
materialStruct goldWingMaterials = { { 0.33, 0.22, 0.03, 1.0 },{ 0.78, 0.57, 0.11, 1.0 },{ 0.99, 0.91, 0.81, 1.0 },27.8 };

materialStruct coldTailMaterials = { { 0.3, 0.3, 0.7, 1.0 },{ 0.5, 0.5, 0.8, 1.0 },{ 1.0, 1.0, 1.0, 1.0 },50.0 };
materialStruct coldHeadMaterials = { { 0.3, 0.3, 0.7, 1.0 },{ 0.5, 0.5, 0.8, 1.0 },{ 1.0, 1.0, 1.0, 1.0 },50.0 };
materialStruct coldBodyMaterials = { { 0.3, 0.3, 0.7, 1.0 },{ 0.5, 0.5, 0.8, 1.0 },{ 1.0, 1.0, 1.0, 1.0 },50.0 };
materialStruct coldFeelerMaterials = { { 1.0, 0.0, 0.5, 1.0 },{ 1.0, 0.1, 0.5, 1.0 },{ 0.0, 0.0, 0.5, 1.0 },80.0 };
materialStruct coldEyeMaterials = { { 0.0, 0.0, 0.1, 1.0 },{ 0.1, 0.1, 0.1, 1.0 },{ 0.0, 0.0, 0.1, 1.0 },0.0 };
materialStruct coldWingMaterials = { { 0.3, 0.3, 0.7, 1.0 },{ 0.3, 0.5, 0.8, 1.0 },{ 0.0, 1.0, 1.0, 1.0 },30.0 };

materialStruct transparentTailMaterials = { { 0.7, 0.4, 0.1, 1.0 },{ 0.4, 0.2, 0.1, 1.0 },{ 0.6, 0.3, 0.1, 1.0 },10.0 };
materialStruct transparentHeadMaterials = { { 0.7, 0.4, 0.1, 1.0 },{ 0.4, 0.2, 0.1, 1.0 },{ 0.6, 0.3, 0.1, 1.0 },10.0 };
materialStruct transparentBodyMaterials = { { 0.7, 0.4, 0.1, 1.0 },{ 0.4, 0.2, 0.1, 1.0 },{ 0.6, 0.3, 0.1, 1.0 },10.0 };
materialStruct transparentFeelerMaterials = { { 0.7, 0.7, 0.7, 1.0 },{ 0.1, 0.5, 0.8, 1.0 },{ 1.0, 1.0, 1.0, 1.0 },50.0 };
materialStruct transparentEyeMaterials = { { 0.0, 0.0, 0.1, 1.0 },{ 0.1, 0.1, 0.1, 1.0 },{ 0.0, 0.0, 0.1, 1.0 },0.0 };
materialStruct transparentWingMaterials = { { 0.5, 1.0, 1.0, 1.0 },{ 0.9, 1.0, 1.0, 1.0 },{ 0.9, 1.0, 1.0, 1.0 },10.0 };

materialStruct *tailMaterials;
materialStruct *headMaterials;
materialStruct *bodyMaterials;
materialStruct *feelerMaterials;
materialStruct *eyeMaterials;
materialStruct *wingMaterials;

/* Draw a half circle */
void drawHalfCircleArea(float cx, float cy, float cz, float r, int num_segments)
{
	GLfloat vertex[4];
	GLfloat delta_angle = 1.1 * PI / num_segments;
	int i = 0;

	glBegin(GL_TRIANGLE_FAN);

	vertex[0] = cx;
	vertex[1] = cy;
	vertex[2] = cz;
	vertex[3] = 1.0;
	glVertex4fv(vertex);

	/* draw the vertex on the contour of the circle */
	while (i < num_segments)
	{
		vertex[0] = cos(delta_angle *i) * r + cx;
		vertex[1] = sin(delta_angle *i) * r + cy;
		vertex[2] = cz;
		vertex[3] = 1.0;
		glVertex4fv(vertex);
		i++;
	}
	vertex[0] = 1.0 * r + cx;
	vertex[1] = 0.0 * r + cy;
	vertex[2] = cz;
	vertex[3] = 1.0;
	glVertex4fv(vertex);
	glEnd();
}

/* give the spectific meterial structure to glMaterialfv */
void chooseMaterial(materialStruct *material)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &material->shininess);
}

void body()
{
	glPushMatrix();

	chooseMaterial(bodyMaterials);
	glTranslatef(0.0, -0.5 * BODY_HEIGHT, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(p, BODY_RADIUS, BODY_RADIUS, BODY_HEIGHT, 15, 15);

	glPopMatrix();
}

void tail()
{
	glPushMatrix();

	chooseMaterial(tailMaterials);
	glTranslatef(0.0, -0.45 * BODY_HEIGHT, 0.0);
	glScalef(1.0, 2.7, 1.0);
	gluSphere(p, TAIL_RADIUS, 20, 20);

	glPopMatrix();
}

void head()
{
	glPushMatrix();

	chooseMaterial(headMaterials);
	glTranslatef(0.0, 0.5 * BODY_HEIGHT, 0.0);
	gluSphere(p, HEAD_RADIUS, 20, 20);

	glPopMatrix();
}

void wingLeft()
{
	glPushMatrix();

	chooseMaterial(wingMaterials);

	glRotatef(90.0, 0.0, 0.0, 1.0);
	glScalef(1.1, 1.4, 1.0);

	drawHalfCircleArea(0.5, 0.15, 0.0, WING_UPPER_RADIUS, 15);
	drawHalfCircleArea(-1.3, 0.15, 0.0, WING_LOWER_RADIUS, 15);
	glNormal3f(0.0, 0.0, 1.0);

	drawHalfCircleArea(0.5, 0.15, 0.01, WING_UPPER_RADIUS, 15);
	drawHalfCircleArea(-1.3, 0.15, 0.01, WING_LOWER_RADIUS, 15);
	glNormal3f(0.0, 0.0, -1.0);

	glPopMatrix();
}

void wingRight()
{
	glPushMatrix();

	chooseMaterial(wingMaterials);

	glRotatef(-90.0, 0.0, 0.0, 1.0);
	glScalef(1.1, 1.4, 1.0);

	drawHalfCircleArea(-0.5, 0.15, 0.0, WING_UPPER_RADIUS, 15);
	drawHalfCircleArea(1.3, 0.15, 0.0, WING_LOWER_RADIUS, 15);
	glNormal3f(0.0, 0.0, 1.0);
	drawHalfCircleArea(-0.5, 0.15, 0.01, WING_UPPER_RADIUS, 15);
	drawHalfCircleArea(1.3, 0.15, 0.01, WING_LOWER_RADIUS, 15);
	glNormal3f(0.0, 0.0, -1.0);

	glPopMatrix();
}

void feelerLeft()
{
	glPushMatrix();

	chooseMaterial(feelerMaterials);

	glTranslatef(0.0, 0.5 * BODY_HEIGHT, 0.0);
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(p, FEELER_BASE_RADIUS, FEELER_TOP_RADIUS, FEELER_HEIGHT, 15, 15);
	glPopMatrix();
}

void feelerRight()
{
	glPushMatrix();

	chooseMaterial(feelerMaterials);

	glTranslatef(0.0, 0.5 * BODY_HEIGHT, 0.0);
	glTranslatef(-1.0, 0.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(p, FEELER_BASE_RADIUS, FEELER_TOP_RADIUS, FEELER_HEIGHT, 15, 15);
	glPopMatrix();
}

void eyeLeft()
{
	glPushMatrix();

	chooseMaterial(eyeMaterials);
	glTranslatef(-0.1, 0.5 * BODY_HEIGHT + 0.45 * HEAD_RADIUS, 0.18);
	gluSphere(p, EYE_RADIUS, 20, 20);

	glPopMatrix();
}

void eyeRight()
{
	glPushMatrix();

	chooseMaterial(eyeMaterials);
	glTranslatef(0.1, 0.5 * BODY_HEIGHT + 0.45 * HEAD_RADIUS, 0.18);
	gluSphere(p, EYE_RADIUS, 20, 20);

	glPopMatrix();
}

void butterfly()
{
	glTranslatef(x, 0.0, z);

	glPushMatrix();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	/* draw body */
	glRotatef(theta[0], 0.0, 0.0, 1.0);
	body();

	/* draw tail */
	tail();

	/* draw head */
	head();

	/* draw left feeler */
	glRotatef(20.0, 0.0, 0.0, 1.0);
	feelerLeft();

	/* draw right feeler */
	glRotatef(-40.0, 0.0, 0.0, 1.0);
	feelerRight();

	/* draw left eye */
	glRotatef(20.0, 0.0, 0.0, 1.0);
	eyeLeft();

	/* draw right eye */
	eyeRight();

	/* draw left wing */
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	wingLeft();

	/* draw right wing */
	glRotatef(theta[2] - theta[1], 0.0, 1.0, 0.0);
	wingRight();
	glPopMatrix();
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // clear the screen
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	butterfly();
	glutSwapBuffers();
}

void flying()
{
	if (wl_direction > 0)
	{
		theta[1] += 0.02;
		if (theta[1] > 50)
		{
			wl_direction = -1;
			theta[1] -= 0.02;
		}
	}
	else
	{
		theta[1] -= 0.02;
		if (theta[1] < -50)
		{
			wl_direction = 1;
			theta[1] += 0.02;
		}
	}

	if (wr_direction > 0)
	{
		theta[2] -= 0.02;
		if (theta[2] < -50)
		{
			wr_direction = -1;
			theta[2] += 0.02;
		}
	}
	else
	{
		theta[2] += 0.02;
		if (theta[2] > 50)
		{
			wr_direction = 1;
			theta[2] -= 0.02;
		}
	}
}

void moving()
{
	theta[0] += MOVING_SPEED;
	x = MOVING_RADIUS * cos(theta[0] * PI / 180.0);
	z = MOVING_RADIUS * sin(theta[0] * PI / 180.0);
	glutPostRedisplay();
}

void myIdle()
{
	moving();
	flying();
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		glOrtho(O_LEFT, O_RIGHT, O_BOTTOM*(GLfloat)h / (GLfloat)w, O_TOP*(GLfloat)h / (GLfloat)w, O_NEAR, O_FAR);
	else
		glOrtho(O_LEFT*(GLfloat)w / (GLfloat)h, O_RIGHT*(GLfloat)w / (GLfloat)h, O_BOTTOM, O_TOP, O_NEAR, O_FAR);
}

void setMenu(int id)
{
	if (id == 1)
	{
		tailMaterials = &goldTailMaterials;
		headMaterials = &goldHeadMaterials;
		bodyMaterials = &goldBodyMaterials;
		feelerMaterials = &goldFeelerMaterials;
		eyeMaterials = &goldEyeMaterials;
		wingMaterials = &goldWingMaterials;
	}
	if (id == 2)
	{
		tailMaterials = &coldTailMaterials;
		headMaterials = &coldHeadMaterials;
		bodyMaterials = &coldBodyMaterials;
		feelerMaterials = &coldFeelerMaterials;
		eyeMaterials = &coldEyeMaterials;
		wingMaterials = &coldWingMaterials;
	}
	if (id == 3)
	{
		tailMaterials = &transparentTailMaterials;
		headMaterials = &transparentHeadMaterials;
		bodyMaterials = &transparentBodyMaterials;
		feelerMaterials = &transparentFeelerMaterials;
		eyeMaterials = &transparentEyeMaterials;
		wingMaterials = &transparentWingMaterials;
	}
}

void lightMenu(int id)
{
	if (id == 1)
	{
		currentLighting = &noonLighting;
	}
	if (id == 2)
	{
		currentLighting = &earlyEveningLighting;
	}
	if (id == 3)
	{
		currentLighting = &lateEveningLighting;
	}
	glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting->ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting->diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting->specular);
}

void createMenu()
{
	int id;

	id = glutCreateMenu(setMenu);
	glutAddMenuEntry("Gold", 1);
	glutAddMenuEntry("Cold", 2);
	glutAddMenuEntry("Transparent", 3);
	glutAttachMenu(GLUT_LEFT_BUTTON);

	id = glutCreateMenu(lightMenu);
	glutAddMenuEntry("Noon", 1);
	glutAddMenuEntry("Early Night", 2);
	glutAddMenuEntry("Late Night", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}


void init()
{
	createMenu();
	p = gluNewQuadric();

	x = MOVING_RADIUS;
	z = 0.0;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // Set background

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	currentLighting = &noonLighting;

	glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting->ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting->diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting->specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);

	tailMaterials = &goldTailMaterials;
	headMaterials = &goldHeadMaterials;
	bodyMaterials = &goldBodyMaterials;
	feelerMaterials = &goldFeelerMaterials;
	eyeMaterials = &goldEyeMaterials;
	wingMaterials = &goldWingMaterials;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);         // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set the display mode
	glutInitWindowSize(W, H);      // set the window size in pexels
	glutCreateWindow("Butterfly"); // open the screen window

	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutIdleFunc(myIdle);

	glEnable(GL_DEPTH_TEST);       // Enable hidden-surface removal
	init();
	glutMainLoop();
}



