/*
 * lab5_.c
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

//set the order of all parts
#define ALL 0
#define BODY 1
#define LUA 2
#define LLA 3
#define RUA 4
#define RLA 5
#define LUL 6
#define LLL 7
#define RUL 8
#define RLL 9
#define LF 10
#define RF 11

//set translating, bending and rotate velocity
#define transLeftBoudary -10.0
#define transRightBoudary 15.0
#define transVelocity 0.5

#define bendBODYv 0.1
#define bendLUAv 0.8
#define bendLLAv 0.4
#define bendRUAv 0.8
#define bendRLAv 0.4
#define bendLULv 0.8
#define bendLLLv 0.4
#define bendRULv 0.8
#define bendRLLv 0.4
#define bendLFv 0.15
#define bendRFv 0.15


#define rotateVelocity 1

//set rotate angle
GLfloat theta[]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0,0,0,0};

//set states
GLfloat transDirection=1;
GLboolean translate_state=GL_FALSE;

//set bending direction
GLfloat bendingDirection[]={0,-1,1,1,-1,-1,-1,-1,1,1,1,1};

//set states
GLboolean bending_state=GL_FALSE;
GLboolean rotate_state=GL_FALSE;

GLfloat posX=0,posY=0,posZ=0;//set temp position for translating

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
    return;
}

void head()
{
    glPushMatrix();
    glutSolidSphere(HEAD_RADIUS,100,100);
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
    return;
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
    return;
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
    return;
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
    return;
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
    return;
}

void eye()
{
    glPushMatrix();
    glutSolidSphere(EYE_RADIUS, 100, 100);
    glPopMatrix();
    return;
}

void object()
{
    glTranslatef(posX, posY, posZ);//all part should translate
    glRotatef(theta[ALL], 0, 1, 0);//all part should rotate some angles

	//make the left feeler
	glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    glColor3f(0.1,1.0,0.1);
    glTranslatef(BODY_RADIUS/2,BODY_HEIGHT+NECK_HEIGHT+(HEAD_RADIUS*sqrt(3)/2),0.0);
    glRotatef(theta[LF], 1, 0, 0);
    glRotatef(-30.0,0.0,0.0,1.0);
    feeler();
    glPopMatrix();

	//make the right feeler
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    glColor3f(0.1,1.0,0.1);
    glTranslatef(-BODY_RADIUS/2,BODY_HEIGHT+NECK_HEIGHT+(HEAD_RADIUS*sqrt(3)/2),0.0);
    glRotatef(theta[RF], 1, 0, 0);
    glRotatef(30.0,0.0,0.0,1.0);
    feeler();
    glPopMatrix();

	//make the head
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    glColor3f(0.7,1.0,0.7);
    glTranslatef(0, BODY_HEIGHT+NECK_HEIGHT, 0);
    head();
    glPopMatrix();

	//make the neck
	glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    glColor3f(1.0,1.0,1.0);
    glTranslatef(0, BODY_HEIGHT+NECK_HEIGHT, 0);
    neck();
    glPopMatrix();

	//make the body
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    glColor3f(0.7,1.0,0.7);
    body();
    glPopMatrix();

	//make the left upper and lower arm
	glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    glColor3f(0.55,1.0,0.55);
    glTranslatef(-BODY_RADIUS*8/7, 0, 0);
    glTranslatef(0.0, BODY_HEIGHT, 0);
    glRotatef(theta[LUA], 1, 0, 0);
    glTranslatef(0.0, -UPPER_ARM_HEIGHT, 0.0);
    upper_arm();
    glColor3f(0.1,1.0,0.1);
    glRotatef(theta[LLA], 1, 0, 0);
    glTranslatef(0.0, -LOWER_ARM_HEIGHT*0.9,0.0);
    lower_arm();
    glPopMatrix();

	//make the right upper and lower arm
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    glColor3f(0.55,1.0,0.55);
    glTranslatef(BODY_RADIUS*8/7, 0, 0);
    glTranslatef(0.0, BODY_HEIGHT, 0);
    glRotatef(theta[RUA], 1, 0, 0);
    glTranslatef(0.0, -UPPER_ARM_HEIGHT, 0.0);
    upper_arm();
    glColor3f(0.1,1.0,0.1);
    glRotatef(theta[RLA], 1, 0, 0);
    glTranslatef(0.0, -LOWER_ARM_HEIGHT*0.9, 0.0);
    lower_arm();
    glPopMatrix();

	//make the left upper and lower leg
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    glColor3f(0.55,1.0,0.55);
    glTranslatef(-BODY_RADIUS/2, 0, 0);
    glRotatef(theta[LUL], 1, 0, 0);
    glTranslatef(0.0, -UPPER_LEG_HEIGHT, 0.0);
    upper_leg();
    glColor3f(0.2,1.0,0.2);
    glRotatef(theta[LLL], 1, 0, 0);
    glTranslatef(0.0, -LOWER_LEG_HEIGHT*0.9, 0.0);
    lower_leg();
    glPopMatrix();

	//make the right upper and lower leg
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    glColor3f(0.55,1.0,0.55);
    glTranslatef(BODY_RADIUS/2, 0, 0);
    glRotatef(theta[RUL], 1, 0, 0);
    glTranslatef(0.0, -UPPER_LEG_HEIGHT, 0.0);
    upper_leg();
    glColor3f(0.3,1.0,0.3);
    glRotatef(theta[RLL], 1, 0, 0);
    glTranslatef(0.0, -LOWER_LEG_HEIGHT*0.9, 0.0);
    lower_leg();
    glPopMatrix();

    //make the left eye
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    glColor3f(1.0,1.0,1.0);
    glTranslatef(-HEAD_RADIUS*2/5,BODY_HEIGHT+NECK_HEIGHT+HEAD_RADIUS*3/5-EYE_RADIUS,HEAD_RADIUS*4/5);
    eye();
    glPopMatrix();

	//make the right eye
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
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

	//double buffer
    glutSwapBuffers();
    return;
}

void bendFunc(GLint order, GLfloat MaxAngle, GLfloat MinAngle)
{
    if (theta[order]>=MaxAngle)
        bendingDirection[order]=-1;
    if (theta[order]<=MinAngle)
        bendingDirection[order]=1;
    return;
}

//run the function if there is no event
void myidle()
{
    if (translate_state==GL_TRUE)
    {
        posX+=transDirection*transVelocity;
        if (posX<=transLeftBoudary)
            transDirection=1;
        if (posX>=transRightBoudary)
            transDirection=-1;
    }
    if (bending_state==GL_TRUE)
    {
        theta[BODY]+=bendBODYv*bendingDirection[BODY];
        bendFunc(BODY,15,-30);
        theta[LUA]+=bendLUAv*bendingDirection[LUA];
        bendFunc(LUA,40,-40);
        theta[LLA]+=bendLUAv*bendingDirection[LLA];
        bendFunc(LLA,20,-20);
        theta[RUA]+=bendRUAv*bendingDirection[RUA];
        bendFunc(RUA,40,-40);
        theta[RLA]+=bendRLAv*bendingDirection[RLA];
        bendFunc(RLA,20,-20);
        theta[LUL]+=bendLULv*bendingDirection[LUL];
        bendFunc(LUL,40,-40);
        theta[LLL]+=bendLLLv*bendingDirection[LLL];
        bendFunc(LLL,20,-20);
        theta[RUL]+=bendRULv*bendingDirection[RUL];
        bendFunc(RUL,40,-40);
        theta[RLL]+=bendRLLv*bendingDirection[RLL];
        bendFunc(RLL,20,-20);
        theta[LF]+=bendLFv*bendingDirection[LF];
        bendFunc(LF,15,-15);
        theta[RF]+=bendRFv*bendingDirection[RF];
        bendFunc(RF,15,-15);
    }
    if (rotate_state==GL_TRUE)
    {
        theta[ALL]+=rotateVelocity;
        if (theta[ALL]>360)
            theta[ALL]=0;
    }
    glutPostRedisplay();
    return;
}

//use menu to change animation state
void mymenu(int id)
{
    if (id==1)
    {
        translate_state=!translate_state;
        return;
    }
    if (id==2)
    {
        bending_state=!bending_state;
        return;
    }
    if (id==3)
    {
        rotate_state=!rotate_state;
        return;
    }
    return;
}

//create menu
void createMenu()
{
    int id;
    id=glutCreateMenu(mymenu);
    glutAddMenuEntry("Translatng",1);
    glutAddMenuEntry("Bending",2);
    glutAddMenuEntry("Rootating",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    return;
}

//initialize color
void myinit()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    p=gluNewQuadric();
    return;
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
    return;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,800);
    glutCreateWindow("My Android Robot");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(myidle);
    glEnable(GL_DEPTH_TEST);
    myinit();
    createMenu();
    glutMainLoop();
}





