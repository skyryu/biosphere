// twoAnimal.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include <stdio.h>
#include <GL/glut.h>
//#include <GL/glaux.h>

int teapotSel = 0;//record current selected teapot
//window size
GLsizei ww = 500;
GLsizei wh = 500;

//current mod view matrix
float m1[16];
float m2[16];

float project_matrix[16];


void selectObj1()
{
	glLoadName(1);
	glColor3f(1.0,1.0,1.0);

	glPushMatrix();
	glMultMatrixf(m1);
	glutWireTeapot(10);
	glPopMatrix();                                      
}
void selectObj2()
{
	glLoadName(2);
	glColor3f(0,1.0,1.0);

	glPushMatrix();
	glMultMatrixf(m2);
	glutWireTeapot(10);
	glPopMatrix();
}
void drawObjects1()
{
	glColor3f(1.0,1.0,1.0);
	
	glPushMatrix();
	glMultMatrixf(m1);
	glutWireTeapot(10);
	glPopMatrix();
}
void drawObjects2()
{
	glColor3f(0,1.0,1.0);

	glPushMatrix();
	glMultMatrixf(m2);
	glutWireTeapot(10);
	glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	drawObjects1();
	drawObjects2();
	
	glutSwapBuffers();
}

void processHits (GLint hits, GLuint buffer[])
{
	int i;
	GLuint names, *ptr;
	printf("hits = %d\n", hits);
	ptr=(GLuint *) buffer; 
	ptr+=3;
	for (i = 0; i < hits; i++) 
	{	// ��ÿ�����м�¼
			
			printf ("teaport %d ��ѡ��!\n",*ptr);
			if(*ptr == 1) teapotSel = 1;
			else if(*ptr == 2) teapotSel = 2;
			else teapotSel = 0;
			ptr++;
	}
}

void mouse(int button, int state, int x, int y)
{
	GLuint selectBuf[512];
	GLint hits;
	GLint viewport[4];
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		// �������ƻ�����
		glGetIntegerv(GL_VIEWPORT, viewport);
		glSelectBuffer (512, selectBuf);
		glRenderMode(GL_SELECT);
		// ��ʼ������ջ
		glInitNames();
		glPushName(0);
		glMatrixMode(GL_PROJECTION);
		glGetFloatv(GL_PROJECTION_MATRIX,project_matrix);
		glLoadIdentity();
		//����һ���Թ��Ϊ���ĵ� 5��5 ��ʰȡ����
		gluPickMatrix((GLdouble) x, (GLdouble) (viewport[3] - y), 5.0, 5.0, viewport);
		//gluLookAt(0,2,4,0,0,0,0,1,0);
		//gluPerspective(60,1,0,100);
		glOrtho(-50,50,-50,50,-50,50);
		
		glMatrixMode(GL_MODELVIEW);
		selectObj1();
		selectObj2();
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(project_matrix);

		glMatrixMode(GL_MODELVIEW);
		//glFlush();
		// ���������Ļ���ģʽ��hits �б���������Ϣ
		hits = glRenderMode(GL_RENDER);
		// ���������Ϣ�����ж϶����Ƿ�ѡ��
		
		processHits(hits, selectBuf);

		glutPostRedisplay();
	}
} 

void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	

	glOrtho(-50,50,-50,50,-50,50);
	//gluPerspective(45,1,0,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//initial m1,m2
	glPushMatrix();
	glTranslated(0,0,-5);
	glRotated(35,1,0,0);
	glGetFloatv(GL_MODELVIEW_MATRIX,m1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(10,0,-5);
	glRotated(35,1,0,0);
	glGetFloatv(GL_MODELVIEW_MATRIX,m2);
	glPopMatrix();
	glClearColor (0.0, 0.0, 0.0,1.0);
	glEnable(GLUT_DEPTH);
}

void myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45,1,0,100);
	glOrtho(-50,50,-50,50,-50,50);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	teapotSel = 0;
	ww=w;
	wh=h;
	//gluLookAt(0,0,-5,0,0,-10,0,1,0);
}

void keyboard(unsigned char key,int x,int y)
{
	glMatrixMode(GL_MODELVIEW);
	
	switch(key)
	{
	case 'w':
		if(teapotSel == 1)
		{
			glPushMatrix();
			glLoadMatrixf(m1);
			glTranslated(1,0,0);
			glGetFloatv(GL_MODELVIEW_MATRIX,m1);
			glPopMatrix();
		}
		break;
	case 's':
		if(teapotSel == 1)
		{
			glPushMatrix();
			glLoadMatrixf(m1);
			glTranslated(-1,0,0);
			glGetFloatv(GL_MODELVIEW_MATRIX,m1);
			glPopMatrix();
		}
		break;
	case 'a':
		if(teapotSel == 1)
		{
			glPushMatrix();
			glLoadMatrixf(m1);
			glRotated(5,0,1,0);
			glGetFloatv(GL_MODELVIEW_MATRIX,m1);
			glPopMatrix();
		}
		break;
	case 'd':
		if(teapotSel == 1)
		{
			glPushMatrix();
			glLoadMatrixf(m1);
			glRotated(-5,0,1,0);
			glGetFloatv(GL_MODELVIEW_MATRIX,m1);
			glPopMatrix();
		}
		break;
	case 'i'://up arrow
		if(teapotSel == 2)
		{
			glPushMatrix();
			glLoadMatrixf(m2);
			glTranslated(1,0,0);
			glGetFloatv(GL_MODELVIEW_MATRIX,m2);
			glPopMatrix();
		}
		break;
	case 'k'://down arrow
		if(teapotSel == 2)
		{
			glPushMatrix();
			glLoadMatrixf(m2);
			glTranslated(-1,0,0);
			glGetFloatv(GL_MODELVIEW_MATRIX,m2);
			glPopMatrix();
		}
		break;
	case 'j':// left
		if(teapotSel == 2)
		{
			glPushMatrix();
			glLoadMatrixf(m2);
			glRotated(5,0,1,0);
			glGetFloatv(GL_MODELVIEW_MATRIX,m2);
			glPopMatrix();
		}
		break;
	case 'l'://right
		if(teapotSel == 2)
		{
			glPushMatrix();
			glLoadMatrixf(m2);
			glRotated(-5,0,1,0);
			glGetFloatv(GL_MODELVIEW_MATRIX,m2);
			glPopMatrix();
		}
		break;
	default:break;
	}
	glutPostRedisplay();
}
int main(int argc, char * * argv)
{
	glutInit(&argc, argv);  
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("faceBook");
	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	
	myinit();
	glutMainLoop();
	return 0;
}

