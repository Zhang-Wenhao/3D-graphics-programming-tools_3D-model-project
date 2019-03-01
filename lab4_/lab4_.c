/*
 * lab4_.c
 *
 *  Created on: 2018Äê4ÔÂ23ÈÕ
 *      Author: 40360
 */
#include <GL/glut.h>
#include <math.h>   //for sqrt()

//set boundary
#define WIN_LEFT -15
#define WIN_RIGHT 15
#define WIN_BOTTOM -15
#define WIN_TOP 15
#define WIN_NEAR -15
#define WIN_FAR 15

//set arguments of object
#define FEELER_RADIUS 0.1
#define FEELER_HEIGHT 1.5

#define HEAD_RADIUS 4.0

#define EYE_RADIUS 0.35

#define NECK_RADIUS 4.05
#define NECK_HEIGHT 0.5

#define BODY_HEIGHT 5.0
#define BODY_RADIUS 4.0

#define UPPER_ARM_HEIGHT 2.5
#define UPPER_ARM_RADIUS 0.5

#define LOWER_ARM_HEIGHT 2.5
#define LOWER_ARM_RADIUS 0.35

#define UPPER_LEG_HEIGHT 3.5
#define UPPER_LEG_RADIUS 0.65

#define LOWER_LEG_HEIGHT 3.5
#define LOWER_LEG_RADIUS 0.5

GLUquadricObj *p;//for draw cylinder, disk and sphere

//draw the object
void body()
{
    glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(p,BODY_RADIUS,BODY_RADIUS,BODY_HEIGHT,100,100);
    gluDisk(p, 0, BODY_RADIUS, 100, 100);
    glTranslatef(0, 0, BODY_HEIGHT);
    gluDisk(p, 0, BODY_RADIUS, 100, 100);
    glPopMatrix();
}

void head()
{
    glPushMatrix();
    gluSphere(p,HEAD_RADIUS,100,100);
    glPopMatrix();
}

void neck()
{
    glPushMatrix();
    glRotatef(90.0,1.0,0.0,0.0);
    gluCylinder(p, NECK_RADIUS, NECK_RADIUS, NECK_HEIGHT,100,100);
    glPopMatrix();
}

void feeler()
{
    glPushMatrix();
	glRotatef(-90.0,1.0,0.0,0.0);
    gluCylinder(p,FEELER_RADIUS,FEELER_RADIUS,FEELER_HEIGHT,100,100);
    glTranslatef(0.0, 0.0, FEELER_HEIGHT);
    gluDisk(p, 0, FEELER_RADIUS, 100, 100);
    glPopMatrix();
}

void lower_leg()
{
    glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(p,LOWER_LEG_RADIUS,LOWER_LEG_RADIUS,LOWER_LEG_HEIGHT,100,100);
    gluDisk(p, 0, LOWER_LEG_RADIUS, 100, 100);
    glTranslatef(0, 0, LOWER_LEG_HEIGHT);
    gluDisk(p, 0, LOWER_LEG_RADIUS, 100, 100);
    glPopMatrix();
}

void upper_leg()
{
    glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(p,UPPER_LEG_RADIUS,UPPER_LEG_RADIUS,UPPER_LEG_HEIGHT,100,100);
    gluDisk(p, 0, UPPER_LEG_RADIUS, 100, 100);
    glTranslatef(0, 0, UPPER_LEG_HEIGHT);
    gluDisk(p, 0, UPPER_LEG_RADIUS, 100, 100);
    glPopMatrix();
}

void lower_arm()
{
    glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(p,LOWER_ARM_RADIUS,LOWER_ARM_RADIUS,LOWER_ARM_HEIGHT,100,100);
    gluDisk(p, 0, LOWER_ARM_RADIUS, 100, 100);
    glTranslatef(0, 0, LOWER_ARM_HEIGHT);
    gluDisk(p, 0, LOWER_ARM_RADIUS, 100, 100);
    glPopMatrix();
}

void upper_arm()
{
    glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(p,UPPER_ARM_RADIUS,UPPER_ARM_RADIUS,UPPER_ARM_HEIGHT,100,100);
    gluDisk(p, 0, UPPER_ARM_RADIUS, 100, 100);
    glTranslatef(0, 0, UPPER_ARM_HEIGHT);
    gluDisk(p, 0, UPPER_ARM_RADIUS, 100, 100);
    glPopMatrix();
}

void eye()
{
    glPushMatrix();
    gluSphere(p, EYE_RADIUS, 100, 100);
    glPopMatrix();
}

void object()
{
	//make the left feeler
	glPushMatrix();
    glColor3f(0.1,1.0,0.1);
    glTranslatef(BODY_RADIUS/2,BODY_HEIGHT+NECK_HEIGHT+(HEAD_RADIUS*sqrt(3)/2),0.0);
    glRotatef(-30.0,0.0,0.0,1.0);
    feeler();
    glPopMatrix();

	//make the right feeler
    glPushMatrix();
    glColor3f(0.1,1.0,0.1);
    glTranslatef(-BODY_RADIUS/2,BODY_HEIGHT+NECK_HEIGHT+(HEAD_RADIUS*sqrt(3)/2),0.0);
    glRotatef(30.0,0.0,0.0,1.0);
    feeler();
    glPopMatrix();

	//make the head
    glPushMatrix();
    glColor3f(0.7,1.0,0.7);
    glTranslatef(0, BODY_HEIGHT+NECK_HEIGHT, 0);
    head();
    glPopMatrix();

	//make the neck
	glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(0, BODY_HEIGHT+NECK_HEIGHT, 0);
    neck();
    glPopMatrix();

	//make the body
    glPushMatrix();
    glColor3f(0.7,1.0,0.7);
    body();
    glPopMatrix();

	//make the left upper and lower arm
	glPushMatrix();
    glColor3f(0.55,1.0,0.55);
    glTranslatef(-BODY_RADIUS*8/7, 0, 0);
    glTranslatef(0.0, BODY_HEIGHT, 0);
    glTranslatef(0.0, -UPPER_ARM_HEIGHT, 0.0);
    upper_arm();
    glColor3f(0.1,1.0,0.1);
    glTranslatef(0.0, -LOWER_ARM_HEIGHT*0.9,0.0);
    lower_arm();
    glPopMatrix();

	//make the right upper and lower arm
    glPushMatrix();
    glColor3f(0.55,1.0,0.55);
    glTranslatef(BODY_RADIUS*8/7, 0, 0);
    glTranslatef(0.0, BODY_HEIGHT, 0);
    glTranslatef(0.0, -UPPER_ARM_HEIGHT, 0.0);
    upper_arm();
    glColor3f(0.1,1.0,0.1);
    glTranslatef(0.0, -LOWER_ARM_HEIGHT*0.9, 0.0);
    lower_arm();
    glPopMatrix();

	//make the left upper and lower leg
    glPushMatrix();
    glColor3f(0.55,1.0,0.55);
    glTranslatef(-BODY_RADIUS/2, 0, 0);
    glTranslatef(0.0, -UPPER_LEG_HEIGHT, 0.0);
    upper_leg();
    glColor3f(0.2,1.0,0.2);
    glTranslatef(0.0, -LOWER_LEG_HEIGHT*0.9, 0.0);
    lower_leg();
    glPopMatrix();

	//make the right upper and lower leg
    glPushMatrix();
    glColor3f(0.55,1.0,0.55);
    glTranslatef(BODY_RADIUS/2, 0, 0);
    glTranslatef(0.0, -UPPER_LEG_HEIGHT, 0.0);
    upper_leg();
    glColor3f(0.3,1.0,0.3);
    glTranslatef(0.0, -LOWER_LEG_HEIGHT*0.9, 0.0);
    lower_leg();
    glPopMatrix();

    //make the left eye
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(-HEAD_RADIUS*2/5,BODY_HEIGHT+NECK_HEIGHT+HEAD_RADIUS*3/5-EYE_RADIUS,HEAD_RADIUS*4/5);
    eye();
    glPopMatrix();

	//make the right eye
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(HEAD_RADIUS*2/5,BODY_HEIGHT+NECK_HEIGHT+HEAD_RADIUS*3/5-EYE_RADIUS,HEAD_RADIUS*4/5);
    eye();
    glPopMatrix();
    return;
}

//display function
void display()
{
	//clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.0,1.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);//isometric view

    object();
    glFlush();
}

//initialize color
void myinit()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    p =gluNewQuadric();
}

//make sure the whole object appears in the middle of the window and stay original ratio when reshape
void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w<=h)
        glOrtho(WIN_LEFT,WIN_RIGHT,WIN_BOTTOM*(GLfloat)h/(GLfloat)w,WIN_TOP*(GLfloat)h/(GLfloat)w,WIN_NEAR,WIN_FAR);
    else
        glOrtho(WIN_LEFT*(GLfloat)w/(GLfloat)h,WIN_RIGHT*(GLfloat)w/(GLfloat)h,WIN_BOTTOM,WIN_TOP,WIN_NEAR,WIN_FAR);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,800);
    glutCreateWindow("My Andorid Robot");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glEnable(GL_DEPTH_TEST);
    myinit();
    glutMainLoop();
}




