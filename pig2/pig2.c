/*
 * pig2.c
 *
 *  Created on: 2018��4��24��
 *      Author: 40360
 */
#include <GL/glut.h>
#include <windows.h>

#include <math.h>
int axis; //��һֻ����ת����
int axis2; //�ڶ�ֻ����ת����
float theta[3] ={0.0, 0.0, 0.0}; //��һֻ��ÿ�������ת��
float theta2[3] ={0.0, 0.0, 0.0}; //�ڶ�ֻ��ÿ�������ת��
const int n = 1000;
GLfloat ax = -0.5f; //��һֻ�������
GLfloat ay = 0.0f;
GLfloat az = 0.0f;
GLfloat bx= 0.5f; //�ڶ�ֻ�������
GLfloat by = 0.0f;
GLfloat bz = 0.0f;
GLfloat mx = 1.0f; //��һֻ�����ű���
GLfloat my = 1.0f;
GLfloat mz = 1.0f;
GLfloat nx = 1.0f; //�ڶ�ֻ�����ű���
GLfloat ny = 1.0f;
GLfloat nz = 1.0f;
const GLfloat Pi = 3.1415926536f; //Բ����

void drawPig()
{
	//glClearDepth(1.0f);// ������Ȼ���
	//glEnable(GL_DEPTH_TEST);// ������Ȳ���
	//glDepthFunc(GL_LEQUAL);

	//��һֻ����
	glLoadIdentity();
	glScalef(mx, my, mz);
	glTranslatef(ax, ay, az);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.5, 0.5);
	glTranslatef(0.15, -0.2, 0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //��ǰ��

	glLoadIdentity();
	glScalef(mx, my, mz);
	glTranslatef(ax, ay, az);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.5, 0.5);
	glTranslatef(-0.15, -0.2, 0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //��ǰ��

	glLoadIdentity();
	glScalef(mx, my, mz);
	glTranslatef(ax, ay, az);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.5, 0.5);
	glTranslatef(0.15, -0.2, -0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //����

	glLoadIdentity();
	glScalef(mx, my, mz);
	glTranslatef(ax, ay, az);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.5, 0.5);
	glTranslatef(-0.15, -0.2, -0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //�Һ��

	glLoadIdentity();
	glScalef(mx, my, mz);
	glTranslatef(ax, ay, az);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.5, 0.5);
	GLUquadricObj *quadratic;
	quadratic=gluNewQuadric();
	gluCylinder(quadratic,0.05f,0.05f,0.27f,50,50); //����

	glLoadIdentity();
	glScalef(mx, my, mz);
	glTranslatef(ax, ay, az);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
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

	glLoadIdentity();
	glScalef(mx, my, mz);
	glTranslatef(ax, ay, az);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
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

	glLoadIdentity();
	glScalef(mx, my, mz);
	glTranslatef(ax, ay, az);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.8, 0.8);
	glutSolidSphere( 0.25f, 100, 100 );  //����

	glLoadIdentity();
	glScalef(mx, my, mz);
	glTranslatef(ax, ay, az);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.5, 0.5);
    glBegin(GL_POLYGON);
    for(int i=0; i<n; ++i)
        glVertex3f(0.06*cos(2*Pi/n*i) , 0.04*sin(2*Pi/n*i), 0.27f);
    glEnd();//����(����)

	glLoadIdentity();
	glScalef(mx, my, mz);
	glTranslatef(ax, ay, az);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for(int i=0; i<n; ++i)
        glVertex3f(-0.02+0.01*cos(2*Pi/n*i), 0.01*sin(2*Pi/n*i), 0.27f);
    glEnd();//�ұǿ�

	glLoadIdentity();
	glScalef(mx, my, mz);
	glTranslatef(ax, ay, az);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for(int i=0; i<n; ++i)
        glVertex3f(0.02+0.01*cos(2*Pi/n*i), 0.01*sin(2*Pi/n*i), 0.27f);
    glEnd();//��ǿ�

	glLoadIdentity();
	glScalef(mx, my, mz);
	glTranslatef(ax, ay, az);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.05, 0.08, 0.23);
	glutSolidSphere( 0.013f, 1000, 1000 );  //����

	glLoadIdentity();
	glScalef(mx, my, mz);
	glTranslatef(ax, ay, az);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(-0.05, 0.08, 0.23);
	glutSolidSphere( 0.013f, 1000, 1000 );  //����

	//�ڶ�ֻ����
	glLoadIdentity();
	glScalef(nx, ny, nz);
	glTranslatef(bx, by, bz);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.8, 0.8);
	glTranslatef(0.15, -0.2, 0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //��ǰ��

	glLoadIdentity();
	glScalef(nx, ny, nz);
	glTranslatef(bx, by, bz);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.8, 0.8);
	glTranslatef(-0.15, -0.2, 0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //��ǰ��

	glLoadIdentity();
	glScalef(nx, ny, nz);
	glTranslatef(bx, by, bz);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.8, 0.8);
	glTranslatef(0.15, -0.2, -0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //����

	glLoadIdentity();
	glScalef(nx, ny, nz);
	glTranslatef(bx, by, bz);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.8, 0.8);
	glTranslatef(-0.15, -0.2, -0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //�Һ��

	glLoadIdentity();
	glScalef(nx, ny, nz);
	glTranslatef(bx, by, bz);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.8, 0.8);
	GLUquadricObj *quadratic2;
	quadratic2=gluNewQuadric();
	gluCylinder(quadratic2,0.05f,0.05f,0.27f,50,50); //����

	glLoadIdentity();
	glScalef(nx, ny, nz);
	glTranslatef(bx, by, bz);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
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

	glLoadIdentity();
	glScalef(nx, ny, nz);
	glTranslatef(bx, by, bz);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
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

	glLoadIdentity();
	glScalef(nx, ny, nz);
	glTranslatef(bx, by, bz);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.6, 0.7);
	glutSolidSphere( 0.25f, 100, 100 );  //����

	glLoadIdentity();
	glScalef(nx, ny, nz);
	glTranslatef(bx, by, bz);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.8, 0.8);
    glBegin(GL_POLYGON);
    for(int i=0; i<n; ++i)
        glVertex3f(0.06*cos(2*Pi/n*i) , 0.04*sin(2*Pi/n*i), 0.27f);
    glEnd();//����(����)

	glLoadIdentity();
	glScalef(nx, ny, nz);
	glTranslatef(bx, by, bz);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for(int i=0; i<n; ++i)
        glVertex3f(-0.02+0.01*cos(2*Pi/n*i), 0.01*sin(2*Pi/n*i), 0.27f);
    glEnd();//�ұǿ�

	glLoadIdentity();
	glScalef(nx, ny, nz);
	glTranslatef(bx, by, bz);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for(int i=0; i<n; ++i)
        glVertex3f(0.02+0.01*cos(2*Pi/n*i), 0.01*sin(2*Pi/n*i), 0.27f);
    glEnd();//��ǿ�

	glLoadIdentity();
	glScalef(nx, ny, nz);
	glTranslatef(bx, by, bz);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.05, 0.08, 0.23);
	glutSolidSphere( 0.013f, 1000, 1000 );  //����

	glLoadIdentity();
	glScalef(nx, ny, nz);
	glTranslatef(bx, by, bz);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(-0.05, 0.08, 0.23);
	glutSolidSphere( 0.013f, 1000, 1000 );  //����
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	drawPig();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 1.0, 100.0);
	gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0 ,1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void mykey(unsigned char key, int x, int y)
{
	//����1
	if(key == 'Z'|| key == 'z') //�Ŵ�
	{
		mx += 0.01;
		my += 0.01;
		mz += 0.01;
	}
	if(key == 'X'|| key == 'x') //��С
	{
		mx -= 0.01;
		my -= 0.01;
		mz -= 0.01;
	}
	if(key == 'A'|| key == 'a') //��x�Ḻ�����ƶ�
	{
		ax -= 0.01f;
	}
	if(key == 'D'|| key == 'd') //��x���������ƶ�
	{
		ax += 0.01f;
	}
	if(key == 'S'|| key == 's') //��y�Ḻ�����ƶ�
	{
		ay -= 0.01f;
	}
	if(key == 'W'|| key == 'w') //��y���������ƶ�
	{
		ay += 0.01f;
	}
	if(key == 'E'|| key == 'e') //��z�Ḻ�����ƶ�
	{
		az -= 0.01f;
	}
	if(key == 'Q'|| key == 'q') //��z���������ƶ�
	{
		az += 0.01f;
	}
	if(key == 'U'||key == 'u') //��x��˳ʱ��ת��
	{
		axis = 0;
		theta[axis] += 5.0;
		if (theta[axis] > 360.0)
			theta[axis] -= 360.0;
	}
	if(key == 'J'||key == 'j') //��y��˳ʱ��ת��
	{
		axis = 1;
		theta[axis] += 5.0;
		if (theta[axis] > 360.0)
			theta[axis] -= 360.0;
	}
	if(key == 'N'||key == 'n') //��z��˳ʱ��ת��
	{
		axis = 2;
		theta[axis] += 5.0;
		if (theta[axis] > 360.0)
			theta[axis] -= 360.0;
	}

	//����2
	if(key == 'C'|| key == 'c') //�Ŵ�
	{
		nx += 0.01;
		ny += 0.01;
		nz += 0.01;
	}
	if(key == 'V'|| key == 'v') //��С
	{
		nx -= 0.01;
		ny -= 0.01;
		nz -= 0.01;
	}
	if(key == 'F'|| key == 'f') //��x�Ḻ�����ƶ�
	{
		bx -= 0.01f;
	}
	if(key == 'H'|| key == 'h') //��x���������ƶ�
	{
		bx += 0.01f;
	}
	if(key == 'G'|| key == 'g') //��y�Ḻ�����ƶ�
	{
		by -= 0.01f;
	}
	if(key == 'T'|| key == 't') //��y���������ƶ�
	{
		by += 0.01f;
	}
	if(key == 'Y'|| key == 'y') //��z�Ḻ�����ƶ�
	{
		bz -= 0.01f;
	}
	if(key == 'R'|| key == 'r') //��z���������ƶ�
	{
		bz += 0.01f;
	}
	if(key == 'I'||key == 'i') //��x��˳ʱ��ת��
	{
		axis2 = 0;
		theta2[axis2] += 5.0;
		if (theta2[axis2] > 360.0)
			theta2[axis2] -= 360.0;
	}
	if(key == 'K'||key == 'k') //��y��˳ʱ��ת��
	{
		axis2 = 1;
		theta2[axis2] += 5.0;
		if (theta2[axis2] > 360.0)
			theta2[axis2] -= 360.0;
	}
	if(key == 'M'||key == 'm') //��z��˳ʱ��ת��
	{
		axis2 = 2;
		theta2[axis2] += 5.0;
		if (theta2[axis2] > 360.0)
			theta2[axis2] -= 360.0;
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
		ax = -0.5f; //��һֻ�������
		ay = 0.0f;
		az = 0.0f;
		bx= 0.5f; //�ڶ�ֻ�������
		by = 0.0f;
		bz = 0.0f;
		mx = 1.0f; //��һֻ�����ű���
		my = 1.0f;
		mz = 1.0f;
		nx = 1.0f; //�ڶ�ֻ�����ű���
		ny = 1.0f;
		nz = 1.0f;
		display();
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

	glutCreateMenu(mymenu); //�Ҽ��˵�
	glutAddMenuEntry("Clear Screen", 1);
	glutAddMenuEntry("Restore", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();
    glutMainLoop();
}



