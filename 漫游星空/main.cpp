#include <windows.h>	
#include <gl/glut.h>	
#include "Texture.h"	
#include<math.h>

#define MAXTEXTURE	6

// ���崰�ڵĿ�ȡ��߶�
const int WIN_WIDTH = 600;
const int WIN_HEIGHT = 480;
BOOL isFullScreen = FALSE;
// �û���������
GLfloat	ep_Angle;
GLfloat	es_Angle;
GLfloat	mp_Angle;
GLfloat	ms_Angle;
GLuint	texture[MAXTEXTURE];											
GLUquadricObj *quadric;													// ���������������
GLfloat	angle_Z;						
GLfloat LightAmbient[] = { 1.0f, 1.0f, 1.0f, 0.0f };					// ���廷�������ɫ
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 0.0f };					// ��������������ɫ
GLfloat LightPosition[] = { 500.0f, 500.0f, 500.0f, 1.0f };					// �����Դ��λ�ã���λ��Դ��

//GLfloat fogColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};							// �����ɫΪ��ɫ
GLfloat fogColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};	

//*****************************************************************************

GLUnurbsObj *pNurb=NULL;

GLfloat ctrlPoints[4][4][3]={	{	{-1.0f,0.0f,0.0f},  //p01
									{-1.0f,0.0f,-0.5f}, //p02
									{-1.0f,2.0f,-0.5f},  //p03
									{0.0f,6.0f,-0.9f}},  //p04
								{	{-1.0f,0.0f,1.0f},
									{-1.0f,0.0f,2.0f},
									{-1.0f,2.0f,2.0f},
									{0.0f,6.0f,-0.9f}},
								{	{1.0f,0.0f,1.0f},
									{1.0f,0.0f,2.0f},
									{1.0f,2.0f,2.0f},
									{0.0f,6.0f,-0.9f}},
								{	{1.0f,0.0f,0.0f},
									{1.0f,0.0f,-0.5f},
									{1.0f,2.0f,-0.5f},
									{0.0f,6.0f,-0.9f}}};

GLfloat Knots[8]={0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f};

GLfloat ctrlPoints_1[8][3] = {{-4.0, 0.0, 0.0},{-2.0, 3.0, 0.0},
							  {0.0, 4.0, 0.0},{2.0, 3.0, 0.0},
							  {4.0, 0.0, 0.0},{6.0, -1.0, 0.0},
							  {7.0, -1.0, 0.0},{8.0, 1.0, 0.0}};


int i,j;
static GLfloat xRot=0.0f;
static GLfloat yRot=0.0f;
static GLfloat Rot=0.0f;

GLdouble disx=1,disy=1,disz=1;
void ROTATEF()
{
	//glRotatef(330.0f,1.0f,0.0f,0.0f);
	glRotatef(xRot,1.0f,0.0f,0.0f);
	glRotatef(Rot,0.0f,1.0f,0.0f);
//	glRotatef(disx,0.0f,0.0f,1.0f);
	//glTranslatef(disx,disy,disz);

}
//*****************************************************************************

// OpenGL��ʼ��
void InitGL(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	// ��������
	BuildTexture("Data/1.bmp", texture[0]);								// ����BMP,JPG,GIF���ļ�,����ͼƬ��ת��Ϊ����
	BuildTexture("Data/2.bmp", texture[1]);
	BuildTexture("Data/3.bmp", texture[2]);
	BuildTexture("Data/4.bmp", texture[3]);
	BuildTexture("Data/5.bmp", texture[4]);
	BuildTexture("Data/6.bmp", texture[5]);
	glEnable(GL_TEXTURE_2D);									
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);						// ���û�����
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);						// �����������
//���������������Ϊ���Ƶ�������̫����׼��
	quadric = gluNewQuadric();								
	gluQuadricTexture(quadric, GLU_TRUE);							
	gluQuadricDrawStyle(quadric, GLU_FILL);								// �������
	glEnable(GL_LIGHTING);											
	glEnable(GL_LIGHT1);                                            
	// ������ĸ��ֲ���
	glFogi(GL_FOG_MODE, GL_LINEAR);										// �������
	glFogfv(GL_FOG_COLOR, fogColor);                  					// �����ɫ
	glFogf(GL_FOG_DENSITY, 0.02f);                 						// ���Ũ��
	glHint(GL_FOG_HINT, GL_DONT_CARE);                   			
	glFogf(GL_FOG_START, 1.0f);                          				// ��Ŀ�ʼ���
	glFogf(GL_FOG_END, 30.0f);                            				// �����ֹ���
//	glEnable(GL_FOG);													// ������
}
//ѭ������
void xun()
{
	int i=1;
	while(i<3550000)
	{
		i++;
	}
}
GLdouble angle1=10,dis=-8,nucleusx=1,nucleusz=0;

// �������ƺ���
void Display(void)
{
	//*****************************************
	GLUquadricObj *mySphere;
	mySphere = gluNewQuadric();
	gluQuadricDrawStyle(mySphere,  GLU_LINE);
	//*****************************************
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.5, 0.0f, dis);									// ������ϵ������Ļ8.0f

	glRotatef(angle1, nucleusx ,0.0f, nucleusz);
	glEnable(GL_LIGHT0);												// �򿪹�Դ0
	//=============================���Ʊ����ǿ�
	glPushMatrix ();						
		glTranslatef(0.0f, 0.0f,-10.0f);					//�ƶ�
		glRotatef (angle_Z, 0.0f, 0.0f, 1.0f);				//��ת
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[1]);							// ���ǿ�����
		glBegin(GL_QUADS); 
			glNormal3f( 0.0f, 0.0f, 1.0f);									//���÷�����
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-20.0f, -20.0f, -15.0f);    //���ڻ���ͼ��ʱָ�����������(x,y)
			glTexCoord2f(6.0f, 0.0f); glVertex3f( 20.0f, -20.0f, -15.0f);
			glTexCoord2f(6.0f, 6.0f); glVertex3f( 20.0f,  20.0f, -15.0f);
			glTexCoord2f(0.0f, 6.0f); glVertex3f(-20.0f,  20.0f, -15.0f);
		glEnd();
		glDisable(GL_DEPTH_TEST);
	glPopMatrix ();		


	
	//==========================����̫��
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glEnable(GL_BLEND);						
	glDisable(GL_DEPTH_TEST);	
	
	//===============����̫������
	glDisable(GL_LIGHTING);												// �رչ���
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);									// ����Դ����alphaͨ��ֵ�İ�͸����Ϻ���
	glBegin(GL_QUADS);
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f,-2.5f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.5f,-2.5f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.5f, 2.5f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.5f, 2.5f, 0.0f);
	glEnd();
	
	glDisable(GL_BLEND);												
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	
	glEnable(GL_LIGHTING);												// ��������
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);					// ���ù�Դ1�ĵ�ǰλ��
	glEnable(GL_TEXTURE_2D );	
				
	glBindTexture(GL_TEXTURE_2D, texture[5]);	
	glRotatef(ep_Angle, 0.0f, 1.0f, 0.0f);
	gluSphere(quadric, 0.1f, 32, 32);									// ����̫������



	//===============================���Ƶ���

	glDisable(GL_LIGHT0);
	glRotatef(ep_Angle, 0.0f, 1.0f, 0.0f);								// ������ϵ��Y����תep_Angle�Ƕ�  ���Ƶ���ת
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);								// ������ϵ��X����ת-90��
	glTranslatef(1.0f, -1.0f, 2.0f);										// ������ϵ����10.0f
	glBindTexture(GL_TEXTURE_2D, texture[0]);			
	glPushMatrix ();													
		glRotatef(es_Angle, 0.0f, 0.0f, 1.0f);								// ������ϵ��Z����תes_Angle�Ƕ�  ���Ƶ�����ת
		gluSphere(quadric, 0.3f, 32, 32);									// ��������
	glPopMatrix ();			
		
	glTranslatef(5.5f, 5.0f, 10.0f);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
//	glRotatef(ms_Angle, 0.0f, 0.0f, 1.0f);								// ������ϵ��Z����תms_Angle�Ƕ� ����������ת

	//******************************************************������� 
	glPushMatrix();
		
	//	glutSolidCube(2.0);
		ROTATEF();
//		glRotatef(90.0, -1.0, 0.0, 0.0);
		glScalef(0.2,0.2,0.2);  //��С����
		glTranslatef(0,0,disx);

		gluCylinder(quadric, 1.0, 1.0, 10.0, 120, 120);     //����Բ�� 
		glTranslatef(0.0, 0.0, 10.0);						//�Ƶ��� 
		gluCylinder(quadric, 1.0, 0.1, 1.5, 120, 120);
		
		glTranslatef(0.0, 0.0, -10.5);						
		gluCylinder(quadric, 0.7, 0.1, 1.0, 120, 120);		//������ 		
	glPopMatrix();	
		//******************************************************�ƽ���1�� 
	glPushMatrix();
		ROTATEF();
		
	//	glRotatef(90.0, -1.0, 0.0, 0.0);
		glScalef(0.2,0.2,0.2);  //��С����	
		glTranslatef(0,0,disx);	

		glTranslatef(0.0, 0.0, -4.5);						//�Ƶ���,����B���� 
	
		glTranslatef(2.0, 0.0, 4.5);					//
		gluCylinder(quadric, 0.5, 0.5, 4.5, 120, 120);		//Բ�� 
		glTranslatef(0.0, 0.0, 4.5);						//�Ƶ��� 
		gluCylinder(quadric, 0.5, 0.1, 2.0, 120, 120);
		glTranslatef(0.0, 0.0, -5.0);						
		gluCylinder(mySphere, 0.3, 0.1, 1.0, 120, 120);		//������ 
		glTranslatef(0.5, 0.0, 0.5);
		glBegin(GL_POLYGON); 
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.7f,0.0f,0.0f);
			glVertex3f(0.7f,0.0f,0.7f);  
			glVertex3f(0.0f,0.0f,1.5f); 
			glVertex3f(0.0, 0.0, 0.0);	
		glEnd();
		
	glPopMatrix();	
	
	
	//******************************************************�ƽ���2�� 
	glPushMatrix();
		ROTATEF();
//		glRotatef(90.0, -1.0, 0.0, 0.0);
		glScalef(0.2,0.2,0.2);  //��С����
		glTranslatef(0,0,disx);

		glTranslatef(-2.0, 0.0, 0.0);
		gluCylinder(quadric, 0.5, 0.5, 4.5, 120, 120);
		glTranslatef(0.0, 0.0, 4.5);						//�Ƶ���
		gluCylinder(quadric, 0.5, 0.1, 2.0, 120, 120);     //Բ׶ͷ 
		glTranslatef(0.0, 0.0, -5.0);						
		gluCylinder(quadric, 0.3, 0.1, 1.0, 120, 120);		//������
		glTranslatef(-0.5, 0.0, 0.5);
		glBegin(GL_POLYGON); 
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(-0.7f,0.0f,0.0f);
			glVertex3f(-0.7f,0.0f,0.7f);  
			glVertex3f(0.0f,0.0f,1.5f); 
			glVertex3f(0.0, 0.0, 0.0);	
		glEnd();		
	glPopMatrix();	
	
	//******************************************************�ƽ���3�� 
	glPushMatrix();
		ROTATEF();
//		glRotatef(90.0, -1.0, 0.0, 0.0);
		glScalef(0.2,0.2,0.2);  //��С����
		glTranslatef(0,0,disx);

		glTranslatef(0.0, 2.0, 0.0);
		gluCylinder(quadric, 0.5, 0.5, 4.5, 120, 120);
		glTranslatef(0.0, 0.0, 4.5);						//�Ƶ���
		gluCylinder(quadric, 0.5, 0.1, 2.0, 120, 120);		//Բ׶ͷ 
		glTranslatef(0.0, 0.0, -5.0);						
		gluCylinder(quadric, 0.3, 0.1, 1.0, 120, 120);		//������
	
		glTranslatef(0.0, 0.5, 0.5);
		glBegin(GL_POLYGON); 
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0f,0.7f,0.0f);
			glVertex3f(0.0f,0.7f,0.7f);  
			glVertex3f(0.0f,0.0f,1.5f); 
			glVertex3f(0.0, 0.0, 0.0);	
		glEnd();		
	glPopMatrix();	
		
	//******************************************************�ƽ���4�� 
	glPushMatrix();
		ROTATEF();
//		glRotatef(90.0, -1.0, 0.0, 0.0);
		glScalef(0.2,0.2,0.2);  //��С����
		glTranslatef(0,0,disx);
		glTranslatef(0.0, -2.0, 0.0);

		gluCylinder(quadric, 0.5, 0.5, 4.5, 120, 120);
		glTranslatef(0.0, 0.0, 4.5);						//�Ƶ���
		gluCylinder(quadric, 0.5, 0.1, 2.0, 120, 120);
		glTranslatef(0.0, 0.0, -5.0);						
		gluCylinder(quadric, 0.3, 0.1, 1.0, 120, 120);		//������
		glTranslatef(0.0, -0.5, 0.5);
		glBegin(GL_POLYGON); 
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0f,-0.7f,0.0f);
			glVertex3f(0.0f,-0.7f,0.7f);  
			glVertex3f(0.0f,0.0f,1.5f); 
			glVertex3f(0.0, 0.0, 0.0);	
		glEnd();		
	glPopMatrix();			
	glPopMatrix();	
	
	
		
/*

	//************************************************************ �ƽ���2��ͷ 
    //���ƿ��Ƶ��������
  //	glColor3ub(200,200,200);
  
	glPushMatrix();					
		ROTATEF();
		
		glRotatef(90.0, -1.0, 0.0, 0.0);
		glTranslatef(-2.0, 0.0, 4.5);					//�ƶ����� 
		glRotatef(-90.0, -1.0, 0.0, 0.0);	
		
		glRotatef(90.0, 0.0, -1.0, 0.0);	
		
		glScalef(0.5,0.5,0.5);  //��С����

	    glPointSize(4.0f); 
	    glColor3f(1.0, 1.0, 0.0);
	
		gluBeginSurface(pNurb);
		gluNurbsSurface(pNurb,
						8,
						Knots,
						8,
						Knots,
						4*3,
						3,
						&ctrlPoints[0][0][0],
						4,
						4,
						GL_MAP2_VERTEX_3);
		gluEndSurface(pNurb);
	glPopMatrix();
	

	//************************************************************ �ƽ���1��ͷ 
	glPushMatrix();
	//	ROTATEF();
		
		glRotatef(90.0, -1.0, 0.0, 0.0);
		glTranslatef(2.0, 0.0, 4.5);					//�ƶ����� 
		glRotatef(-90.0, -1.0, 0.0, 0.0);	
		
		glRotatef(90.0, 0.0, 1.0, 0.0);	
		glScalef(0.2,0.2,0.2);  //��С����
		glScalef(0.5,0.5,0.5);  //��С����

	    glPointSize(4.0f); 
	    glColor3f(1.0, 1.0, 0.0);
	
		gluBeginSurface(pNurb);
		gluNurbsSurface(pNurb,
						8,
						Knots,
						8,
						Knots,
						4*3,
						3,
						&ctrlPoints[0][0][0],
						4,
						4,
						GL_MAP2_VERTEX_3);
		gluEndSurface(pNurb);
	
	glPopMatrix();
	
	
	//************************************************************ �ƽ���3��ͷ 
	glPushMatrix();
		ROTATEF();
		
		glRotatef(90.0, -1.0, 0.0, 0.0);
		glTranslatef(0.0, 2.0, 4.5);					//�ƶ����� 
		glRotatef(-90.0, -1.0, 0.0, 0.0);	
		
		glRotatef(180.0, 0.0, 1.0, 0.0);	
		
		glScalef(0.5,0.5,0.5);  //��С����

	    glPointSize(4.0f); 
	    glColor3f(1.0, 1.0, 0.0);
	    /*
	    glBegin(GL_POINTS);
	    for (int i = 0; i < 4; i++)
	    {
	        for (int j = 0; j < 4; j++)
	            glVertex3fv(ctrlPoints[i][j]);
	
	    }
	    glEnd();
	    //���ƿ�����
	    
	    glLineWidth(1.5f);
	    glColor3f(0.0,1.0,1.0); 
	    for ( i = 0; i < 4; i++)
	    {
	        glBegin(GL_LINE_STRIP);
	        for ( j = 0; j < 4; j++)
	            glVertex3fv(ctrlPoints[i][j]);
	        glEnd();
	
	        glBegin(GL_LINE_STRIP);
	        for ( j = 0; j < 4; j++)
	            glVertex3fv(ctrlPoints[j][i]);
	        glEnd();
	    }	
		
		
	
		gluBeginSurface(pNurb);
		gluNurbsSurface(pNurb,
						8,
						Knots,
						8,
						Knots,
						4*3,
						3,
						&ctrlPoints[0][0][0],
						4,
						4,
						GL_MAP2_VERTEX_3);
		gluEndSurface(pNurb);
	
	glPopMatrix();
	/*
	//************************************************************ �ƽ���4��ͷ 
	glPushMatrix();
		ROTATEF();
		
		glRotatef(90.0, -1.0, 0.0, 0.0);
		glTranslatef(0.0, -2.0, 4.5);					//�ƶ����� 
		glRotatef(-90.0, -1.0, 0.0, 0.0);	
		
		glRotatef(0.0, 0.0, 1.0, 0.0);	
		
		glScalef(0.5,0.5,0.5);  //��С����

	    glPointSize(4.0f); 
	    glColor3f(1.0, 1.0, 0.0);
	    /*
	    glBegin(GL_POINTS);
	    for (int i = 0; i < 4; i++)
	    {
	        for (int j = 0; j < 4; j++)
	            glVertex3fv(ctrlPoints[i][j]);
	
	    }
	    glEnd();
	    //���ƿ�����
	    
	    glLineWidth(1.5f);
	    glColor3f(0.0,1.0,1.0); 
	    for (int i = 0; i < 4; i++)
	    {
	        glBegin(GL_LINE_STRIP);
	        for (int j = 0; j < 4; j++)
	            glVertex3fv(ctrlPoints[i][j]);
	        glEnd();
	
	        glBegin(GL_LINE_STRIP);
	        for (int j = 0; j < 4; j++)
	            glVertex3fv(ctrlPoints[j][i]);
	        glEnd();
	    }	
		
		//
	
		gluBeginSurface(pNurb);
		gluNurbsSurface(pNurb,
						8,
						Knots,
						8,
						Knots,
						4*3,
						3,
						&ctrlPoints[0][0][0],
						4,
						4,
						GL_MAP2_VERTEX_3);
		gluEndSurface(pNurb);
	
	glPopMatrix();

*/


//	glPopMatrix();

	glTranslatef(15.0f, 0.0f, 0.0f);										// ������ϵ����10.0f
	

	//===============================���Ƶ���

	glDisable(GL_LIGHT0);
	glRotatef(ep_Angle, 0.0f, 1.0f, 0.0f);								// ������ϵ��Y����תep_Angle�Ƕ�  ���Ƶ���ת
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);								// ������ϵ��X����ת-90��
	glTranslatef(10.0f, 10.0f, 0.0f);										// ������ϵ����10.0f
	glBindTexture(GL_TEXTURE_2D, texture[0]);			
	glPushMatrix ();													
	glRotatef(es_Angle, 0.0f, 0.0f, 1.0f);								// ������ϵ��Z����תes_Angle�Ƕ�  ���Ƶ�����ת
	gluSphere(quadric, 6.3f, 32, 32);									// ��������
	glPopMatrix ();					
	//=====================��������
	glRotatef(mp_Angle, 0.0f, 0.0f, 1.0f);								// ������ϵ��Z����תmp_Angle�Ƕ� ����������ת
	glBindTexture(GL_TEXTURE_2D, texture[3]);						
	glTranslatef(7.5f, 0.0f, 0.0f);										// ����0.5f
	glRotatef(ms_Angle, 0.0f, 0.0f, 1.0f);								// ������ϵ��Z����תms_Angle�Ƕ� ����������ת
	gluSphere(quadric, 0.9, 32, 32);									// ������������
	//***********************************************************************




	// ��������
	ep_Angle += 0.01f;
	mp_Angle += 0.15f;
	es_Angle += 0.12f;
	ms_Angle += 0.15f;
	angle_Z += 0.01f;
	xun();
	gluLookAt(0,100,0,0,0,0,0,0,0);
	glutSwapBuffers();		// ����˫����
}
// ���ô��ڸı��Сʱ�Ĵ�����
void Reshape(int width, int height)
{
	if (height==0)
	{
		height=1;
	}
	glViewport(0,0,width,height);
	// ����ͶӰ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
// ���̰��������Ĵ��������ж�ӦASCII��İ�����
void Keyboard (unsigned char key, int x, int y)
{
	switch(key) {
	case 27:				// ��ESC��ʱ�˳�����
		exit (0);
		break;
	case 'w':
		angle1+=1;
		nucleusx=1;
		break;
	case's':
		angle1-=1;
		nucleusx=1;
		break;
	case'a':
		angle1-=1;
		nucleusz=1;
		break;
	case'd':
		angle1-=1;
		nucleusz=1;
		break;
	case'i':
		dis+=0.5;
		break;
	case'o':
		dis-=0.5;
		break;
	case'j':
		disx+=0.5;
		disy+=0.5;
	//	disz+=0.5;
		break;
	case'k':
		disx-=0.5;
		disy-=0.5;
	//	disz-=0.5;
		break;
	default:
		break;
	}
}
// ���̰��������Ĵ��������޶�ӦASCII��İ�����
void arrow_keys(int a_keys, int x, int y)
{
	switch(a_keys) {
		case GLUT_KEY_F1:		// ��F1��ʱ�л�����/ȫ��ģʽ
			if(isFullScreen)
			{
				glutReshapeWindow(WIN_WIDTH, WIN_HEIGHT);
				glutPositionWindow(30, 30);
				isFullScreen = FALSE;
			}
			else
			{
				glutFullScreen();
				isFullScreen = TRUE;
			}
			break;

		case GLUT_KEY_UP:
			xRot+=1.0f;
			break;
		case GLUT_KEY_DOWN:
			xRot-=1.0f;
			break;
		case GLUT_KEY_LEFT:
			Rot-=1.0f;
			break;
		case GLUT_KEY_RIGHT:
			Rot+=1.0f;
			break;
		default:
			break;
	}
}
//ʱ�ӿ���
void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000000,TimerFunc,1);
}
// ����������
void main(int argc, char** argv)
{
	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);					
	glutInitWindowPosition(30,30);								
	glutCreateWindow("����Ĺ�ת����ת�Լ�������ת");			
	InitGL();					
	glutDisplayFunc(Display);	
	glutReshapeFunc(Reshape);	
	glutKeyboardFunc(Keyboard);	
	glutSpecialFunc(arrow_keys);
	glutIdleFunc(Display);		
	glutMainLoop();				
}