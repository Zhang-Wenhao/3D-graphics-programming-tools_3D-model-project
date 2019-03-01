/*
 * lab8_1.c
 *
 *  Created on: 2018Äê4ÔÂ23ÈÕ
 *      Author: 40360
 */
#include <stdlib.h>
#include <GL/glut.h>


#define BODY_HEIGHT 5.0
#define BODY_WIDTH 1.5
#define BODY_LENGTH 3.0

#define HEAD_RADIUS 1.0

#define CAP_HEIGHT 1.4
#define CAP_RADIUS 2.0

#define UPPER_LEG_HEIGHT 2.5
#define UPPER_LEG_RADIUS 0.65

#define LOWER_LEG_HEIGHT 3.5
#define LOWER_LEG_RADIUS 0.5

#define UPPER_ARM_HEIGHT  2.0
#define UPPER_ARM_RADIUS  0.5

#define LOWER_ARM_HEIGHT 3.0
#define LOWER_ARM_RADIUS 0.25

#define HAND 0.25
#define GLOVE 0.2

#define SHOES_HEIGHT  0.25
#define SHOES_WIDTH  1.5
#define SHOES_LENGTH  1.5

#define BODY 0
#define LUA 1
#define LLA 2
#define RUA 3
#define RLA 4
#define LUL 5
#define LLL 6
#define RUL 7
#define RLL 8
#define ALL 9
GLfloat theta[]= {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
GLboolean movement = GL_FALSE;
GLfloat light_direction[3] = {-6.5, -6.5, -6.5};
GLUquadricObj *p;
//define the structrue of the materials.
typedef struct materialStruct{
       GLfloat ambient[4];
       GLfloat diffuse[4];
       GLfloat specular[4];
       GLfloat shininess;
      } materialStruct;
  //define the structrue of the light.
typedef struct lightingStruct{
        GLfloat ambient[4];
        GLfloat diffuse[4];
        GLfloat specular[4];
        } lightingStruct;
//define the arguments of the materials and light.
materialStruct metallicHeadMaterials={{0.5,0.3,0.0,1.0},{0.7,0.50,0.0,1.0},{0.76,0.76,0.6,1.0},20.6};
materialStruct plasticHeadMaterials={{0.3,0.5,0.0,1.0},{0.5,0.70,0.0,1.0},{0.16,0.16,0.16,1.0},50.0};
materialStruct ghostHeadMaterials={{0.7,0.7,0.3,1.0},{0.6,0.60,0.6,1.0},{0.0,0.0,0.00,1.0},50.0};

materialStruct metallicBodyMaterials={{0.5,0.2,0.2,1.0},{0.7,0.50,0.0,1.0},{0.67,0.67,0.67,1.0},20.6};
materialStruct plasticBodyMaterials={{0.2,0.6,0.0,1.0},{0.2,0.70,0.0,1.0},{0.16,0.16,0.16,1.0},50.0};
materialStruct ghostBodyMaterials={{0.6,0.6,0.6,1.0},{0.5,0.50,0.5,1.0},{0.0,0.0,0.0,1.0},50.0};

materialStruct metallicShoesMaterials={{0.8,0.2,0.2,1.0},{0.9,0.50,0.0,1.0},{0.8,0.8,0.8,1.0},20.6};
materialStruct plasticShoesMaterials={{0.2,0.9,0.2,1.0},{0.2,0.80,0.1,1.0},{0.16,0.16,0.16,1.0},50.0};
materialStruct ghostShoesMaterials={{0.15,0.15,0.15,1.0},{0.35,0.35,0.35,1.0},{0.0,0.0,0.0,1.0},50.0};

materialStruct metallicUpperLegMaterials={{0.76,0.76,0.3,1.0},{0.7,0.70,0.2,1.0},{0.60,0.6,0.6,1.0},20.6};
materialStruct plasticUpperLegMaterials={{0.35,0.9,0.3,1.0},{0.45,0.80,0.1,1.0},{0.16,0.16,0.16,1.0},50.0};
materialStruct ghostUpperLegMaterials={{0.65,0.65,0.5,1.0},{0.65,0.65,0.65,1.0},{0.0,0.0,0.0,1.0},50.0};

materialStruct metallicLowerLegMaterials={{0.46,0.46,0.0,1.0},{0.4,0.40,0.1,1.0},{0.60,0.6,0.6,1.0},20.6};
materialStruct plasticLowerLegMaterials={{0.15,0.6,0.2,1.0},{0.25,0.60,0.1,1.0},{0.16,0.16,0.16,1.0},50.0};
materialStruct ghostLowerLegMaterials={{0.45,0.45,0.45,1.0},{0.5,0.5,0.5,1.0},{0.0,0.0,0.0,1.0},50.0};

materialStruct metallicUpperArmMaterials={{0.76,0.26,0.3,1.0},{0.7,0.20,0.2,1.0},{0.70,0.7,0.7,1.0},20.6};
materialStruct plasticUpperArmMaterials={{0.25,0.9,0.3,1.0},{0.25,0.90,0.2,1.0},{0.16,0.16,0.16,1.0},50.0};
materialStruct ghostUpperArmMaterials={{0.75,0.75,0.75,1.0},{0.45,0.45,0.45,1.0},{0.0,0.0,0.0,1.0},50.0};

materialStruct metallicLowerArmMaterials={{0.56,0.3,0.3,1.0},{0.5,0.30,0.3,1.0},{0.70,0.7,0.7,1.0},20.6};
materialStruct plasticLowerArmMaterials={{0.45,0.9,0.5,1.0},{0.46,0.90,0.32,1.0},{0.16,0.16,0.16,1.0},50.0};
materialStruct ghostLowerArmMaterials={{0.55,0.55,0.55,1.0},{0.15,0.15,0.15,1.0},{0.0,0.0,0.0,1.0},50.0};

materialStruct metallicCapMaterials={{0.66,0.3,0.3,1.0},{0.7,0.30,0.3,1.0},{0.70,0.7,0.7,1.0},20.6};
materialStruct plasticCapMaterials={{0.25,0.25,0.25,1.0},{0.26,0.26,0.26,1.0},{0.16,0.16,0.16,1.0},50.0};
materialStruct ghostCapMaterials={{0.55,0.0,0.0,1.0},{0.15,0.15,0.15,1.0},{0.0,0.0,0.0,1.0},50.0};

materialStruct metallicGloveMaterials={{0.76,0.3,0.3,1.0},{0.7,0.60,0.3,1.0},{0.70,0.7,0.7,1.0},20.6};
materialStruct plasticGloveMaterials={{0.25,0.95,0.25,1.0},{0.26,0.96,0.26,1.0},{0.16,0.16,0.16,1.0},50.0};
materialStruct ghostGloveMaterials={{0.0,0.0,0.0,1.0},{0.0,0.0,0.0,1.0},{0.0,0.0,0.0,1.0},50.0};

lightingStruct whiteLight={{0.7,0.7,0.7,1.0},{0.8,0.8,0.8,1.0},{0.9,0.9,0.9,1.0}};
lightingStruct yellowLight={{0.8,0.8,0.0,1.0},{0.9,0.9,0.0,1.0},{0.9,0.9,0.0,1.0}};
lightingStruct redLight={{1.0,0.0,0.0,1.0},{0.8,0.0,0.0,1.0},{0.9,0.0,0.0,1.0}};

materialStruct whitespotLight={{0.7,0.7,0.7,1.0},{0.8,0.8,0.8,1.0},{0.9,0.9,0.9,1.0},100};
materialStruct yellowspotLight={{0.8,0.8,0.0,1.0},{0.9,0.9,0.0,1.0},{0.9,0.9,0.0,1.0},100};
materialStruct redspotLight={{1.0,0.0,0.0,1.0},{0.8,0.0,0.0,1.0},{0.9,0.0,0.0,1.0},100};
GLfloat emission[]={0.4f,0.4f,0.4f,0.0f};
GLfloat light0_pos[4]={6.5,6.5,6.5,1.0};

materialStruct  *headMaterial=&metallicHeadMaterials;
materialStruct  *bodyMaterial=&metallicBodyMaterials;
materialStruct  *shoesMaterial=&metallicShoesMaterials;
materialStruct  *upperLegMaterial=&metallicUpperLegMaterials;
materialStruct  *lowerLegMaterial=&metallicLowerLegMaterials;
materialStruct  *upperArmMaterial=&metallicUpperArmMaterials;
materialStruct  *lowerArmMaterial=&metallicLowerArmMaterials;
materialStruct  *capMaterial=&metallicCapMaterials;
materialStruct  *gloveMaterial=&metallicGloveMaterials;
lightingStruct *currentLight=&whiteLight;
materialStruct  *currentspot=&whitespotLight;
//callback function of key event. to change the color of the light.
void light(unsigned char w,int y,int r){
     switch(w){
               case 'w':
                currentLight=&whiteLight;
               currentspot=&whitespotLight;
               emission[0]=0.4f;
                emission[1]=0.4f;
                 emission[2]=0.4f;
                    break;
               case 'r':
                   currentLight=&redLight;
                   currentspot=&redspotLight;
                   emission[0]=0.4f;
                emission[1]=0.0f;
                 emission[2]=0.0f;
                    break;
               case 'y' :
                    currentLight=&yellowLight;
                    currentspot=&yellowspotLight;
                    emission[0]=0.4f;
                emission[1]=0.4f;
                 emission[2]=0.0f;
                    break;}}
     //define the reaction about menu.
void mymenu(int id){
     if(id==1) {
               headMaterial=&metallicHeadMaterials;
               bodyMaterial=&metallicBodyMaterials;
             shoesMaterial=&metallicShoesMaterials;
             upperLegMaterial=&metallicUpperLegMaterials;
            lowerLegMaterial=&metallicLowerLegMaterials;
           upperArmMaterial=&metallicUpperArmMaterials;
             lowerArmMaterial=&metallicLowerArmMaterials;
             capMaterial=&metallicCapMaterials;
            gloveMaterial=&metallicGloveMaterials;
            }
      if(id==2){
                headMaterial=&plasticHeadMaterials;
               bodyMaterial=&plasticBodyMaterials;
             shoesMaterial=&plasticShoesMaterials;
             upperLegMaterial=&plasticUpperLegMaterials;
            lowerLegMaterial=&plasticLowerLegMaterials;
           upperArmMaterial=&plasticUpperArmMaterials;
             lowerArmMaterial=&plasticLowerArmMaterials;
             capMaterial=&plasticCapMaterials;
            gloveMaterial=&plasticGloveMaterials;}
     if(id==3){
                headMaterial=&ghostHeadMaterials;
               bodyMaterial=&ghostBodyMaterials;
             shoesMaterial=&ghostShoesMaterials;
             upperLegMaterial=&ghostUpperLegMaterials;
            lowerLegMaterial=&ghostLowerLegMaterials;
           upperArmMaterial=&ghostUpperArmMaterials;
             lowerArmMaterial=&ghostLowerArmMaterials;
             capMaterial=&ghostCapMaterials;
            gloveMaterial=&ghostGloveMaterials;}}
            //define the reaction of mouse event.
void mouse(GLint button,GLint state, GLint x, GLint y){
     if( button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
     movement=!movement;
               }
               //let robot rotate automaticlly.
     void idle(){
    if(movement){
          theta[ALL]+=0.5;
          if(theta[ALL]>360) theta[ALL]-=360;
                theta[BODY]+=0.1;
               if(theta[BODY]>45) theta[BODY]-=45;
                theta[LUA]-=0.2;
               if(theta[LUA]<-90) theta[LUA]+=90;
                theta[LLA]-=0.3;
               if(theta[LLA]<-90) theta[LLA]+=90;
                theta[RUA]-=0.15;
               if(theta[RUA]<-90) theta[RUA]+=90;
                theta[RLA]-=0.2;
               if(theta[RLA]<-90) theta[RLA]+=90;
                theta[LUL]+=0.5;
               if(theta[LUL]>45) theta[LUL]-=135;
                theta[LLL]+=0.4;
               if(theta[LLL]>90) theta[LLL]-=90;
                 theta[RUL]+=0.8;
               if(theta[RUL]>45) theta[RUL]-=135;
                theta[RLL]+=0.3;
               if(theta[RLL]>90) theta[RLL]-=90;
                    }
                    glutPostRedisplay();
                    }
//to draw the spot which stand for light source.
void spotlight(){
      glPushMatrix();
     gluSphere(p,0.5,15,15);
     glPopMatrix();
     }
     //to draw the body of the robot
void body(){
     glPushMatrix();
     glTranslatef(0.0,0.5*BODY_HEIGHT,0.0);
     glScalef(BODY_LENGTH,BODY_HEIGHT,BODY_WIDTH);
     glutSolidCube(1.0);
     glPopMatrix();
     }
//to draw the head of the robot
void head(){
      glPushMatrix();
     gluSphere(p,HEAD_RADIUS,15,15);
     glPopMatrix();
     }
//to draw the lower leg of the robot
void lowerLeg(){
     glPushMatrix();
     glTranslatef(0.0,-LOWER_LEG_HEIGHT,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     gluCylinder(p,LOWER_LEG_RADIUS,UPPER_LEG_RADIUS,LOWER_LEG_HEIGHT,100,100);
    glPopMatrix();
     }
//draw the upper leg of the robot
void upperLeg(){
    glPushMatrix();
    gluSphere(p,UPPER_LEG_RADIUS,15,15);
     glTranslatef(0.0,-UPPER_LEG_HEIGHT,0.0);
      glRotatef(-90.0,1.0,0.0,0.0);
     gluCylinder(p,UPPER_LEG_RADIUS,UPPER_LEG_RADIUS,UPPER_LEG_HEIGHT,100,100);
     gluSphere(p,UPPER_LEG_RADIUS,15,15);
     glPopMatrix();
     }
//to draw the upper arm of the robot
void upperArm(){
      glPushMatrix();
     glTranslatef(0.0,-0.5*BODY_HEIGHT*0.125,0.0);
     glScalef(2*UPPER_ARM_RADIUS,BODY_HEIGHT*0.125,BODY_WIDTH);
     glutSolidCube(1.0);
     glTranslatef(0.0,-UPPER_ARM_HEIGHT-0.5*BODY_HEIGHT*0.125,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     gluCylinder(p,UPPER_ARM_RADIUS,UPPER_ARM_RADIUS,UPPER_ARM_HEIGHT,100,100);
     glPopMatrix();
     }
     //to draw the lower arm of the robot
void lowerArm(){
    glPushMatrix();
     gluSphere(p,LOWER_ARM_RADIUS,15,15);
     glTranslatef(0.0,-LOWER_ARM_HEIGHT,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     gluCylinder(p,LOWER_ARM_RADIUS,LOWER_ARM_RADIUS,LOWER_ARM_HEIGHT,100,100);
    glPopMatrix();}
    //to draw the cap of the robot
void capA(){
     glPushMatrix();
     glRotatef(-90.0,1.0,0.0,0.0);
     gluCylinder(p,HEAD_RADIUS,HEAD_RADIUS,CAP_HEIGHT,100,100);
     glPopMatrix();}
void capB(){
     glPushMatrix();
     glTranslatef(0.0,0.5*(CAP_HEIGHT*0.05),0.0);
     glScalef(1.75*CAP_RADIUS,CAP_RADIUS*0.20,1.75*CAP_RADIUS);
     glutSolidCube(1.0);
     glPopMatrix();}
     //to draw the wristband of the robot
void glove(){
     glPushMatrix();
     glTranslatef(0.0,-GLOVE,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     gluCylinder(p,LOWER_ARM_RADIUS,LOWER_ARM_RADIUS,GLOVE,100,100);
     glPopMatrix();}
     //to draw the hand of the robot
void hand(){
      glPushMatrix();
      glTranslatef(0.0,-0.5*HAND,0.0);
     gluSphere(p,HAND,15,15);
     glPopMatrix();
     }
     //to draw the shoes of the robot
void shoes(){
      glPushMatrix();
      glTranslatef(0.0,-SHOES_HEIGHT*0.5,0.0);
     glScalef(SHOES_LENGTH,SHOES_HEIGHT,SHOES_WIDTH);
     glutSolidCube(1.0);
     glPopMatrix();
     }
//draw entire robot and let it move also define the material about differents parts
void object(){
      glRotatef(theta[ALL],0,1,0);
     glPushMatrix();
     glRotatef(theta[BODY],1,0,0);
     glColor3f(0.7,1.0,0.7);
      glMaterialfv(GL_FRONT,GL_AMBIENT,bodyMaterial->ambient);
     glMaterialfv(GL_FRONT,GL_DIFFUSE,bodyMaterial->diffuse);
     glMaterialfv(GL_FRONT,GL_SPECULAR,bodyMaterial->specular);
     glMaterialfv(GL_FRONT,GL_SHININESS,&bodyMaterial->shininess);
     body();
     glPopMatrix();

     glPushMatrix();
     glColor3f(0.8,0.8,0.8);
     glMaterialfv(GL_FRONT,GL_AMBIENT,headMaterial->ambient);
     glMaterialfv(GL_FRONT,GL_DIFFUSE,headMaterial->diffuse);
     glMaterialfv(GL_FRONT,GL_SPECULAR,headMaterial->specular);
     glMaterialfv(GL_FRONT,GL_SHININESS,&headMaterial->shininess);
       glRotatef(theta[BODY],1,0,0);
     glTranslatef(0.0,BODY_HEIGHT+HEAD_RADIUS,0.0);
          head();
       glPopMatrix();

     glPushMatrix();
     glColor3f(0.0,0.0,0.0);
     glMaterialfv(GL_FRONT,GL_AMBIENT,capMaterial->ambient);
     glMaterialfv(GL_FRONT,GL_DIFFUSE,capMaterial->diffuse);
     glMaterialfv(GL_FRONT,GL_SPECULAR,capMaterial->specular);
     glMaterialfv(GL_FRONT,GL_SHININESS,&capMaterial->shininess);
     glRotatef(theta[BODY],1,0,0);
      glTranslatef(0.0,BODY_HEIGHT+HEAD_RADIUS+0.7,0.0);
    capA();
     glPopMatrix();

     glPushMatrix();
     glColor3f(0.0,0.0,0.0);
     glMaterialfv(GL_FRONT,GL_AMBIENT,capMaterial->ambient);
     glMaterialfv(GL_FRONT,GL_DIFFUSE,capMaterial->diffuse);
     glMaterialfv(GL_FRONT,GL_SPECULAR,capMaterial->specular);
     glMaterialfv(GL_FRONT,GL_SHININESS,&capMaterial->shininess);
       glRotatef(theta[BODY],1,0,0);
     glTranslatef(0.0,BODY_HEIGHT+HEAD_RADIUS+HEAD_RADIUS*0.7+CAP_HEIGHT,0.0);
    capB();

       glPopMatrix();

       glPushMatrix();
     glColor3f(0.7,1.0,0.7);
      glMaterialfv(GL_FRONT,GL_AMBIENT,upperArmMaterial->ambient);
     glMaterialfv(GL_FRONT,GL_DIFFUSE,upperArmMaterial->diffuse);
     glMaterialfv(GL_FRONT,GL_SPECULAR,upperArmMaterial->specular);
     glMaterialfv(GL_FRONT,GL_SHININESS,&upperArmMaterial->shininess);
       glRotatef(theta[BODY],1,0,0);
      glTranslatef(-BODY_LENGTH*0.5-UPPER_ARM_RADIUS*0.5-0.15,BODY_HEIGHT,0.0);
     glRotatef(theta[LUA],1,0,0);
     upperArm();
      glColor3f(0.8,0.8,0.8);
      glMaterialfv(GL_FRONT,GL_AMBIENT,lowerArmMaterial->ambient);
     glMaterialfv(GL_FRONT,GL_DIFFUSE,lowerArmMaterial->diffuse);
     glMaterialfv(GL_FRONT,GL_SPECULAR,lowerArmMaterial->specular);
     glMaterialfv(GL_FRONT,GL_SHININESS,&lowerArmMaterial->shininess);
     glTranslatef(0,-UPPER_ARM_HEIGHT,0.0);
      glRotatef(theta[LLA],1,0,0);
     lowerArm();
     glColor3f(0.7,1.0,0.7);
     glMaterialfv(GL_FRONT,GL_AMBIENT,gloveMaterial->ambient);
     glMaterialfv(GL_FRONT,GL_DIFFUSE,gloveMaterial->diffuse);
     glMaterialfv(GL_FRONT,GL_SPECULAR,gloveMaterial->specular);
     glMaterialfv(GL_FRONT,GL_SHININESS,&gloveMaterial->shininess);
     glTranslatef(0.0,-LOWER_ARM_HEIGHT,0.0);
     glove();
     glColor3f(0.8,0.8,0.8);
     glMaterialfv(GL_FRONT,GL_AMBIENT,headMaterial->ambient);
     glMaterialfv(GL_FRONT,GL_DIFFUSE,headMaterial->diffuse);
     glMaterialfv(GL_FRONT,GL_SPECULAR,headMaterial->specular);
     glMaterialfv(GL_FRONT,GL_SHININESS,&headMaterial->shininess);
     glTranslatef(0.0,-GLOVE,0.0);
     hand();
     glPopMatrix();

      glPushMatrix();
     glColor3f(0.7,1.0,0.7);
     glMaterialfv(GL_FRONT,GL_AMBIENT,upperArmMaterial->ambient);
     glMaterialfv(GL_FRONT,GL_DIFFUSE,upperArmMaterial->diffuse);
     glMaterialfv(GL_FRONT,GL_SPECULAR,upperArmMaterial->specular);
     glMaterialfv(GL_FRONT,GL_SHININESS,&upperArmMaterial->shininess);
     glRotatef(theta[BODY],1,0,0);
      glTranslatef(BODY_LENGTH*0.5+UPPER_ARM_RADIUS*0.5+0.15,BODY_HEIGHT,0.0);
     glRotatef(theta[RUA],1,0,0);
     upperArm();
      glColor3f(0.8,0.8,0.8);
     glMaterialfv(GL_FRONT,GL_AMBIENT,lowerArmMaterial->ambient);
     glMaterialfv(GL_FRONT,GL_DIFFUSE,lowerArmMaterial->diffuse);
     glMaterialfv(GL_FRONT,GL_SPECULAR,lowerArmMaterial->specular);
     glMaterialfv(GL_FRONT,GL_SHININESS,&lowerArmMaterial->shininess);
     glTranslatef(0,-UPPER_ARM_HEIGHT,0.0);
      glRotatef(theta[RLA],1,0,0);
     lowerArm();
     glColor3f(0.7,1.0,0.7);
    glMaterialfv(GL_FRONT,GL_AMBIENT,gloveMaterial->ambient);
     glMaterialfv(GL_FRONT,GL_DIFFUSE,gloveMaterial->diffuse);
     glMaterialfv(GL_FRONT,GL_SPECULAR,gloveMaterial->specular);
     glMaterialfv(GL_FRONT,GL_SHININESS,&gloveMaterial->shininess);
     glTranslatef(0.0,-LOWER_ARM_HEIGHT,0.0);
     glove();
     glColor3f(0.8,0.8,0.8);
     glMaterialfv(GL_FRONT,GL_AMBIENT,headMaterial->ambient);
     glMaterialfv(GL_FRONT,GL_DIFFUSE,headMaterial->diffuse);
     glMaterialfv(GL_FRONT,GL_SPECULAR,headMaterial->specular);
     glMaterialfv(GL_FRONT,GL_SHININESS,&headMaterial->shininess);
      glTranslatef(0.0,-GLOVE,0.0);
     hand();
     glPopMatrix();

     glPushMatrix();
     glColor3f(0.7,1.0,0.7);
     glMaterialfv(GL_FRONT,GL_AMBIENT,upperLegMaterial->ambient);
     glMaterialfv(GL_FRONT,GL_DIFFUSE,upperLegMaterial->diffuse);
     glMaterialfv(GL_FRONT,GL_SPECULAR,upperLegMaterial->specular);
     glMaterialfv(GL_FRONT,GL_SHININESS,&upperLegMaterial->shininess);
      glTranslatef(-BODY_LENGTH*0.5+UPPER_LEG_RADIUS*0.5+0.35,0.0,0.0);
     glRotatef(theta[LUL],1,0,0);
     upperLeg();
     glColor3f(0.8,0.8,0.8);
     glMaterialfv(GL_FRONT,GL_AMBIENT,lowerLegMaterial->ambient);
     glMaterialfv(GL_FRONT,GL_DIFFUSE,lowerLegMaterial->diffuse);
     glMaterialfv(GL_FRONT,GL_SPECULAR,lowerLegMaterial->specular);
     glMaterialfv(GL_FRONT,GL_SHININESS,&lowerLegMaterial->shininess);
     glTranslatef(0.0,-UPPER_LEG_HEIGHT,0);
     glRotatef(theta[LLL],1,0,0);
     lowerLeg();
     glColor3f(0.0,0.0,0.0);
     glMaterialfv(GL_FRONT,GL_AMBIENT,shoesMaterial->ambient);
     glMaterialfv(GL_FRONT,GL_DIFFUSE,shoesMaterial->diffuse);
     glMaterialfv(GL_FRONT,GL_SPECULAR,shoesMaterial->specular);
     glMaterialfv(GL_FRONT,GL_SHININESS,&shoesMaterial->shininess);
     glTranslatef(0.0,-LOWER_LEG_HEIGHT,0);
     shoes();
     glPopMatrix();

    glPushMatrix();
     glColor3f(0.7,1.0,0.7);
      glMaterialfv(GL_FRONT,GL_AMBIENT,upperLegMaterial->ambient);
     glMaterialfv(GL_FRONT,GL_DIFFUSE,upperLegMaterial->diffuse);
     glMaterialfv(GL_FRONT,GL_SPECULAR,upperLegMaterial->specular);
     glMaterialfv(GL_FRONT,GL_SHININESS,&upperLegMaterial->shininess);
     glTranslatef(BODY_LENGTH*0.5-UPPER_LEG_RADIUS*0.5-0.35,0.0,0.0);
        glRotatef(theta[RUL],1,0,0);
     upperLeg();
     glColor3f(0.8,0.8,0.8);
      glMaterialfv(GL_FRONT,GL_AMBIENT,lowerLegMaterial->ambient);
     glMaterialfv(GL_FRONT,GL_DIFFUSE,lowerLegMaterial->diffuse);
     glMaterialfv(GL_FRONT,GL_SPECULAR,lowerLegMaterial->specular);
     glMaterialfv(GL_FRONT,GL_SHININESS,&lowerLegMaterial->shininess);
      glTranslatef(0.0,-UPPER_LEG_HEIGHT,0);
         glRotatef(theta[RLL],1,0,0);
     lowerLeg();
     glColor3f(0.0,0.0,0.0);
      glMaterialfv(GL_FRONT,GL_AMBIENT,shoesMaterial->ambient);
     glMaterialfv(GL_FRONT,GL_DIFFUSE,shoesMaterial->diffuse);
     glMaterialfv(GL_FRONT,GL_SPECULAR,shoesMaterial->specular);
     glMaterialfv(GL_FRONT,GL_SHININESS,&shoesMaterial->shininess);
     glTranslatef(0.0,-LOWER_LEG_HEIGHT,0);
     shoes();
     glPopMatrix();
     glLoadIdentity();
     //let spot which stand for light source rotate againt robot and enable light.
     glRotatef(-theta[ALL],0,1,0);
      glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);
       glLightfv(GL_LIGHT0,GL_POSITION,light0_pos);
     glTranslatef(6.5,6.5,6.5);
     glMaterialfv(GL_FRONT,GL_AMBIENT,currentspot->ambient);
     glMaterialfv(GL_FRONT,GL_DIFFUSE,currentspot->diffuse);
     glMaterialfv(GL_FRONT,GL_SPECULAR,currentspot->specular);
     glMaterialfv(GL_FRONT,GL_SHININESS,&currentspot->shininess);
   glMaterialfv(GL_FRONT,GL_EMISSION,emission);
     spotlight();
      }
//display object.
void display(){
     glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     gluLookAt(1.0,1.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);
    object();
   glutSwapBuffers();
     }
      void init(){
           glClearColor(0.5f,0.5f,0.5f,1.0f);
           p =gluNewQuadric();
      glEnable(GL_LIGHTING);
           glEnable(GL_LIGHT0);
           glEnable(GL_NORMALIZE);
           glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);
         glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,2.0);
         glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);
           glLightfv(GL_LIGHT0,GL_AMBIENT,currentLight->ambient);
            glLightfv(GL_LIGHT0,GL_DIFFUSE,currentLight->diffuse);
            glLightfv(GL_LIGHT0,GL_SPECULAR,currentLight->specular);
              glLightfv(GL_LIGHT0,GL_POSITION,light0_pos);
           }
           void reshape(int w,int h){
                glViewport(0,0,w,h);
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                if(w<=h)
                glOrtho(-12.0,12.0,-12.0*(GLfloat)h/(GLfloat)w,12.0*(GLfloat)h/(GLfloat)w,-12.0,12.0);
                else
                  glOrtho(-12.0*(GLfloat)w/(GLfloat)h,12.0*(GLfloat)w/(GLfloat)h,-12.0,12.0,-12.0,12.0);}
     int main(int argc, char **argv){
         glutInit(&argc, argv);
         glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
         glutInitWindowSize(500,500);
         glutCreateWindow(" robot ");
          glutDisplayFunc(display);
         glutReshapeFunc(reshape);
         glEnable(GL_DEPTH_TEST);
         glutIdleFunc(idle);
         init();
         glutCreateMenu(mymenu);
         glutAddMenuEntry("metallic",1);
         glutAddMenuEntry("plastic",2);
         glutAddMenuEntry("ghost",3);
         glutAttachMenu(GLUT_RIGHT_BUTTON);
         glutKeyboardFunc(light);
         glutMouseFunc(mouse);
         glutMainLoop();}




