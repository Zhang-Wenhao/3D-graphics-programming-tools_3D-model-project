/*
 * lab8_2.c
 *
 *  Created on: 2018Äê4ÔÂ23ÈÕ
 *      Author: 40360
 */

#include <stdlib.h>
#include <GL/glut.h>

#define TORSO_WIDTH 4.0
#define TORSO_HEIGHT 2.0
#define TORSO_DEPTH 2.0
#define HEAD_WIDTH 2.0
#define HEAD_HEIGHT 1.0
#define HEAD_DEPTH 1.0
#define LOWER_ARM_HEIGHT 2.5
#define LOWER_ARM_WIDTH 0.6
#define UPPER_ARM_HEIGHT 1.0
#define UPPER_ARM_WIDTH 0.4
#define LOWER_LEG_HEIGHT 3.0
#define LOWER_LEG_WIDTH 0.6
#define UPPER_LEG_HEIGHT 2.0
#define UPPER_LEG_WIDTH 0.4
#define FOOT_WIDTH 1.0
#define FOOT_HEIGHT 0.2
#define ANTENNA_RADIUS 0.1
#define ANTENNA_HEIGHT 1.0
#define SPHERE_RADIUS 0.3

#define TORSO 0
#define HEAD 1
#define LAX 2
#define RAX 3
#define LUAX 4
#define LLAX 5
#define RUAX 6
#define RLAX 7
#define LULX 8
#define LLLX 9
#define RULX 10
#define RLLX 11
#define OBJECT 12
#define LIGHT 13
#define SPHERE 14
GLfloat theta[15] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; //set the initial shape and orientation of the object
GLint TORSO_direction = 1;
GLint HEAD_direction = 1;
GLint LAX_direction = 1;
GLint RAX_direction = 1;
GLint LUAX_direction = 1;
GLint LLAX_direction = 1;
GLint RUAX_direction = 1;
GLint RLAX_direction = 1;
GLint LULX_direction = 1;
GLint LLLX_direction = 1;
GLint RULX_direction = 1;
GLint RLLX_direction = 1;

GLfloat spherecolor[3][3] = {{1.0, 1.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 0.0, 0.0}};
GLint color_id = 0;

GLboolean ifanimating = GL_FALSE; //set "not animating" to be the initial state

GLint menu_id = 0;

GLUquadricObj *p;   // pointer to quadric object

// shading ...
typedef struct materialStruct {
  GLfloat TORSOambient[4];
  GLfloat TORSOdiffuse[4];
  GLfloat TORSOspecular[4];
  GLfloat TORSOshininess;
  GLfloat HEADambient[4];
  GLfloat HEADdiffuse[4];
  GLfloat HEADspecular[4];
  GLfloat HEADshininess;
  GLfloat ANTENNAambient[4];
  GLfloat ANTENNAdiffuse[4];
  GLfloat ANTENNAspecular[4];
  GLfloat ANTENNAshininess;
  GLfloat UAambient[4];
  GLfloat UAdiffuse[4];
  GLfloat UAspecular[4];
  GLfloat UAshininess;
  GLfloat LAambient[4];
  GLfloat LAdiffuse[4];
  GLfloat LAspecular[4];
  GLfloat LAshininess;
  GLfloat ULambient[4];
  GLfloat ULdiffuse[4];
  GLfloat ULspecular[4];
  GLfloat ULshininess;
  GLfloat LLambient[4];
  GLfloat LLdiffuse[4];
  GLfloat LLspecular[4];
  GLfloat LLshininess;
  GLfloat FOOTambient[4];
  GLfloat FOOTdiffuse[4];
  GLfloat FOOTspecular[4];
  GLfloat FOOTshininess;
} materialStruct;

//properties of the Optimus Prime
materialStruct OptimusPrimeMaterials = {
   {0.88, 0.12, 0.03, 1.0},
   {0.91, 0.11, 0.11, 1.0},
   {0.59, 0.21, 0.21, 1.0},
   27.8,
   {0.13, 0.22, 0.83, 1.0},
   {0.18, 0.17, 0.91, 1.0},
   {0.19, 0.21, 0.81, 1.0},
   27.8,
   {0.88, 0.88, 0.88, 1.0},
   {0.98, 0.97, 0.91, 1.0},
   {0.79, 0.81, 0.81, 1.0},
   27.8,
   {0.88, 0.88, 0.88, 1.0},
   {0.78, 0.77, 0.81, 1.0},
   {0.79, 0.81, 0.81, 1.0},
   27.8,
   {0.88, 0.12, 0.03, 1.0},
   {0.48, 0.11, 0.11, 1.0},
   {0.99, 0.21, 0.21, 1.0},
   27.8,
   {0.88, 0.88, 0.88, 1.0},
   {0.78, 0.77, 0.81, 1.0},
   {0.79, 0.81, 0.81, 1.0},
   27.8,
   {0.13, 0.22, 0.83, 1.0},
   {0.18, 0.17, 0.51, 1.0},
   {0.19, 0.21, 0.91, 1.0},
   27.8,
   {0.13, 0.22, 0.83, 1.0},
   {0.08, 0.07, 0.01, 1.0},
   {0.19, 0.21, 0.91, 1.0},
   27.8,
};

//properties of the Bumblebee
materialStruct BumblebeeMaterials = {
   {0.93, 0.90, 0.0, 1.0},
   {0.96, 1.0, 0.0, 1.0},
   {0.0, 0.0, 0.0, 1.0},
   32.0,
   {0.53, 0.50, 0.0, 1.0},
   {0.86, 0.90, 0.0, 1.0},
   {0.18, 0.16, 0.0, 1.0},
   12.0,
   {0.03, 0.03, 0.0, 1.0},
   {0.06, 0.05, 0.0, 1.0},
   {0.08, 0.06, 0.0, 1.0},
   32.0,
   {0.03, 0.03, 0.0, 1.0},
   {0.26, 0.25, 0.20, 1.0},
   {0.08, 0.06, 0.0, 1.0},
   32.0,
   {0.53, 0.50, 0.0, 1.0},
   {0.86, 0.90, 0.0, 1.0},
   {0.88, 0.86, 0.0, 1.0},
   32.0,
   {0.03, 0.03, 0.0, 1.0},
   {0.26, 0.25, 0.20, 1.0},
   {0.08, 0.06, 0.0, 1.0},
   32.0,
   {0.53, 0.50, 0.0, 1.0},
   {0.66, 0.70, 0.0, 1.0},
   {0.68, 0.66, 0.0, 1.0},
   32.0,
   {0.03, 0.03, 0.0, 1.0},
   {0.26, 0.25, 0.20, 1.0},
   {0.08, 0.06, 0.0, 1.0},
   32.0
};

//properties of the Megatron
materialStruct MegatronMaterials = {
   {0.8, 0.8, 0.8, 1.0},
   {0.7, 0.7, 0.7, 1.0},
   {0.7, 0.7, 0.7, 1.0},
   100.0,
   {1.0, 1.0, 1.0, 1.0},
   {1.0, 1.0, 1.0, 1.0},
   {0.0, 0.0, 0.0, 1.0},
   100.0,
   {0.88, 0.12, 0.03, 1.0},
   {0.48, 0.11, 0.11, 1.0},
   {0.99, 0.21, 0.21, 1.0},
   100.0,
   {0.3, 0.1, 0.1, 1.0},
   {0.3, 0.1, 0.1, 1.0},
   {0.0, 0.0, 0.0, 1.0},
   100.0,
   {0.3, 0.3, 0.3, 1.0},
   {0.5, 0.5, 0.5, 1.0},
   {0.3, 0.3, 0.3, 1.0},
   100.0,
   {0.5, 0.5, 0.5, 1.0},
   {0.7, 0.7, 0.7, 1.0},
   {0.0, 0.0, 0.0, 1.0},
   100.0,
   {0.03, 0.03, 0.03, 1.0},
   {0.25, 0.25, 0.25, 1.0},
   {0.07, 0.07, 0.07, 1.0},
   100.0,
   {0.88, 0.12, 0.03, 1.0},
   {0.91, 0.11, 0.11, 1.0},
   {0.59, 0.21, 0.21, 1.0},
   100.0
};

materialStruct *currentMaterials;

typedef struct lightingStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat cutoff;
} lightingStruct;

//properties of the white lighting
lightingStruct whiteLighting = {
   {0.0, 0.0, 0.0, 1.0},
   {1.0, 1.0, 1.0, 1.0},
   {1.0, 1.0, 1.0, 1.0},
   30.0
};

//properties of the yellow lighting
lightingStruct yellowLighting = {
   {0.0, 0.0, 0.0, 1.0},
   {1.0, 1.0, 0.0, 1.0},
   {1.0, 1.0, 0.0, 1.0},
   22.5
};

//properties of the red lighting
lightingStruct redLighting = {
   {0.0, 0.0, 0.0, 1.0},
   {1.0, 0.0, 0.0, 1.0},
   {1.0, 0.0, 0.0, 1.0},
   15.0
};

lightingStruct *currentLighting;

/* codes for every part of the object*/
void torso()
{
     glPushMatrix();
     glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials -> TORSOambient);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials -> TORSOdiffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials -> TORSOspecular);
     glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials -> TORSOshininess);
     glTranslatef(0.0, 0.5*TORSO_HEIGHT, 0.0);
     glScalef(TORSO_WIDTH, TORSO_HEIGHT, TORSO_DEPTH);
     glutSolidCube(1.0);
     glPopMatrix();
}

void head()
{
     glPushMatrix();
     glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials -> HEADambient);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials -> HEADdiffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials -> HEADspecular);
     glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials -> HEADshininess);
     glTranslatef(0.0, 0.5*HEAD_HEIGHT, 0.0);
     glScalef(HEAD_WIDTH, HEAD_HEIGHT, HEAD_DEPTH);
     glutSolidCube(1.0);
     glPopMatrix();
}

void antenna()
{
     glPushMatrix();
     glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials -> ANTENNAambient);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials -> ANTENNAdiffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials -> ANTENNAspecular);
     glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials -> ANTENNAshininess);
     glRotatef (-90.0, 1.0, 0.0, 0.0);
     gluCylinder(p, ANTENNA_RADIUS, ANTENNA_RADIUS, ANTENNA_HEIGHT, 15, 15);
     glPopMatrix();
}

void lower_arm()
{
     glPushMatrix();
     glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials -> LAambient);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials -> LAdiffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials -> LAspecular);
     glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials -> LAshininess);
     glTranslatef(0.0, -0.5*LOWER_ARM_HEIGHT, 0.0);
     glScalef(LOWER_ARM_WIDTH, LOWER_ARM_HEIGHT, LOWER_ARM_WIDTH);
     glutSolidCube(1.0);
     glPopMatrix();
}

void upper_arm()
{
     glPushMatrix();
     glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials -> UAambient);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials -> UAdiffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials -> UAspecular);
     glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials -> UAshininess);
     glTranslatef(0.0, -0.5*UPPER_ARM_HEIGHT, 0.0);
     glScalef(UPPER_ARM_WIDTH, UPPER_ARM_HEIGHT, UPPER_ARM_WIDTH);
     glutSolidCube(1.0);
     glPopMatrix();
}

void lower_leg()
{
     glPushMatrix();
     glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials -> LLambient);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials -> LLdiffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials -> LLspecular);
     glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials -> LLshininess);
     glTranslatef(0.0, -0.5*LOWER_LEG_HEIGHT, 0.0);
     glScalef(LOWER_LEG_WIDTH, LOWER_LEG_HEIGHT, LOWER_LEG_WIDTH);
     glutSolidCube(1.0);
     glPopMatrix();
}

void upper_leg()
{
     glPushMatrix();
     glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials -> ULambient);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials -> ULdiffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials -> ULspecular);
     glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials -> ULshininess);
     glTranslatef(0.0, -0.5*UPPER_LEG_HEIGHT, 0.0);
     glScalef(UPPER_LEG_WIDTH, UPPER_LEG_HEIGHT, UPPER_LEG_WIDTH);
     glutSolidCube(1.0);
     glPopMatrix();
}

void foot()
{
     glPushMatrix();
     glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials -> FOOTambient);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials -> FOOTdiffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials -> FOOTspecular);
     glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials -> FOOTshininess);
     glTranslatef(0.0, -0.5*FOOT_HEIGHT, 0.0);
     glScalef(FOOT_WIDTH, FOOT_HEIGHT, FOOT_WIDTH);
     glutSolidCube(1.0);
     glPopMatrix();
}

void sphere() //codes for the visual representation of the spotlight
{
     glPushMatrix();
     glDisable(GL_LIGHTING);
     glColor3fv(spherecolor[color_id]);
     gluSphere(p, SPHERE_RADIUS, 16, 16);
     glEnable(GL_LIGHTING);
     glPopMatrix();
}

void object()
{
     glTranslatef(0.0, 1.0, 0.0);
     glRotatef(theta[OBJECT], 0.0, 1.0, 0.0); //rotate the whole object
     glPushMatrix();
     glRotatef(theta[TORSO], 1.0, 0.0, 0.0);
     torso();
     glPushMatrix(); //save present model-view matrix
     glTranslatef(0.0, TORSO_HEIGHT + 0.05, 0.0); //update model-view matrix for head
     glRotatef(theta[HEAD], 0.0, 1.0, 0.0);
     head();
     glPushMatrix(); //save present model-view matrix
     glTranslatef(-HEAD_WIDTH/2 + ANTENNA_RADIUS + 0.5, HEAD_HEIGHT, 0.0); //update model-view matrix for left antenna
     glRotatef(theta[LAX], 1.0, 0.0, 0.0);
     antenna();
     glPopMatrix(); //recover original model-view matrix
     glPushMatrix(); //save present model-view matrix
     glTranslatef(HEAD_WIDTH/2 - ANTENNA_RADIUS - 0.5, HEAD_HEIGHT, 0.0); //update model-view matrix for right antenna
     glRotatef(theta[RAX], 1.0, 0.0, 0.0);
     antenna();
     glPopMatrix(); //recover original model-view matrix
     glPopMatrix(); //recover original model-view matrix
     glPushMatrix(); //save it again
     glTranslatef(-TORSO_WIDTH/2 - UPPER_ARM_WIDTH/2 - 0.1, TORSO_HEIGHT, 0.0); //update model-view matrix for left upper arm
     glRotatef(theta[LUAX], 1.0, 0.0, 0.0);
     upper_arm();
     glTranslatef(0.0, -UPPER_ARM_HEIGHT, 0.0); //update model-view matrix for left lower arm
     glRotatef(theta[LLAX], 1.0, 0.0, 0.0);
     lower_arm();
     glPopMatrix(); //recover original model-view matrix
     glPushMatrix(); //save it again
     glTranslatef(TORSO_WIDTH/2 + UPPER_ARM_WIDTH/2 + 0.1, TORSO_HEIGHT, 0.0); //update model-view matrix for right upper arm
     glRotatef(theta[RUAX], 1.0, 0.0, 0.0);
     upper_arm();
     glTranslatef(0.0, -UPPER_ARM_HEIGHT, 0.0); //update model-view matrix for right lower arm
     glRotatef(theta[RLAX], 1.0, 0.0, 0.0);
     lower_arm();
     glPopMatrix(); //recover original model-view matrix
     glPushMatrix(); //save it again
     glTranslatef(-TORSO_WIDTH/2 + UPPER_LEG_WIDTH/2 + 1.2, 0.0, 0.0); //update model-view matrix for left upper leg
     glRotatef(theta[LULX], 1.0, 0.0, 0.0);
     upper_leg();
     glTranslatef(0.0, -UPPER_LEG_HEIGHT, 0.0); //update model-view matrix for left lower leg
     glRotatef(theta[LLLX], 1.0, 0.0, 0.0);
     lower_leg();
     glTranslatef(0.0, -LOWER_LEG_HEIGHT, 0.0); //update model-view matrix for left foot
     foot();
     glPopMatrix(); //recover original model-view matrix
     glPushMatrix(); //save it again
     glTranslatef(TORSO_WIDTH/2 - UPPER_LEG_WIDTH/2 - 1.2, 0.0, 0.0); //update model-view matrix for right upper leg
     glRotatef(theta[RULX], 1.0, 0.0, 0.0);
     upper_leg();
     glTranslatef(0.0, -UPPER_LEG_HEIGHT, 0.0); //update model-view matrix for right lower leg
     glRotatef(theta[RLLX], 1.0, 0.0, 0.0);
     lower_leg();
     glTranslatef(0.0, -LOWER_LEG_HEIGHT, 0.0); //update model-view matrix for right foot
     foot();
     glPopMatrix();
     glPopMatrix();
}

void display()
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     float position[] = {4.5f, 1.0f, 4.5f, 1.0f};
     float direction[] = {-1.0f, 0.0f, -1.0f};
     glEnable(GL_LIGHTING); //allow lighting
     glEnable(GL_LIGHT0); //allow the light source LIGHT0
     glEnable(GL_NORMALIZE); //allow for autonormallization at a performance penalty
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     glRotatef(theta[LIGHT], 0.0, 1.0, 0.0); //rotate the spotlight
     glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting -> ambient); //add ambient light to the light source
     glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting -> diffuse); //add diffuse light to the light source
     glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting -> specular); //add specular light to the light source
     glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, currentLighting -> cutoff); //set a cutoff angle
     glLightfv(GL_LIGHT0, GL_POSITION, position); //fix the light source
     glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction); //set the direction of the light
     glLightf(GL_LIGHT0 , GL_SPOT_EXPONENT, 1.0); //sey the concentration of the light
     float model_ambient[] = {0.4f, 0.4f, 0.4f, 1.0f}; //light model properties
     int model_two_side = 1; //0=2sided, 1=1sided
     int viewpoint = 0;      //0=infiniteViewpoint, 1=localViewpoint
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);  //small white ambient light
     glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, viewpoint); //local and infinite viewpoint
     glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1); //only outside face because we don't see the inside of the object
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //create an isometric view of the object
     object();
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     glRotatef(theta[SPHERE], 0.0, 1.0, 0.0); //rotate the spotlight sphere
     glTranslatef(4.5, 1.0, 4.5); //translate the sphere to the light position
     sphere();
     glutSwapBuffers();
}

void reshape(int w, int h)
{
     glViewport(0, 0, w, h); //let the image be shown in the window size
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     if (h <= w)
        glOrtho(-7.0*w/h, 7.0*w/h, -7.0, 7.0, -10.0, 10.0);
     else
        glOrtho(-7.0, 7.0, -7.0*h/w, 7.0*h/w, -10.0, 10.0); //make sure the whole object appears in the middle of the window and preserves its shape and proportions even in the event that the window¡¯s aspect ratio has been changed
}

void idle() //codes for animation
{
     if (ifanimating) {                          //codes for bending
        if (HEAD_direction > 0) {
           theta[HEAD] += 0.03;
           if (theta[HEAD] > 60) {
              HEAD_direction = -1;
              theta[HEAD] -= 0.03;
           }
        }
        else {
           theta[HEAD] -= 0.03;
           if (theta[HEAD] < -60) {
              HEAD_direction = 1;
              theta[HEAD] += 0.03;
           }
        }
        if (LAX_direction > 0) {
           theta[LAX] += 0.03;
           if (theta[LAX] > 60) {
              LAX_direction = -1;
              theta[LAX] -= 0.03;
           }
        }
        else {
           theta[LAX] -= 0.03;
           if (theta[LAX] < -60) {
              LAX_direction = 1;
              theta[LAX] += 0.03;
           }
        }
        if (RAX_direction > 0) {
           theta[RAX] += 0.03;
           if (theta[RAX] > 60) {
              RAX_direction = -1;
              theta[RAX] -= 0.03;
           }
        }
        else {
           theta[RAX] -= 0.03;
           if (theta[RAX] < -60) {
              RAX_direction = 1;
              theta[RAX] += 0.03;
           }
        }
        if (LUAX_direction > 0) {
           theta[LUAX] -= 0.03;
           if (theta[LUAX] < -60) {
              LUAX_direction = -1;
              theta[LUAX] += 0.03;
           }
        }
        else {
           theta[LUAX] += 0.03;
           if (theta[LUAX] > 60) {
              LUAX_direction = 1;
              theta[LUAX] -= 0.03;
           }
        }
        if (LLAX_direction > 0) {
           theta[LLAX] -= 0.03;
           if (theta[LLAX] < -60) {
              LLAX_direction = -1;
              theta[LLAX] += 0.03;
           }
        }
        else {
           theta[LLAX] += 0.03;
           if (theta[LLAX] > 60) {
              LLAX_direction = 1;
              theta[LLAX] -= 0.03;
           }
        }
        if (RUAX_direction > 0) {
           theta[RUAX] += 0.03;
           if (theta[RUAX] > 60) {
              RUAX_direction = -1;
              theta[RUAX] -= 0.03;
           }
        }
        else {
           theta[RUAX] -= 0.03;
           if (theta[RUAX] < -60) {
              RUAX_direction = 1;
              theta[RUAX] += 0.03;
           }
        }
        if (RLAX_direction > 0) {
           theta[RLAX] += 0.03;
           if (theta[RLAX] > 60) {
              RLAX_direction = -1;
              theta[RLAX] -= 0.03;
           }
        }
        else {
           theta[RLAX] -= 0.03;
           if (theta[RLAX] < -60) {
              RLAX_direction = 1;
              theta[RLAX] += 0.03;
           }
        }
        if (LULX_direction > 0) {
           theta[LULX] += 0.03;
           if (theta[LULX] > 60) {
              LULX_direction = -1;
              theta[LULX] -= 0.03;
           }
        }
        else {
           theta[LULX] -= 0.03;
           if (theta[LULX] < -60) {
              LULX_direction = 1;
              theta[LULX] += 0.03;
           }
        }
        if (LLLX_direction > 0) {
           theta[LLLX] += 0.045;
           if (theta[LLLX] > 90) {
              LLLX_direction = -1;
              theta[LLLX] -= 0.045;
           }
        }
        else {
           theta[LLLX] -= 0.045;
           if (theta[LLLX] < 0) {
              LLLX_direction = 1;
              theta[LLLX] += 0.045;
           }
        }
        if (RULX_direction > 0) {
           theta[RULX] -= 0.03;
           if (theta[RULX] < -60) {
              RULX_direction = -1;
              theta[RULX] += 0.03;
           }
        }
        else {
           theta[RULX] += 0.03;
           if (theta[RULX] > 60) {
              RULX_direction = 1;
              theta[RULX] -= 0.03;
           }
        }
        if (RLLX_direction > 0) {
           theta[RLLX] += 0.045;
           if (theta[RLLX] > 90) {
              RLLX_direction = -1;
              theta[RLLX] -= 0.045;
           }
        }
        else {
           theta[RLLX] -= 0.045;
           if (theta[RLLX] < 0) {
              RLLX_direction = 1;
              theta[RLLX] += 0.045;
           }
        }
        theta[OBJECT] += 0.02;                           //codes for rotation of the object
        if (theta[OBJECT] > 360) theta[OBJECT] -= 360;
        theta[LIGHT] -= 0.02;                           //codes for rotation of the spotlight
        if (theta[LIGHT] < -360) theta[LIGHT] += 360;
        theta[SPHERE] -= 0.02;                           //codes for rotation of the spotlight sphere
        if (theta[SPHERE] < -360) theta[SPHERE] += 360;
     }
     glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
     if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
        ifanimating = !ifanimating; //chage the value of ifanimating to control the animation when click the left button
}

void menu(int id)
{
     if (id == 1)
        currentMaterials = &OptimusPrimeMaterials;
     if (id == 2)
        currentMaterials = &BumblebeeMaterials;
     if (id == 3)
        currentMaterials = &MegatronMaterials;
}

void key(unsigned char k, int x, int y)
{
     switch(k) {
     //press w to chage the light to white
     case 'w':
      currentLighting = &whiteLighting;
      color_id = 0;
	  break;
     //press y to chage the light to yellow
     case 'y':
	  currentLighting = &yellowLighting;
	  color_id = 1;
	  break;
     //press r to chage the light to red
     case 'r':
	  currentLighting = &redLighting;
	  color_id = 2;
	  break;
	  //press W to chage the light to white
     case 'W':
      currentLighting = &whiteLighting;
      color_id = 0;
	  break;
     //press Y to chage the light to yellow
     case 'Y':
	  currentLighting = &yellowLighting;
	  color_id = 1;
	  break;
     //press R to chage the light to red
     case 'R':
	  currentLighting = &redLighting;
	  color_id = 2;
	  break;
   }
}

void init()
{
     currentMaterials = &OptimusPrimeMaterials; //set the initial materials of the object
     currentLighting = &whiteLighting; //set the initial type of lighting
     glClearColor(0.6f, 0.7f, 0.8f, 1.0f);
     p = gluNewQuadric();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Transformers");
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST); /* Enable hidden-surface removal */
   	glutReshapeFunc(reshape);
    glutMouseFunc(mouse); //call the mouse function
    glutKeyboardFunc(key); //call the key function
    glutIdleFunc(idle); //call the idle function
    menu_id = glutCreateMenu(menu); //creat a menu
	glutAddMenuEntry("Optimus Prime", 1); //set options on the menu (triggers for different types of materials)
	glutAddMenuEntry("Bumblebee", 2);
	glutAddMenuEntry("Megatron", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON); //attach the menu to right button of the mouse
    init();
    glutMainLoop();
}



