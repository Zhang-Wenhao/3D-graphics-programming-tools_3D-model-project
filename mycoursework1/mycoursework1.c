/*
 * mycoursework1.c
 *
 *  Created on: 2018.05.02
 *      Author: WenhaoZhang
 */

#include <GL/glut.h>
#include <math.h>   //for calculating()

//set boundary
#define LEFTB -30
#define RIGHTB 30
#define BOTTOMB -30
#define TOPB 30
#define NEARB -30
#define FARB 30

//set arguments of object
#define BODY_HEIGHT 9
#define BODY_WIDTH 16
#define BODY_LENGTH 9

#define HEAD_LENGTH 5

#define UPPER_LEG_HEIGHT 4.5
#define UPPER_LEG_RADIUS 1.0

#define LOWER_LEG_HEIGHT 4.0
#define LOWER_LEG_RADIUS 0.7

#define TAIL_RADIUS 0.6
#define TAIL_HEIGHT 3.0

#define MOUTH_LENGTH 0.30

#define HORN_RADIUS 0.8
#define HORN_HEIGHT 2.0

#define BEARD_RADIUS 0.7
#define BEARD_HEIGHT 3.0

#define SPOTLIGHT_RADIUS 1

//set the order of all parts
static GLint ALL = 1;

#define BODY 2
#define FLU 3
#define FLL 4
#define BLU 5
#define BLL 6
#define FRU 7
#define FRL 8
#define BRU 9
#define BRL 10
#define HD 11
#define TL 12

//set translating boundary
#define transLeftBoudary -13.0
#define transRightBoudary 7.0

//set translating speed
#define transSpeed 0.05

//set the moving speed
#define movBODYv 0.06
#define movFLUv 0.6
#define movFLLv 0.3
#define movFRUv 0.6
#define movFRLv 0.3
#define movBLUv 0.6
#define movBLLv 0.3
#define movBRUv 0.6
#define movBRLv 0.3
#define movHDv 0.1
#define movTLv 0.4

//set the rotating speed
#define rotateSpeed 0.345

//set rotate angle
GLfloat theta[]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0,0,0,0};

//set moving direction
GLfloat movingDirection[]={0,-1,1,1,-1,-1,-1,-1,1,1,1,1};

//set states
GLfloat transDirection=1;
GLboolean moving_state=GL_FALSE;
GLboolean rotate_state=GL_FALSE;
GLboolean translate_state=GL_FALSE;
GLint jump_TO_WHERE = 1;
GLboolean RT=GL_TRUE;
GLfloat currentLocation[3]={0.0,0.0,0.0};//set initial position of X, Z and Y


GLUquadricObj *p;   //for drawing cylinder, disk and sphere

GLint PATH = 1;

//set lighting structure
typedef struct lightingStruct
{
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
}
lightingStruct;

//set white,yellow and red light source
lightingStruct whiteLighting={{0.0,0.0,0.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0}};
lightingStruct yellowLighting={{0.0,0.0,0.0,1.0},{1.0,1.0,0.0,1.0},{1.0,1.0,0.0,1.0}};
lightingStruct redLighting={{0.0,0.0,0.0,1.0},{1.0,0.0,0.0,1.0},{1.0,1.0,1.0,1.0}};

//set current lighting
lightingStruct *Lighting;

//set spot source's color,cutoff angle
GLfloat source_color[3];
GLfloat cutoff_angle;

//set light's position and direction
GLfloat light_pos[]={-RIGHTB*2/3,TOPB*2/3,FARB*1/3};
GLfloat light_direction[]={0.3,-1,0};

//set ambient light
float model_ambient[]={0.3,0.3,0.3,1.0};

//set material structure
typedef struct materialStruct
{
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;
	}
	materialStruct;

	materialStruct	GrayHeadMaterial={{1.0,0.98,0.80,1.0},{1.0,0.98,0.80,1.0},{0.2,0.2,0.2,1.0},50.0};
	materialStruct	GrayBodyMaterial={{0.3,0.3,0.3,1.0},{0.8,0.8,0.8,1.0},{0.7,0.7,0.7,1.0},128.0};
	materialStruct	GrayUlegMaterial={{0.85,0.85,0.85,1.0},{0.85,0.85,0.85,1.0},{0.2,0.2,0.2,1.0},50.0};
	materialStruct	GrayLlegMaterial={{0.6,0.6,0.6,1.0},{0.5,0.50,0.5,1.0},{0.0,0.0,0.0,1.0},50.0};
	materialStruct	GrayHornMaterial={{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},{0.70,0.7,0.7,1.0},20.0};
	materialStruct	GrayHairMaterial={{0.45,0.45,0.45,1.0},{0.8,0.8,0.8,1.0},{0.0,0.0,0.0,1.0},50.0};
	materialStruct	GrayBeardMaterial={{0.6,0.6,0.6,1.0},{0.5,0.5,0.5,1.0},{0.0,0.0,0.0,1.0},50.0};
	materialStruct	GrayTailMaterial={{0.6,0.6,0.6,1.0},{0.5,0.50,0.5,1.0},{0.0,0.0,0.0,1.0},50.0};
	materialStruct	GrayMouthMaterial={{0.03, 0.03, 0.03, 1.0},{0.25, 0.25, 0.25, 1.0},{0.07, 0.07, 0.07, 1.0},100.0};
	materialStruct	GrayBeyeMaterial={{0.03, 0.03, 0.03, 1.0},{0.25, 0.25, 0.25, 1.0},{0.07, 0.07, 0.07, 1.0},100.0};
	materialStruct	GrayWeyeMaterial={{0.9,0.9,0.9,1.0},{0.9,0.9,0.9,1.0},{0.0,0.0,0.0,1.0},50.0};

	materialStruct	RedBlueHeadMaterial={{1.0,0.98,0.80,1.0},{1.0,0.98,0.80,1.0},{0.2,0.2,0.2,1.0},50.0};
	materialStruct	RedBlueBodyMaterial={{1.0,1.0,1.0},{1.0,1.0,1.0},{0.7,0.7,0.7,1.0},50};
	materialStruct	RedBlueUlegMaterial={{1.0,1.0,1.0},{1.0,1.0,1.0},{0.7,0.7,0.7,1.0},50};
	materialStruct	RedBlueLlegMaterial={{0.8,0.8,0.8},{0.8,0.8,0.8},{0.7,0.7,0.7,1.0},50};
	materialStruct	RedBlueHornMaterial={{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},{0.70,0.7,0.7,1.0},20.0};
	materialStruct	RedBlueHairMaterial={{1.0,1.0,1.0},{1.0,1.0,1.0},{0.7,0.7,0.7,1.0},50};
	materialStruct	RedBlueBeardMaterial={{1.0,1.0,1.0},{1.0,1.0,1.0},{0.7,0.7,0.7,1.0},50};
	materialStruct	RedBlueTailMaterial={{1.0,1.0,1.0},{1.0,1.0,1.0},{0.7,0.7,0.7,1.0},50};
	materialStruct	RedBlueMouthMaterial={{0.03, 0.03, 0.03, 1.0},{0.25, 0.25, 0.25, 1.0},{0.07, 0.07, 0.07, 1.0},100.0};
	materialStruct	RedBlueBeyeMaterial={{0.03, 0.03, 0.03, 1.0},{0.25, 0.25, 0.25, 1.0},{0.07, 0.07, 0.07, 1.0},100.0};
	materialStruct	RedBlueWeyeMaterial={{0.9,0.9,0.9,1.0},{0.9,0.9,0.9,1.0},{0.0,0.0,0.0,1.0},50.0};

	materialStruct	YellowGreenHeadMaterial={{1.0,0.98,0.80,1.0},{1.0,0.98,0.80,1.0},{0.2,0.2,0.2,1.0},50.0};
	materialStruct	YellowGreenBodyMaterial={{1.0,0.98,0.80,1.0},{1.0,0.98,0.80,1.0},{0.2,0.2,0.2,1.0},50.0};
	materialStruct	YellowGreenUlegMaterial={{1.0,0.98,0.80,1.0},{1.0,0.98,0.80,1.0},{0.2,0.2,0.2,1.0},50.0};
	materialStruct	YellowGreenLlegMaterial={{1.0,1.0,0.75,1.0},{0.8,0.8,0.5,1.0},{0.2,0.2,0.2,1.0},50.0};
	materialStruct	YellowGreenHornMaterial={{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},{0.70,0.7,0.7,1.0},20.0};
	materialStruct	YellowGreenHairMaterial={{1.0,1.0,0.75,1.0},{0.8,0.8,0.5,1.0},{0.2,0.2,0.2,1.0},50.0};
	materialStruct	YellowGreenBeardMaterial={{1.0,1.0,0.75,1.0},{0.8,0.8,0.5,1.0},{0.2,0.2,0.2,1.0},50.0};
	materialStruct	YellowGreenTailMaterial={{1.0,1.0,0.75,1.0},{0.8,0.8,0.5,1.0},{0.2,0.2,0.2,1.0},50.0};
	materialStruct	YellowGreenMouthMaterial={{0.03, 0.03, 0.03, 1.0},{0.25, 0.25, 0.25, 1.0},{0.07, 0.07, 0.07, 1.0},100.0};
	materialStruct	YellowGreenBeyeMaterial={{0.03, 0.03, 0.03, 1.0},{0.25, 0.25, 0.25, 1.0},{0.07, 0.07, 0.07, 1.0},100.0};
	materialStruct	YellowGreenWeyeMaterial={{0.9,0.9,0.9,1.0},{0.9,0.9,0.9,1.0},{0.0,0.0,0.0,1.0},50.0};

	materialStruct	GrassMaterial={{0.9,0.9,0.9,1.0},{0.0,0.8,0.0,1.0},{0.0,0.0,0.0,1.0},50.0};

	//set material of every part
	materialStruct *headMaterial;
	materialStruct *bodyMaterial;
	materialStruct *ulegMaterial;
	materialStruct *llegMaterial;
	materialStruct *hornMaterial;
	materialStruct *hairMaterial;
	materialStruct *beardMaterial;
	materialStruct *tailMaterial;
	materialStruct *mouthMaterial;
	materialStruct *beyeMaterial;
	materialStruct *weyeMaterial;
	materialStruct *grassMaterial;

void body(){
    glPushMatrix();
    glTranslatef(0.0,0.5*BODY_HEIGHT,0.0);
    glScalef(BODY_LENGTH,BODY_HEIGHT,BODY_WIDTH);
    glutSolidCube(1.0);
    glPopMatrix();
    return;
    }

void head(){
	 glPushMatrix();
	 glTranslatef(0, BODY_HEIGHT, BODY_LENGTH);
	 glutSolidCube(HEAD_LENGTH);
     glPopMatrix();
     return;
	}

void hair(){
	 glPushMatrix();
	 glTranslatef(0.0,1.3*BODY_HEIGHT,0.5625*BODY_WIDTH);
	 glScalef(10.0,1.0,10.0);
	 glutSolidCube(0.5);
	 glPopMatrix();
	 return;
	}

void beard(){
	glPushMatrix();
	glTranslatef(0.0,7.0,10.0);
	glRotatef(90,1.0,0.0,0.0);
    glutSolidCone(BEARD_RADIUS,BEARD_HEIGHT, 100, 100);
    glPopMatrix();
    return;
	}

void lower_leg()
{
    glPushMatrix();
    glRotatef(90, 1.0, 0.0, 0.0);
    gluDisk(p,0.0,LOWER_LEG_RADIUS,20,4);
    gluCylinder(p,LOWER_LEG_RADIUS,LOWER_LEG_RADIUS,LOWER_LEG_HEIGHT,100,100);
    glPopMatrix();
    return;
	}

void upper_leg()
{
    glPushMatrix();
    glTranslatef(0, -0.9*UPPER_LEG_HEIGHT, 0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(p,UPPER_LEG_RADIUS,UPPER_LEG_RADIUS,UPPER_LEG_HEIGHT,100,100);
    glPopMatrix();
    return;
	}

void tail()
{
	glPushMatrix();
	glRotatef(135,1.0,0.0,0.0);
	gluCylinder(p,TAIL_RADIUS,0.4*TAIL_RADIUS,TAIL_HEIGHT,100,100);
	glTranslatef(0.0,0.0,0.0);
	glPopMatrix();
	return;
	}

void right_eye1()
{
    glPushMatrix();
    glTranslatef(1.3,9.8,11.5);
    glutSolidCube(0.4);
    glPopMatrix();
    return;
	}

void left_eye1()
{
    glPushMatrix();
    glTranslatef(-1.3,9.8,11.5);
    glutSolidCube(0.4);
    glPopMatrix();
    return;
	}

void right_eye2()
{
	glPushMatrix();
    glTranslatef(1.2,9.8,11.3);
    glScalef(1.7,1.0,1.0);
	glutSolidCube(0.5);
	glPopMatrix();
	return;
	}

void left_eye2()
{
	glPushMatrix();
    glTranslatef(-1.2,9.8,11.3);
    glScalef(1.7,1.0,1.0);
	glutSolidCube(0.5);
	glPopMatrix();
	return;
	}

void mouth()
{
    glPushMatrix();
  	glTranslatef(0.0,8.0,11.5);
    glScalef(4.0,1.0,1.0);
    glutSolidCube(0.2);
    glPopMatrix();
    return;
	}

void left_horn()
{
    glPushMatrix();
  	glTranslatef(1.75,11.0,10.0);
  	glRotatef(-145,0.0,0.0,1.0);
  	glRotatef(-90,0.0,1.0,0.0);
    glutSolidCone(HORN_RADIUS,HORN_HEIGHT, 100, 100);
    glPopMatrix();
    return;
	}

void right_horn()
{
    glPushMatrix();
  	glTranslatef(-1.75,11.0,10.0);
  	glRotatef(-35,0.0,0.0,1.0);
  	glRotatef(-90,0.0,1.0,0.0);
    glutSolidCone(HORN_RADIUS,HORN_HEIGHT, 100, 100);
    glPopMatrix();
    return;
	}

void xyz()
{
	 glPushMatrix();
	 glutSolidCube(1);
	 glPopMatrix();
	 return;
}

//draw the spotlight and set the spotlight's emission color
void spotlight()
{
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3fv(source_color);
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
    glMaterialfv(GL_FRONT,GL_SHININESS,&material->shininess);//set shininess
    return;
}


void all()
{
 	glPushMatrix();
 	chooseMaterial(grassMaterial);
 	glTranslatef(0,-7.9,0);
 	glScalef(50,0.1,50);
	xyz();
	glPopMatrix();

	glTranslatef(currentLocation[0],currentLocation[2], currentLocation[1]);//all parts will translate
	glRotatef(theta[0], 0.0, 0.0, 1.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 1.0, 0.0, 0.0); //the axis of rotating can change

    	//make the body
		glPushMatrix();
		chooseMaterial(bodyMaterial);
	    glRotatef(theta[BODY], 1, 0, 0);
	    body();
	    glPopMatrix();

		//make the whole head
	    //make the head
	    glPushMatrix();
	    glRotatef(theta[BODY], 1, 0, 0);
	    chooseMaterial(headMaterial);
	    glRotatef(theta[HD], 0, 0, 1);
	    head();
	    //make the hair
	    chooseMaterial(hairMaterial);
	    hair();
	  	//make the right horn
	    chooseMaterial(hornMaterial);
	  	right_horn();
	  	//make the left horn
	  	chooseMaterial(hornMaterial);
	  	left_horn();
	    //make the mouth
	  	chooseMaterial(mouthMaterial);
	  	mouth();
	  	//make the beard
	  	chooseMaterial(beardMaterial);
	  	beard();
	    //make the left eye
	  	chooseMaterial(beyeMaterial);
	    left_eye1();
	    chooseMaterial(weyeMaterial);
	    left_eye2();
	     //make the right eye
	    chooseMaterial(beyeMaterial);
	    right_eye1();
	    chooseMaterial(weyeMaterial);
	    right_eye2();
	    glPopMatrix();

	    //make the right front upper and lower leg
	    glPushMatrix();
	    glRotatef(theta[BODY], 1, 0, 0);
	    chooseMaterial(ulegMaterial);
	    glTranslatef(-0.25*BODY_LENGTH,0.0,0.30*BODY_WIDTH);
	    glRotatef(theta[FRU], 1, 0, 0);
	    upper_leg();
	    chooseMaterial(llegMaterial);
	    glTranslatef(0, -0.9*UPPER_LEG_HEIGHT, 0);
	    glRotatef(theta[FRL], 1, 0, 0);
	    lower_leg();
	    glPopMatrix();

		//make the left front upper and lower leg
	    glPushMatrix();
	    glRotatef(theta[BODY], 1, 0, 0);
	    chooseMaterial(ulegMaterial);
	    glTranslatef(0.25*BODY_LENGTH,0.0,0.30*BODY_WIDTH);
	    glRotatef(theta[FLU], 1, 0, 0);
	    upper_leg();
	    chooseMaterial(llegMaterial);
	    glTranslatef(0, -0.9*UPPER_LEG_HEIGHT, 0);
	    glRotatef(theta[FLL], 1, 0, 0);
	    lower_leg();
	    glPopMatrix();

		//make the right back upper and lower leg
	    glPushMatrix();
	    glRotatef(theta[BODY], 1, 0, 0);
	    chooseMaterial(ulegMaterial);
	    glTranslatef(-0.25*BODY_LENGTH,0.0,-0.30*BODY_WIDTH);
	    glRotatef(theta[BRU], 1, 0, 0);
	    upper_leg();
	    glColor3f(1.0,1.0,1.0);
	    glTranslatef(0, -0.9*UPPER_LEG_HEIGHT, 0);
	    chooseMaterial(llegMaterial);
	    lower_leg();
	    glPopMatrix();

		//make the left back upper and lower leg
	    glPushMatrix();
	    glRotatef(theta[BODY], 1, 0, 0);
	    chooseMaterial(ulegMaterial);
	    glTranslatef(0.25*BODY_LENGTH,0.0,-0.30*BODY_WIDTH);
	    glRotatef(theta[BLU], 1, 0, 0);
	    upper_leg();
	    chooseMaterial(llegMaterial);
	    glTranslatef(0, -0.9*UPPER_LEG_HEIGHT, 0);
	    glRotatef(theta[BLL], 1, 0, 0);
	    lower_leg();
	    glPopMatrix();

	    //make the tail
	    glPushMatrix();
	    glRotatef(theta[BODY], 1, 0, 0);
	    chooseMaterial(tailMaterial);
	    glTranslatef(0.0,6.0,-7.2);
	    glRotatef(theta[TL], 0, 1, 0);
	    tail();
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
    //glRotatef(-theta[ALL], 0, 1, 0);//rotate the light with reverse direction
    glLightfv(GL_LIGHT0, GL_AMBIENT, Lighting->ambient);//set current light ambient
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Lighting->diffuse);//set current light diffuse
    glLightfv(GL_LIGHT0, GL_SPECULAR, Lighting->specular);//set current specular
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);//set current light direction
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff_angle);//set current light cutoff angle
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glTranslatef(-RIGHTB*2/3,TOPB*2/3,FARB*2/3);//move the spot light source to where spot light is
    spotlight();//draw the spot light source

    //set the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.0,0.5,1.0,0.0,0.0,0.0,0.0,1.0,0.0);//isometric view

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);  //gray ambient light
    all();
    glutSwapBuffers();//double buffer
    return;
}

void movFunc(GLint order, GLfloat MaxAngle, GLfloat MinAngle)
{
    if (theta[order]>=MaxAngle)
        movingDirection[order]=-1;
    if (theta[order]<=MinAngle)
        movingDirection[order]=1;
    return;
}

//running and rotating

void myidle()
{
	   if (translate_state==GL_TRUE)
	    {
		   // the object will run to a different place when you click on the running button
	    	if (PATH == 1) {
	    		if (currentLocation[1] >= 12) {
	    					PATH++;
	    				}
	    		else {

	    					currentLocation[1] += 0.1;
	    				}
	    	}

	    	else if (PATH == 2) {
	    		if(currentLocation[0]>=0){

	    		if(RT==GL_TRUE){
	    				 currentLocation[2] += jump_TO_WHERE*0.1;
	    				if( currentLocation[2]>=7.3) {
	    					 jump_TO_WHERE=-1;
	    				}

	    				if(currentLocation[2]<=0) {
	    					jump_TO_WHERE=1;
	    					RT = GL_FALSE;
	    				}

	    		}
	    		}

	    			if (currentLocation[0] >= 15) {
	    					PATH++;
	   	    			 }



	    		else{
	    					currentLocation[0] += 0.1;
	    				}
	    	}

	    	else if (PATH == 3) {
	    		if (currentLocation[1] <= -10) {
	    					PATH++;
	    				}
	    		else {

	    					currentLocation[1] -= 0.1;
	    				}
	    			}

	    	else if (PATH == 4) {
	    		if (currentLocation[0] <= -15) {
	    			RT=GL_TRUE;
	    			PATH=PATH-3;

	    				}
	    		else {

	    					currentLocation[0] -= 0.1;
	    				}
	    			}
	    }
    //the body, head, tail and leg of the sheep will move differently
    if (moving_state==GL_TRUE)
    {
        theta[BODY]+=movBODYv*movingDirection[BODY];
        movFunc(BODY,3,-3);
        theta[FLU]+=movFLUv*movingDirection[FLU];
        movFunc(FLU,30,-30);
        theta[FLL]+=movFLLv*movingDirection[FLL];
        movFunc(FLL,30,-0);
        theta[FRU]+=movFRUv*movingDirection[FRU];
        movFunc(FRU,30,-30);
        theta[FRL]+=movFRLv*movingDirection[FRL];
        movFunc(FRL,30,-0);
        theta[BLU]+=movBLUv*movingDirection[BLU];
        movFunc(BLU,30,-30);
        theta[BLL]+=movBLLv*movingDirection[BLL];
        movFunc(BLL,30,0);
        theta[BRU]+=movBRUv*movingDirection[BRU];
        movFunc(BRU,30,-30);
        theta[BRL]+=movBRLv*movingDirection[BRL];
        movFunc(BRL,30,0);
        theta[HD]+=movHDv*movingDirection[HD];
        movFunc(HD,10,-10);
        theta[TL]+=movTLv*movingDirection[TL];
        movFunc(TL,40,-40);
    }
    //all parts of the sheep can rotate
    if (rotate_state==GL_TRUE)
    {
        theta[ALL]+=rotateSpeed;
        if (theta[ALL]>360)
            theta[ALL]=0;
    }
    glutPostRedisplay();
    return;
}

//using mouse function to control animation state
void mymouse(GLint button,GLint state,GLint x,GLint y)
{
    if (button==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        moving_state=!moving_state;
        rotate_state=!rotate_state;
        translate_state=!translate_state;
    }
    return;
}

//using menu to change materials

//using the key(up, left and right) to control the axis of rotating
void specialkey(int key, int x, int y) {
   switch (key) {
   case GLUT_KEY_LEFT:
	ALL = 0;
	break;
  case GLUT_KEY_UP:
	ALL = 1;
	break;
   case GLUT_KEY_RIGHT:
	ALL = 2;
	break;
  }
}

void mymenu(int id)
{
    if (id==1)
    {
        headMaterial=&GrayHeadMaterial;
        bodyMaterial=&GrayBodyMaterial;
        ulegMaterial=&GrayUlegMaterial;
        llegMaterial=&GrayLlegMaterial;
        hornMaterial=&GrayHornMaterial;
        hairMaterial=&GrayHairMaterial;
        beardMaterial=&GrayBeardMaterial;
        tailMaterial=&GrayTailMaterial;
        mouthMaterial=&GrayMouthMaterial;
        beyeMaterial=&GrayBeyeMaterial;
        weyeMaterial=&GrayWeyeMaterial;
        return;
    }
    if (id==2)
    {
        headMaterial=&RedBlueHeadMaterial;
        bodyMaterial=&RedBlueBodyMaterial;
        ulegMaterial=&RedBlueUlegMaterial;
        llegMaterial=&RedBlueLlegMaterial;
        hornMaterial=&RedBlueHornMaterial;
        hairMaterial=&RedBlueHairMaterial;
        beardMaterial=&RedBlueBeardMaterial;
        tailMaterial=&RedBlueTailMaterial;
        mouthMaterial=&RedBlueMouthMaterial;
        beyeMaterial=&RedBlueBeyeMaterial;
        weyeMaterial=&RedBlueWeyeMaterial;
        return;
    }
    if (id==3)
    {
        headMaterial=&YellowGreenHeadMaterial;
        bodyMaterial=&YellowGreenBodyMaterial;
        ulegMaterial=&YellowGreenUlegMaterial;
        llegMaterial=&YellowGreenLlegMaterial;
        hornMaterial=&YellowGreenHornMaterial;
        hairMaterial=&YellowGreenHairMaterial;
        beardMaterial=&YellowGreenBeardMaterial;
        tailMaterial=&YellowGreenTailMaterial;
        mouthMaterial=&YellowGreenMouthMaterial;
        beyeMaterial=&YellowGreenBeyeMaterial;
        weyeMaterial=&YellowGreenWeyeMaterial;
        return;
    }
    return;
}

//create menu
int mm;
void createMenu()
{
    mm=glutCreateMenu(mymenu);
    glutAddMenuEntry("I'm Mr.Black",1);
    glutAddMenuEntry("I'm Mr.White",2);
    glutAddMenuEntry("I'm Mr.Normal",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    return;
}

//initializing
void myinit()
{
    glClearColor(0.9,0.9,0.9,1.0);//background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    p=gluNewQuadric();

    Lighting=&whiteLighting;
    source_color[0]=1.0;
    source_color[1]=1.0;
    source_color[2]=1.0;
    cutoff_angle=35;

    headMaterial=&GrayHeadMaterial;
    bodyMaterial=&GrayBodyMaterial;
    ulegMaterial=&GrayUlegMaterial;
    llegMaterial=&GrayLlegMaterial;
    hornMaterial=&GrayHornMaterial;
    hairMaterial=&GrayHairMaterial;
    beardMaterial=&GrayBeardMaterial;
    tailMaterial=&GrayTailMaterial;
    mouthMaterial=&GrayMouthMaterial;
    beyeMaterial=&GrayBeyeMaterial;
    weyeMaterial=&GrayWeyeMaterial;
    grassMaterial=&GrassMaterial;

    return;
}

//make sure the whole object appears in the middle of the window and stay original ratio when reshape
void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w<=h)
            glOrtho(LEFTB,RIGHTB,BOTTOMB*(GLfloat)h/(GLfloat)w,TOPB*(GLfloat)h/(GLfloat)w,NEARB,FARB);
        else
            glOrtho(LEFTB*(GLfloat)w/(GLfloat)h,RIGHTB*(GLfloat)w/(GLfloat)h,BOTTOMB,TOPB,NEARB,FARB);
}
//main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,800);
    glutCreateWindow("My Little Sheep");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(myidle);
    glutMouseFunc(mymouse);
    glutSpecialFunc(specialkey);
    glEnable(GL_DEPTH_TEST);
    myinit();
    createMenu();
    glutMainLoop();
}
