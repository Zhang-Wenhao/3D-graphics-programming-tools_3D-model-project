/*
 * pig2.c
 *
 *  Created on: 2018年4月24日
 *      Author: 40360
 */
#include <GL/glut.h>
#include <windows.h>

#include <math.h>
int axis; //第一只猪旋转轴编号
int axis2; //第二只猪旋转轴编号
float theta[3] ={0.0, 0.0, 0.0}; //第一只猪每个轴的旋转角
float theta2[3] ={0.0, 0.0, 0.0}; //第二只猪每个轴的旋转角
const int n = 1000;
GLfloat ax = -0.5f; //第一只猪的坐标
GLfloat ay = 0.0f;
GLfloat az = 0.0f;
GLfloat bx= 0.5f; //第二只猪的坐标
GLfloat by = 0.0f;
GLfloat bz = 0.0f;
GLfloat mx = 1.0f; //第一只猪缩放倍数
GLfloat my = 1.0f;
GLfloat mz = 1.0f;
GLfloat nx = 1.0f; //第二只猪缩放倍数
GLfloat ny = 1.0f;
GLfloat nz = 1.0f;
const GLfloat Pi = 3.1415926536f; //圆周率

void drawPig()
{
	//glClearDepth(1.0f);// 设置深度缓存
	//glEnable(GL_DEPTH_TEST);// 启用深度测试
	//glDepthFunc(GL_LEQUAL);

	//第一只动物
	glLoadIdentity();
	glScalef(mx, my, mz);
	glTranslatef(ax, ay, az);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.5, 0.5);
	glTranslatef(0.15, -0.2, 0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //左前脚

	glLoadIdentity();
	glScalef(mx, my, mz);
	glTranslatef(ax, ay, az);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.5, 0.5);
	glTranslatef(-0.15, -0.2, 0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //右前脚

	glLoadIdentity();
	glScalef(mx, my, mz);
	glTranslatef(ax, ay, az);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.5, 0.5);
	glTranslatef(0.15, -0.2, -0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //左后脚

	glLoadIdentity();
	glScalef(mx, my, mz);
	glTranslatef(ax, ay, az);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.5, 0.5);
	glTranslatef(-0.15, -0.2, -0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //右后脚

	glLoadIdentity();
	glScalef(mx, my, mz);
	glTranslatef(ax, ay, az);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.5, 0.5);
	GLUquadricObj *quadratic;
	quadratic=gluNewQuadric();
	gluCylinder(quadratic,0.05f,0.05f,0.27f,50,50); //鼻子

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
	glEnd(); //左耳

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
	glEnd(); //右耳

	glLoadIdentity();
	glScalef(mx, my, mz);
	glTranslatef(ax, ay, az);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.8, 0.8);
	glutSolidSphere( 0.25f, 100, 100 );  //身体

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
    glEnd();//鼻子(表面)

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
    glEnd();//右鼻孔

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
    glEnd();//左鼻孔

	glLoadIdentity();
	glScalef(mx, my, mz);
	glTranslatef(ax, ay, az);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.05, 0.08, 0.23);
	glutSolidSphere( 0.013f, 1000, 1000 );  //左眼

	glLoadIdentity();
	glScalef(mx, my, mz);
	glTranslatef(ax, ay, az);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(-0.05, 0.08, 0.23);
	glutSolidSphere( 0.013f, 1000, 1000 );  //右眼

	//第二只动物
	glLoadIdentity();
	glScalef(nx, ny, nz);
	glTranslatef(bx, by, bz);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.8, 0.8);
	glTranslatef(0.15, -0.2, 0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //左前脚

	glLoadIdentity();
	glScalef(nx, ny, nz);
	glTranslatef(bx, by, bz);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.8, 0.8);
	glTranslatef(-0.15, -0.2, 0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //右前脚

	glLoadIdentity();
	glScalef(nx, ny, nz);
	glTranslatef(bx, by, bz);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.8, 0.8);
	glTranslatef(0.15, -0.2, -0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //左后脚

	glLoadIdentity();
	glScalef(nx, ny, nz);
	glTranslatef(bx, by, bz);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.8, 0.8);
	glTranslatef(-0.15, -0.2, -0.125);
	glutSolidSphere( 0.05f, 100, 100 ); //右后脚

	glLoadIdentity();
	glScalef(nx, ny, nz);
	glTranslatef(bx, by, bz);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.8, 0.8);
	GLUquadricObj *quadratic2;
	quadratic2=gluNewQuadric();
	gluCylinder(quadratic2,0.05f,0.05f,0.27f,50,50); //鼻子

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
	glEnd(); //左耳

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
	glEnd(); //右耳

	glLoadIdentity();
	glScalef(nx, ny, nz);
	glTranslatef(bx, by, bz);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.6, 0.7);
	glutSolidSphere( 0.25f, 100, 100 );  //身体

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
    glEnd();//鼻子(表面)

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
    glEnd();//右鼻孔

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
    glEnd();//左鼻孔

	glLoadIdentity();
	glScalef(nx, ny, nz);
	glTranslatef(bx, by, bz);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.05, 0.08, 0.23);
	glutSolidSphere( 0.013f, 1000, 1000 );  //左眼

	glLoadIdentity();
	glScalef(nx, ny, nz);
	glTranslatef(bx, by, bz);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(-0.05, 0.08, 0.23);
	glutSolidSphere( 0.013f, 1000, 1000 );  //右眼
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
	//动物1
	if(key == 'Z'|| key == 'z') //放大
	{
		mx += 0.01;
		my += 0.01;
		mz += 0.01;
	}
	if(key == 'X'|| key == 'x') //缩小
	{
		mx -= 0.01;
		my -= 0.01;
		mz -= 0.01;
	}
	if(key == 'A'|| key == 'a') //沿x轴负方向移动
	{
		ax -= 0.01f;
	}
	if(key == 'D'|| key == 'd') //沿x轴正方向移动
	{
		ax += 0.01f;
	}
	if(key == 'S'|| key == 's') //沿y轴负方向移动
	{
		ay -= 0.01f;
	}
	if(key == 'W'|| key == 'w') //沿y轴正方向移动
	{
		ay += 0.01f;
	}
	if(key == 'E'|| key == 'e') //沿z轴负方向移动
	{
		az -= 0.01f;
	}
	if(key == 'Q'|| key == 'q') //沿z轴正方向移动
	{
		az += 0.01f;
	}
	if(key == 'U'||key == 'u') //沿x轴顺时针转动
	{
		axis = 0;
		theta[axis] += 5.0;
		if (theta[axis] > 360.0)
			theta[axis] -= 360.0;
	}
	if(key == 'J'||key == 'j') //沿y轴顺时针转动
	{
		axis = 1;
		theta[axis] += 5.0;
		if (theta[axis] > 360.0)
			theta[axis] -= 360.0;
	}
	if(key == 'N'||key == 'n') //沿z轴顺时针转动
	{
		axis = 2;
		theta[axis] += 5.0;
		if (theta[axis] > 360.0)
			theta[axis] -= 360.0;
	}

	//动物2
	if(key == 'C'|| key == 'c') //放大
	{
		nx += 0.01;
		ny += 0.01;
		nz += 0.01;
	}
	if(key == 'V'|| key == 'v') //缩小
	{
		nx -= 0.01;
		ny -= 0.01;
		nz -= 0.01;
	}
	if(key == 'F'|| key == 'f') //沿x轴负方向移动
	{
		bx -= 0.01f;
	}
	if(key == 'H'|| key == 'h') //沿x轴正方向移动
	{
		bx += 0.01f;
	}
	if(key == 'G'|| key == 'g') //沿y轴负方向移动
	{
		by -= 0.01f;
	}
	if(key == 'T'|| key == 't') //沿y轴正方向移动
	{
		by += 0.01f;
	}
	if(key == 'Y'|| key == 'y') //沿z轴负方向移动
	{
		bz -= 0.01f;
	}
	if(key == 'R'|| key == 'r') //沿z轴正方向移动
	{
		bz += 0.01f;
	}
	if(key == 'I'||key == 'i') //沿x轴顺时针转动
	{
		axis2 = 0;
		theta2[axis2] += 5.0;
		if (theta2[axis2] > 360.0)
			theta2[axis2] -= 360.0;
	}
	if(key == 'K'||key == 'k') //沿y轴顺时针转动
	{
		axis2 = 1;
		theta2[axis2] += 5.0;
		if (theta2[axis2] > 360.0)
			theta2[axis2] -= 360.0;
	}
	if(key == 'M'||key == 'm') //沿z轴顺时针转动
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
	if(id == 1) //清除图像
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();
	}
	if(id == 2) //还原
	{
		glClear (GL_COLOR_BUFFER_BIT);
		theta[0] =0.0;
		theta[1] =0.0;
		theta[2] =0.0;
		theta2[0] =0.0;
		theta2[1] =0.0;
		theta2[2] =0.0;
		ax = -0.5f; //第一只猪的坐标
		ay = 0.0f;
		az = 0.0f;
		bx= 0.5f; //第二只猪的坐标
		by = 0.0f;
		bz = 0.0f;
		mx = 1.0f; //第一只猪缩放倍数
		my = 1.0f;
		mz = 1.0f;
		nx = 1.0f; //第二只猪缩放倍数
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
    glutCreateWindow("两只三维的猪");
    glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(mykey); //键盘响应

	glutCreateMenu(mymenu); //右键菜单
	glutAddMenuEntry("Clear Screen", 1);
	glutAddMenuEntry("Restore", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();
    glutMainLoop();
}



