/*
 * lab8_.c
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

#define SPOTLIGHT_RADIUS 0.5

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

//set bending and rotate velocity
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

//set bending direction
GLfloat bendingDirection[]={0,-1,1,1,-1,-1,-1,-1,1,1,1,1};

//set states
GLboolean bending_state=GL_FALSE;
GLboolean rotate_state=GL_FALSE;

GLUquadricObj *p;   //for draw cylinder, disk and sphere

//set material structure
typedef struct materialStruct
{
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;
} materialStruct;

//set different materials
materialStruct chocolateCakeEyeMaterials={{0.21,0.07,0.11},{0.41,0.17,0.21},{0.61,0.37,0.41},15};
materialStruct chocolateCakeHeadMaterials={{0.675,0.425,0.05},{0.775,0.525,0.15},{1.0,0.85,0.45},50};
materialStruct chocolateCakeFeelerMaterials={{0.0,0.0,0.0},{0.4,0.4,0.4},{0.85,0.65,0.49},5};
materialStruct chocolateCakeNeckMaterials={{1.0,1.0,1.0},{1.0,1.0,1.0},{1.0,1.0,1.0},20};
materialStruct chocolateCakeBodyMaterials={{0.25,0.05,0.00},{0.45,0.25,0.10},{0.85,0.65,0.49},100};
materialStruct chocolateCakeUpperArmMaterials={{0.45,0.25,0.09},{0.65,0.45,0.29},{0.85,0.65,0.49},20};
materialStruct chocolateCakeLowerArmMaterials={{0.71,0.57,0.52},{0.91,0.77,0.50},{0.9,0.65,0.39},20};
materialStruct chocolateCakeUpperLegMaterials={{0.30,0.17,0.0},{0.55,0.35,0.39},{0.85,0.65,0.49},20};
materialStruct chocolateCakeLowerLegMaterials={{0.45,0.25,0.09},{0.65,0.45,0.29},{0.85,0.65,0.49},20};

materialStruct matchaCakeEyeMaterials={{0.31,0.57,0.21},{0.31,0.77,0.41},{0.31,0.77,0.61},15};
materialStruct matchaCakeHeadMaterials={{0.42,0.49,0.20},{0.45,0.59,0.27},{0.65,0.79,0.49},100};
materialStruct matchaCakeFeelerMaterials={{0.675,0.425,0.05},{0.775,0.525,0.15},{1.0,0.85,0.45},5};
materialStruct matchaCakeNeckMaterials={{1.0,1.0,1.0},{1.0,1.0,1.0},{1.0,1.0,1.0},20};
materialStruct matchaCakeBodyMaterials={{0.22,0.29,0.00},{0.25,0.39,0.07},{0.55,0.89,0.39},20};
materialStruct matchaCakeUpperArmMaterials={{0.42,0.49,0.20},{0.45,0.59,0.27},{0.65,0.79,0.49},100};
materialStruct matchaCakeLowerArmMaterials={{0.55,0.59,0.39},{0.55,0.65,0.37},{0.85,0.65,0.49},20};
materialStruct matchaCakeUpperLegMaterials={{0.52,0.30,0.18},{0.74,0.50,0.38},{0.94,0.70,0.58},20};
materialStruct matchaCakeLowerLegMaterials={{0.55,0.59,0.39},{0.55,0.65,0.37},{0.85,0.65,0.49},20};

materialStruct strawberryCakeEyeMaterials={{0.85,0.74,0.74},{0.90,0.88,0.86},{1.0,1.0,1.0},20};
materialStruct strawberryCakeHeadMaterials={{0.82,0.18,0.18},{0.90,0.27,0.27},{0.9,0.47,0.47},50};
materialStruct strawberryCakeFeelerMaterials={{0.39,0.35,0.54},{0.59,0.55,0.74},{0.60,0.65,0.84},20};
materialStruct strawberryCakeNeckMaterials={{1.0,1.0,1.0},{1.0,1.0,1.0},{1.0,1.0,1.0},20};
materialStruct strawberryCakeBodyMaterials={{0.41,0.00,0.02},{0.71,0.30,0.32},{0.81,0.30,0.33},20};
materialStruct strawberryCakeUpperArmMaterials={{0.25,0.11,0.42},{0.45,0.33,0.65},{0.65,0.53,0.88},5};
materialStruct strawberryCakeLowerArmMaterials={{0.39,0.35,0.54},{0.59,0.55,0.74},{0.60,0.65,0.84},20};
materialStruct strawberryCakeUpperLegMaterials={{0.52,0.30,0.18},{0.74,0.50,0.38},{0.94,0.70,0.58},20};
materialStruct strawberryCakeLowerLegMaterials={{0.44,0.23,0.22},{0.56,0.28,0.25},{0.75,0.39,0.45},100};

//set material of every part
materialStruct *eyeMaterials;
materialStruct *headMaterials;
materialStruct *feelerMaterials;
materialStruct *neckMaterials;
materialStruct *bodyMaterials;
materialStruct *upperArmMaterials;
materialStruct *lowerArmMaterials;
materialStruct *upperLegMaterials;
materialStruct *lowerLegMaterials;

//set lighting structure
typedef struct lightingStruct
{
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
} lightingStruct;

//set white,yellow and red light
lightingStruct whiteLighting={{0.0,0.0,0.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0}};
lightingStruct yellowLighting={{0.0,0.0,0.0,1.0},{1.8,1.0,0.0,1.0},{1.0,1.0,0.0,1.0}};
lightingStruct redLighting={{0.0,0.0,0.0,1.0},{1.0,0.0,0.0,1.0},{1.0,0.0,0.0,1.0}};

//set current lighting
lightingStruct *currentLighting;

//set spot sphere's color,cutoff angle
GLfloat sphere_color[3];
GLfloat cutoff_angle;

//set light's position and direction
GLfloat light0_pos[]={WIN_RIGHT*2/3,WIN_TOP*2/3,WIN_FAR*2/3,1.0};
GLfloat light_direction[]={-1,-1,-1};

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

//draw the spotlight and set the spotlight's emission color
void spotlight()
{
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3fv(sphere_color);
    glutSolidSphere(SPOTLIGHT_RADIUS, 100, 100);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    return;
}

//make a function to set material of every part
void chooseMaterial(materialStruct *material)
{
    glMaterialfv(GL_FRONT,GL_AMBIENT,material->ambient);//set ambient
    glMaterialfv(GL_FRONT,GL_DIFFUSE,material->diffuse);//set diffuse
    glMaterialfv(GL_FRONT,GL_SPECULAR,material->specular);//set specular
    glMaterialfv(GL_FRONT,GL_SHININESS,&material->shininess);//set shinness
    return;
}

//make the whole object and put the object into world
void object()
{
    glRotatef(theta[ALL], 0, 1, 0);//all part should rotate some angles

	//make the left feeler
	glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);//every part should rotate with body
    chooseMaterial(feelerMaterials);
    glTranslatef(BODY_RADIUS/2,BODY_HEIGHT+NECK_HEIGHT+(HEAD_RADIUS*sqrt(3)/2),0.0);
    glRotatef(theta[LF], 1, 0, 0);
    glRotatef(-30.0,0.0,0.0,1.0);
    feeler();
    glPopMatrix();

	//make the right feeler
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    chooseMaterial(feelerMaterials);
    glTranslatef(-BODY_RADIUS/2,BODY_HEIGHT+NECK_HEIGHT+(HEAD_RADIUS*sqrt(3)/2),0.0);
    glRotatef(theta[RF], 1, 0, 0);
    glRotatef(30.0,0.0,0.0,1.0);
    feeler();
    glPopMatrix();

	//make the head
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    chooseMaterial(headMaterials);
    glTranslatef(0, BODY_HEIGHT+NECK_HEIGHT, 0);
    head();
    glPopMatrix();

	//make the neck
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    chooseMaterial(neckMaterials);
    glTranslatef(0, BODY_HEIGHT+NECK_HEIGHT, 0);
    neck();
    glPopMatrix();

	//make the body
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    chooseMaterial(bodyMaterials);
    body();
    glPopMatrix();

	//make the left upper and lower arm
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    chooseMaterial(upperArmMaterials);
    glTranslatef(-BODY_RADIUS*8/7, 0, 0);
    glTranslatef(0.0, BODY_HEIGHT, 0);
    glRotatef(theta[LUA], 1, 0, 0);
    glTranslatef(0.0, -UPPER_ARM_HEIGHT, 0.0);
    upper_arm();
    chooseMaterial(lowerArmMaterials);
    glRotatef(theta[LLA], 1, 0, 0);
    glTranslatef(0.0, -LOWER_ARM_HEIGHT*0.9,0.0);
    lower_arm();
    glPopMatrix();

	//make the right upper and lower arm
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    chooseMaterial(upperArmMaterials);
    glTranslatef(BODY_RADIUS*8/7, 0, 0);
    glTranslatef(0.0, BODY_HEIGHT, 0);
    glRotatef(theta[RUA], 1, 0, 0);
    glTranslatef(0.0, -UPPER_ARM_HEIGHT, 0.0);
    upper_arm();
    chooseMaterial(lowerArmMaterials);
    glRotatef(theta[RLA], 1, 0, 0);
    glTranslatef(0.0, -LOWER_ARM_HEIGHT*0.9, 0.0);
    lower_arm();
    glPopMatrix();

	//make the left upper and lower leg
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    chooseMaterial(upperLegMaterials);
    glTranslatef(-BODY_RADIUS/2, 0, 0);
    glRotatef(theta[LUL], 1, 0, 0);
    glTranslatef(0.0, -UPPER_LEG_HEIGHT, 0.0);
    upper_leg();
    chooseMaterial(lowerLegMaterials);
    glRotatef(theta[LLL], 1, 0, 0);
    glTranslatef(0.0, -LOWER_LEG_HEIGHT*0.9, 0.0);
    lower_leg();
    glPopMatrix();

	//make the right upper and lower leg
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    chooseMaterial(upperLegMaterials);
    glTranslatef(BODY_RADIUS/2, 0, 0);
    glRotatef(theta[RUL], 1, 0, 0);
    glTranslatef(0.0, -UPPER_LEG_HEIGHT, 0.0);
    upper_leg();
    chooseMaterial(lowerLegMaterials);
    glRotatef(theta[RLL], 1, 0, 0);
    glTranslatef(0.0, -LOWER_LEG_HEIGHT*0.9, 0.0);
    lower_leg();
    glPopMatrix();

	//make the left eye
	glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    chooseMaterial(eyeMaterials);
    glTranslatef(-HEAD_RADIUS*2/5,BODY_HEIGHT+NECK_HEIGHT+HEAD_RADIUS*3/5-EYE_RADIUS,HEAD_RADIUS*17/24);
    eye();
    glPopMatrix();

	//make the right eye
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    chooseMaterial(eyeMaterials);
    glTranslatef(HEAD_RADIUS*2/5,BODY_HEIGHT+NECK_HEIGHT+HEAD_RADIUS*3/5-EYE_RADIUS,HEAD_RADIUS*17/24);
    eye();
    glPopMatrix();
    return;
}

//display function
void display()
{
	//clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//enable light
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

	//set light
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(-theta[ALL], 0, 1, 0);//rotate the light with reverse direction
    glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting->ambient);//set current light ambient
    glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting->diffuse);//set current light diffuse
    glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting->specular);//set current specular
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);//set current light direction
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff_angle);//set current light cutoff angle
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glTranslatef(WIN_RIGHT*2/3,WIN_TOP*2/3,WIN_FAR*2/3);//move the spot sphere to where spot light is
    spotlight();//draw spot light

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

//use keyboard function to change color
void changeLightByKey(unsigned char key,int x,int y)
{
    if (key=='w'||key=='W')
    {
        currentLighting=&whiteLighting;//change current lighting
        cutoff_angle=45;//cutoff angle
		//set sphere color
        sphere_color[0]=1.0;
        sphere_color[1]=1.0;
        sphere_color[2]=1.0;
        return;
    }
    if (key=='y'||key=='Y')
    {
        currentLighting=&yellowLighting;
        cutoff_angle=20;
        sphere_color[0]=1.0;
        sphere_color[1]=1.0;
        sphere_color[2]=0.0;
        return;
    }
    if (key=='r'||key=='R')
    {
        currentLighting=&redLighting;
        cutoff_angle=10;
        sphere_color[0]=1.0;
        sphere_color[1]=0.0;
        sphere_color[2]=0.0;
        return;
    }
    return;
}

//use mouse function to control animation state
void mymouse(GLint button,GLint state,GLint x,GLint y)
{
    if (button==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        bending_state=!bending_state;
        rotate_state=!rotate_state;
    }
    return;
}

//use menu to change materials
void mymenu(int id)
{
    if (id==1)
    {
        eyeMaterials=&chocolateCakeEyeMaterials;
        headMaterials=&chocolateCakeHeadMaterials;
        feelerMaterials=&chocolateCakeFeelerMaterials;
        neckMaterials=&chocolateCakeNeckMaterials;
        bodyMaterials=&chocolateCakeBodyMaterials;
        upperArmMaterials=&chocolateCakeUpperArmMaterials;
        lowerArmMaterials=&chocolateCakeLowerArmMaterials;
        upperLegMaterials=&chocolateCakeUpperLegMaterials;
        lowerLegMaterials=&chocolateCakeLowerLegMaterials;
        return;
    }
    if (id==2)
    {
        eyeMaterials=&matchaCakeEyeMaterials;
        headMaterials=&matchaCakeHeadMaterials;
        feelerMaterials=&matchaCakeFeelerMaterials;
        neckMaterials=&matchaCakeNeckMaterials;
        bodyMaterials=&matchaCakeBodyMaterials;
        upperArmMaterials=&matchaCakeUpperArmMaterials;
        lowerArmMaterials=&matchaCakeLowerArmMaterials;
        upperLegMaterials=&matchaCakeUpperLegMaterials;
        lowerLegMaterials=&matchaCakeLowerLegMaterials;
        return;
    }
    if (id==3)
    {
        eyeMaterials=&strawberryCakeEyeMaterials;
        headMaterials=&strawberryCakeHeadMaterials;
        feelerMaterials=&strawberryCakeFeelerMaterials;
        neckMaterials=&strawberryCakeNeckMaterials;
        bodyMaterials=&strawberryCakeBodyMaterials;
        upperArmMaterials=&strawberryCakeUpperArmMaterials;
        lowerArmMaterials=&strawberryCakeLowerArmMaterials;
        upperLegMaterials=&strawberryCakeUpperLegMaterials;
        lowerLegMaterials=&strawberryCakeLowerLegMaterials;
        return;
    }
    return;
}

//create menu
void createMenu()
{
    int id;
    id=glutCreateMenu(mymenu);
    glutAddMenuEntry("Chocolate Cake",1);
    glutAddMenuEntry("Matcha Cake",2);
    glutAddMenuEntry("Strawberry Cake",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    return;
}

//initialize color,light and material
void myinit()
{
    glClearColor(0.7,0.7,0.7,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    p=gluNewQuadric();

    currentLighting=&whiteLighting;
    sphere_color[0]=1.0;
    sphere_color[1]=1.0;
    sphere_color[2]=1.0;
    cutoff_angle=45;

    eyeMaterials=&chocolateCakeEyeMaterials;
    headMaterials=&chocolateCakeHeadMaterials;
    feelerMaterials=&chocolateCakeFeelerMaterials;
    neckMaterials=&chocolateCakeNeckMaterials;
    bodyMaterials=&chocolateCakeBodyMaterials;
    upperArmMaterials=&chocolateCakeUpperArmMaterials;
    lowerArmMaterials=&chocolateCakeLowerArmMaterials;
    upperLegMaterials=&chocolateCakeUpperLegMaterials;
    lowerLegMaterials=&chocolateCakeLowerLegMaterials;

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
    glutMouseFunc(mymouse);
    glutKeyboardFunc(changeLightByKey);
    glEnable(GL_DEPTH_TEST);
    myinit();
    createMenu();
    glutMainLoop();
}




