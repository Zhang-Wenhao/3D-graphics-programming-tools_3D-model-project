/*
 * pig.c
 *
 *  Created on: 2018��4��24��
 *      Author: 40360
 */

#include <GL/glut.h>
#include <windows.h>

#include <math.h>
int axis; //��һֻ����ת����
int axis2; //�ڶ�ֻ����ת����
GLfloat theta[3] ={0.0, 0.0, 0.0}; //��һֻ��ÿ�������ת��
GLfloat theta2[3] ={0.0, 0.0, 0.0}; //�ڶ�ֻ��ÿ�������ת��
const int n = 1000;
GLfloat ax = -1.0f; //��һֻ��ĳ�ʼ����
GLfloat ay = 0.0f;
GLfloat az = 0.0f;
GLfloat bx= 1.0f; //�ڶ�ֻ��ĳ�ʼ����
GLfloat by = 0.0f;
GLfloat bz = 0.0f;
GLfloat mx = 1.0f; //��һֻ�����ű���
GLfloat my = 1.0f;
GLfloat mz = 1.0f;
GLfloat nx = 1.0f; //�ڶ�ֻ�����ű���
GLfloat ny = 1.0f;
GLfloat nz = 1.0f;
GLint view = 0;
GLfloat ex[3] = {0.0, 0.0, 0.0}; //�۲���λ��
GLfloat ey[3] = {1.0, 0.0, 0.0};
GLfloat ez[3] = {4.0, 0.0, 0.0};
GLfloat fx[3] = {0.0, 0.0, 0.0}; //�۲����λ��
GLfloat fy[3] = {0.0, 0.0, 0.0};
GLfloat fz[3] = {0.0, 0.0, 0.0};
GLint flag;
const GLfloat Pi = 3.1415926536f; //Բ����

void drawPig1() //����һֻ��
{
	glTranslatef(ax,ay,az);
	glScalef(mx, my, mz);
	//glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	//glRotatef(theta[2], 0.0, 0.0, 1.0);

	glPushMatrix();
	glTranslatef(0.15, -0.2, 0.125);
	glColor3f(1.0, 0.5, 0.5);
	glutSolidSphere( 0.05f, 100, 100 ); //��ǰ��
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.5, 0.5);
	glTranslatef(-0.15, -0.2, 0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //��ǰ��
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.5, 0.5);
	glTranslatef(0.15, -0.2, -0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //����
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.5, 0.5);
	glTranslatef(-0.15, -0.2, -0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //�Һ��
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.5, 0.5);
	GLUquadricObj *quadratic;
	quadratic=gluNewQuadric();
	gluCylinder(quadratic,0.05f,0.05f,0.27f,50,50); //����
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.5, 0.5);
	glBegin(GL_TRIANGLES);
		glVertex3f(0.2,0.28,0.15);
		glVertex3f(0.19,0.06,0.15);
		glVertex3f(0.07,0.21,0.1);

		glVertex3f(0.2,0.28,0.15);
		glVertex3f(0.07,0.21,0.1);
		glVertex3f(0.12,0.2,0.08);

		glVertex3f(0.2,0.28,0.15);
		glVertex3f(0.19,0.06,0.15);
		glVertex3f(0.12,0.2,0.08);
	glEnd(); //���
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.5, 0.5);
	glBegin(GL_TRIANGLES);
		glVertex3f(-0.2,0.28,0.15);
		glVertex3f(-0.19,0.06,0.15);
		glVertex3f(-0.07,0.21,0.1);

		glVertex3f(-0.2,0.28,0.15);
		glVertex3f(-0.07,0.21,0.1);
		glVertex3f(-0.12,0.2,0.08);

		glVertex3f(-0.2,0.28,0.15);
		glVertex3f(-0.19,0.06,0.15);
		glVertex3f(-0.12,0.2,0.08);
	glEnd(); //�Ҷ�
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.8, 0.8);
	glutSolidSphere( 0.25f, 100, 100 );  //����
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.5, 0.5);
	glBegin(GL_POLYGON);
	for(int i=0; i<n; ++i)
		glVertex3f(0.06*cos(2*Pi/n*i) , 0.04*sin(2*Pi/n*i), 0.27f);
	glEnd();//����(����)
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for(int i=0; i<n; ++i)
		glVertex3f(-0.02+0.01*cos(2*Pi/n*i), 0.01*sin(2*Pi/n*i), 0.27f);
	glEnd();//�ұǿ�
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for(int i=0; i<n; ++i)
		glVertex3f(0.02+0.01*cos(2*Pi/n*i), 0.01*sin(2*Pi/n*i), 0.27f);
	glEnd();//��ǿ�
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.05, 0.08, 0.23);
	glutSolidSphere( 0.013f, 1000, 1000 );  //����
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(-0.05, 0.08, 0.23);
	glutSolidSphere( 0.013f, 1000, 1000 );  //����
	glPopMatrix();
}

void drawPig2() //���ڶ�ֻ��
{
	glTranslatef(bx, by, bz);
	glScalef(nx, ny, nz);
	//glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	//glRotatef(theta2[2], 0.0, 0.0, 1.0);

	glPushMatrix();
	glColor3f(1.0, 0.8, 0.8);
	glTranslatef(0.15, -0.2, 0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //��ǰ��
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.8, 0.8);
	glTranslatef(-0.15, -0.2, 0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //��ǰ��
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.8, 0.8);
	glTranslatef(0.15, -0.2, -0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //����
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.8, 0.8);
	glTranslatef(-0.15, -0.2, -0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //�Һ��
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.8, 0.8);
	GLUquadricObj *quadratic2;
	quadratic2=gluNewQuadric();
	gluCylinder(quadratic2,0.05f,0.05f,0.27f,50,50); //����
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.8, 0.8);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.2,0.28,0.15);
	glVertex3f(0.19,0.06,0.15);
	glVertex3f(0.07,0.21,0.1);

	glVertex3f(0.2,0.28,0.15);
	glVertex3f(0.07,0.21,0.1);
	glVertex3f(0.12,0.2,0.08);

	glVertex3f(0.2,0.28,0.15);
	glVertex3f(0.19,0.06,0.15);
	glVertex3f(0.12,0.2,0.08);
	glEnd(); //���
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.8, 0.8);
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.2,0.28,0.15);
	glVertex3f(-0.19,0.06,0.15);
	glVertex3f(-0.07,0.21,0.1);

	glVertex3f(-0.2,0.28,0.15);
	glVertex3f(-0.07,0.21,0.1);
	glVertex3f(-0.12,0.2,0.08);

	glVertex3f(-0.2,0.28,0.15);
	glVertex3f(-0.19,0.06,0.15);
	glVertex3f(-0.12,0.2,0.08);
	glEnd(); //�Ҷ�
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.6, 0.7);
	glutSolidSphere( 0.25f, 100, 100 );  //����
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.8, 0.8);
	glBegin(GL_POLYGON);
	for(int i=0; i<n; ++i)
		glVertex3f(0.06*cos(2*Pi/n*i) , 0.04*sin(2*Pi/n*i), 0.27f);
	glEnd();//����(����)
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for(int i=0; i<n; ++i)
		glVertex3f(-0.02+0.01*cos(2*Pi/n*i), 0.01*sin(2*Pi/n*i), 0.27f);
	glEnd();//�ұǿ�
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for(int i=0; i<n; ++i)
		glVertex3f(0.02+0.01*cos(2*Pi/n*i), 0.01*sin(2*Pi/n*i), 0.27f);
	glEnd();//��ǿ�
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.05, 0.08, 0.23);
	glutSolidSphere( 0.013f, 1000, 1000 );  //����
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(-0.05, 0.08, 0.23);
	glutSolidSphere( 0.013f, 1000, 1000 );  //����
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-bx,by,bz);
	glPopMatrix();
}

void display()
{
	//glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	//glEnable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(ex[view],ey[view] ,ez[view] , fx[view], fy[view], fz[view], 0.0 ,1.0, 0.0);

	glColor3f(0.82, 0.82, 0.82);
	glBegin(GL_LINES);
	float i, j;
	for (i = -50; i <= 50; i = i + 0.2)
	{
		glVertex3f(i, -0.25, -50);
		glVertex3f(i,-0.25, 50);
	}
	for (j = -50; j <=50; j += 0.2)
	{
		glVertex3f(-50, -0.25, j);
		glVertex3f(50, -0.25, j);
	}
	glEnd();


	glPushMatrix();
	drawPig1();
	glPopMatrix();

	glPushMatrix();
	drawPig2();
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 0.0, 100.0);
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glShadeModel(GL_FLAT);
}

void mykey(unsigned char key, int x, int y)
{
	//����1
	if(key == 'Q'|| key == 'q') //�Ŵ�
	{
		mx += 0.01;
		my += 0.01;
		mz += 0.01;
	}
	if(key == 'E'|| key == 'e') //��С
	{
		mx -= 0.01;
		my -= 0.01;
		mz -= 0.01;
	}
	if(key == 'D'|| key == 'd') //��ת
	{
		axis = 1;
		theta[axis] -= 5.0;
		if (theta[axis] > 360.0)
			theta[axis] -= 360.0;
		ex[1] = (ex[1]-ax)*cos(5*Pi/180) - (ez[1]-az)*sin(5*Pi/180) + ax;
		ez[1] = (ex[1]-ax)*sin(5*Pi/180) + (ez[1]-az)*cos(5*Pi/180) + az;
		fx[1] = (fx[1]-ax)*cos(5*Pi/180) - (fz[1]-az)*sin(5*Pi/180) + ax;
		fz[1] = (fx[1]-ax)*sin(5*Pi/180) + (fz[1]-az)*cos(5*Pi/180) + az;
	}
	if(key == 'A'|| key == 'a') //��ת
	{
		axis = 1;
		theta[axis] += 5.0;
		if (theta[axis] > 360.0)
			theta[axis] -= 360.0;
		ex[1] = (ex[1]-ax)*cos(5*Pi/180) + (ez[1]-az)*sin(5*Pi/180) + ax;
		ez[1] = -(ex[1]-ax)*sin(5*Pi/180) + (ez[1]-az)*cos(5*Pi/180) + az;
		fx[1] = (fx[1]-ax)*cos(5*Pi/180) + (fz[1]-az)*sin(5*Pi/180) + ax;
		fz[1] = -(fx[1]-ax)*sin(5*Pi/180) + (fz[1]-az)*cos(5*Pi/180) + az;
	}
	if(key == 'S'|| key == 's') //����
	{
		ax -= 0.01*sin(theta[1]*Pi/180);
		az -= 0.01*cos(theta[1]*Pi/180);
		ex[1] -= 0.01*sin(theta[1]*Pi/180);
		ez[1] -= 0.01*cos(theta[1]*Pi/180);
		fx[1] -= 0.01*sin(theta[1]*Pi/180);
		fz[1] -= 0.01*cos(theta[1]*Pi/180);
	}
	if(key == 'W'|| key == 'w') //ǰ��
	{
		ax += 0.01*sin(theta[1]*Pi/180);
		az += 0.01*cos(theta[1]*Pi/180);
		ex[1] += 0.01*sin(theta[1]*Pi/180);
		ez[1] += 0.01*cos(theta[1]*Pi/180);
		fx[1] += 0.01*sin(theta[1]*Pi/180);
		fz[1] += 0.01*cos(theta[1]*Pi/180);
	}

	//����2
	if(key == 'R'|| key == 'r') //�Ŵ�
	{
		nx += 0.01;
		ny += 0.01;
		nz += 0.01;
	}
	if(key == 'Y'|| key == 'y') //��С
	{
		nx -= 0.01;
		ny -= 0.01;
		nz -= 0.01;
	}
	if(key == 'G'|| key == 'g') //����
	{
		bx -= 0.01*sin(theta2[1]*Pi/180);
		bz -= 0.01*cos(theta2[1]*Pi/180);
		ex[2] -= 0.01*sin(theta2[1]*Pi/180);
		ez[2] -= 0.01*cos(theta2[1]*Pi/180);
		fx[2] -= 0.01*sin(theta2[1]*Pi/180);
		fz[2] -= 0.01*cos(theta2[1]*Pi/180);
	}
	if(key == 'T'|| key == 't') //ǰ��
	{
		bx += 0.01*sin(theta2[1]*Pi/180);
		bz += 0.01*cos(theta2[1]*Pi/180);
		ex[2] += 0.01*sin(theta2[1]*Pi/180);
		ez[2] += 0.01*cos(theta2[1]*Pi/180);
		fx[2] += 0.01*sin(theta2[1]*Pi/180);
		fz[2] += 0.01*cos(theta2[1]*Pi/180);
	}
	if(key == 'F'||key == 'f') //��ת
	{
		axis2 = 1;
		theta2[axis2] += 5.0;
		if (theta2[axis2] > 360.0)
			theta2[axis2] -= 360.0;
		ex[2] = (ex[2]-bx)*cos(5*Pi/180) + (ez[2]-bz)*sin(5*Pi/180) + bx;
		ez[2] = -(ex[2]-bx)*sin(5*Pi/180) + (ez[2]-bz)*cos(5*Pi/180) + bz;
		fx[2] = (fx[2]-bx)*cos(5*Pi/180) + (fz[2]-bz)*sin(5*Pi/180) + bx;
		fz[2] = -(fx[2]-bx)*sin(5*Pi/180) + (fz[2]-bz)*cos(5*Pi/180) + bz;
	}
	if(key == 'H'||key == 'h') //��ת
	{
		axis2 = 1;
		theta2[axis2] -= 5.0;
		if (theta2[axis2] > 360.0)
			theta2[axis2] -= 360.0;
		ex[2] = (ex[2]-bx)*cos(5*Pi/180) - (ez[2]-bz)*sin(5*Pi/180) + bx;
		ez[2] = (ex[2]-bx)*sin(5*Pi/180) + (ez[2]-bz)*cos(5*Pi/180) + bz;
		fx[2] = (fx[2]-bx)*cos(5*Pi/180) - (fz[2]-bz)*sin(5*Pi/180) + bx;
		fz[2] = (fx[2]-bx)*sin(5*Pi/180) + (fz[2]-bz)*cos(5*Pi/180) + bz;
	}

	//�ı�۲���λ��
	if(key == '1') //��
	{
		ey[view] += 0.01f;
	}
	if(key == '2') //��
	{
		ey[view] -= 0.01f;
	}
	if(key == '3') //��
	{
		ex[view] -= 0.01f;
	}
	if(key == '4') //��
	{
		ex[view] += 0.01f;
	}
	if(key == '5') //ǰ
	{
		ez[view] += 0.01f;
	}
	if(key == '6') //��
	{
		ez[view] -= 0.01f;
	}

	//�ı�۲����λ��
	if(key == '7') //��
	{
		fy[view] += 0.01f;
	}
	if(key == '8') //��
	{
		fy[view] -= 0.01f;
	}
	if(key == '9') //��
	{
		fx[view] -= 0.01f;
	}
	if(key == '0') //��
	{
		fx[view] += 0.01f;
	}

	glutPostRedisplay();
}

void mymenu(int id)
{
	if(id == 1) //���ͼ��
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();
	}
	if(id == 2) //��ԭ
	{
		glClear (GL_COLOR_BUFFER_BIT);
		theta[0] =0.0;
		theta[1] =0.0;
		theta[2] =0.0;
		theta2[0] =0.0;
		theta2[1] =0.0;
		theta2[2] =0.0;
		ax = -1.0f; //��һֻ�������
		ay = 0.0f;
		az = 0.0f;
		bx= 1.0f; //�ڶ�ֻ�������
		by = 0.0f;
		bz = 0.0f;
		mx = 1.0f; //��һֻ�����ű���
		my = 1.0f;
		mz = 1.0f;
		nx = 1.0f; //�ڶ�ֻ�����ű���
		ny = 1.0f;
		nz = 1.0f;
		view = 0;
		ex[view] = 0.0f; //�۲���λ��
		ey[view] = 1.0f;
		ez[view] = 4.0f;
		fx[view] = 0.0f; //�۲����λ��
		fy[view] = 0.0f;
		fz[view] = 0.0f;
		display();
	}
	if(id == 3)
	{
		view = 1;
		ex[view] = ax+ 0.01*sin(theta[1]*Pi/180);
		ey[view] = ay + 0.3;
		ez[view] = az + 0.01*sin(theta[1]*Pi/180);

		fx[view] = ex[view] + sin(theta[1]*Pi/180);
		fy[view] = ey[view];
		fz[view] = ez[view] + cos(theta[1]*Pi/180);
	}
	if(id == 4)
	{
		view = 2;
		ex[view] = bx + 0.01*sin(theta2[1]*Pi/180);
		ey[view] = by + 0.3;
		ez[view] = bz  + 0.01*sin(theta2[1]*Pi/180);

		fx[view] = ex[view] + sin(theta2[1]*Pi/180);
		fy[view] = ey[view];
		fz[view] = ez[view] + cos(theta2[1]*Pi/180);
	}
}

int main(int argc, char ** argv)
{
    glutInit(& argc , argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
    glutCreateWindow("��ֻ��ά����");
    glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(mykey); //������Ӧ
	glutIdleFunc(display);
	glutCreateMenu(mymenu); //�Ҽ��˵�
	glutAddMenuEntry("Clear Screen", 1);
	glutAddMenuEntry("Restore", 2);
	glutAddMenuEntry("Pig1 view", 3);
	glutAddMenuEntry("Pig2 view", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();
    glutMainLoop();
}


