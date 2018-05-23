#include <windows.h>	
#include <gl/glut.h>	
#include "Texture.h"	
#include<math.h>

#define MAXTEXTURE	6

// 定义窗口的宽度、高度
const int WIN_WIDTH = 600;
const int WIN_HEIGHT = 480;
BOOL isFullScreen = FALSE;
// 用户变量定义
GLfloat	ep_Angle;
GLfloat	es_Angle;
GLfloat	mp_Angle;
GLfloat	ms_Angle;
GLuint	texture[MAXTEXTURE];											
GLUquadricObj *quadric;													// 创建二次曲面对象
GLfloat	angle_Z;						
GLfloat LightAmbient[] = { 1.0f, 1.0f, 1.0f, 0.0f };					// 定义环境光的颜色
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 0.0f };					// 定义漫反射光的颜色
GLfloat LightPosition[] = { 500.0f, 500.0f, 500.0f, 1.0f };					// 定义光源的位置（定位光源）

//GLfloat fogColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};							// 雾的颜色为紫色
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

// OpenGL初始化
void InitGL(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	// 载入纹理
	BuildTexture("Data/1.bmp", texture[0]);								// 载入BMP,JPG,GIF等文件,载入图片并转换为纹理
	BuildTexture("Data/2.bmp", texture[1]);
	BuildTexture("Data/3.bmp", texture[2]);
	BuildTexture("Data/4.bmp", texture[3]);
	BuildTexture("Data/5.bmp", texture[4]);
	BuildTexture("Data/6.bmp", texture[5]);
	glEnable(GL_TEXTURE_2D);									
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);						// 设置环境光
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);						// 设置漫反射光
//建立二次曲面对象，为绘制地球，月亮太阳做准备
	quadric = gluNewQuadric();								
	gluQuadricTexture(quadric, GLU_TRUE);							
	gluQuadricDrawStyle(quadric, GLU_FILL);								// 用面填充
	glEnable(GL_LIGHTING);											
	glEnable(GL_LIGHT1);                                            
	// 设置雾的各种参数
	glFogi(GL_FOG_MODE, GL_LINEAR);										// 雾的类型
	glFogfv(GL_FOG_COLOR, fogColor);                  					// 雾的颜色
	glFogf(GL_FOG_DENSITY, 0.02f);                 						// 雾的浓度
	glHint(GL_FOG_HINT, GL_DONT_CARE);                   			
	glFogf(GL_FOG_START, 1.0f);                          				// 雾的开始深度
	glFogf(GL_FOG_END, 30.0f);                            				// 雾的终止深度
//	glEnable(GL_FOG);													// 启用雾
}
//循环控制
void xun()
{
	int i=1;
	while(i<3550000)
	{
		i++;
	}
}
GLdouble angle1=10,dis=-8,nucleusx=1,nucleusz=0;

// 场景绘制函数
void Display(void)
{
	//*****************************************
	GLUquadricObj *mySphere;
	mySphere = gluNewQuadric();
	gluQuadricDrawStyle(mySphere,  GLU_LINE);
	//*****************************************
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.5, 0.0f, dis);									// 将坐标系移入屏幕8.0f

	glRotatef(angle1, nucleusx ,0.0f, nucleusz);
	glEnable(GL_LIGHT0);												// 打开光源0
	//=============================绘制背景星空
	glPushMatrix ();						
		glTranslatef(0.0f, 0.0f,-10.0f);					//移动
		glRotatef (angle_Z, 0.0f, 0.0f, 1.0f);				//旋转
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[1]);							// 绑定星空纹理
		glBegin(GL_QUADS); 
			glNormal3f( 0.0f, 0.0f, 1.0f);									//设置法向量
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-20.0f, -20.0f, -15.0f);    //用于绘制图形时指定纹理的坐标(x,y)
			glTexCoord2f(6.0f, 0.0f); glVertex3f( 20.0f, -20.0f, -15.0f);
			glTexCoord2f(6.0f, 6.0f); glVertex3f( 20.0f,  20.0f, -15.0f);
			glTexCoord2f(0.0f, 6.0f); glVertex3f(-20.0f,  20.0f, -15.0f);
		glEnd();
		glDisable(GL_DEPTH_TEST);
	glPopMatrix ();		


	
	//==========================绘制太阳
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glEnable(GL_BLEND);						
	glDisable(GL_DEPTH_TEST);	
	
	//===============绘制太阳光晕
	glDisable(GL_LIGHTING);												// 关闭光照
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);									// 基于源象素alpha通道值的半透明混合函数
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
	
	glEnable(GL_LIGHTING);												// 开启光照
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);					// 设置光源1的当前位置
	glEnable(GL_TEXTURE_2D );	
				
	glBindTexture(GL_TEXTURE_2D, texture[5]);	
	glRotatef(ep_Angle, 0.0f, 1.0f, 0.0f);
	gluSphere(quadric, 0.1f, 32, 32);									// 绘制太阳球体



	//===============================绘制地球

	glDisable(GL_LIGHT0);
	glRotatef(ep_Angle, 0.0f, 1.0f, 0.0f);								// 将坐标系绕Y轴旋转ep_Angle角度  控制地球公转
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);								// 将坐标系绕X轴旋转-90度
	glTranslatef(1.0f, -1.0f, 2.0f);										// 将坐标系右移10.0f
	glBindTexture(GL_TEXTURE_2D, texture[0]);			
	glPushMatrix ();													
		glRotatef(es_Angle, 0.0f, 0.0f, 1.0f);								// 将坐标系绕Z轴旋转es_Angle角度  控制地球自转
		gluSphere(quadric, 0.3f, 32, 32);									// 地球球体
	glPopMatrix ();			
		
	glTranslatef(5.5f, 5.0f, 10.0f);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
//	glRotatef(ms_Angle, 0.0f, 0.0f, 1.0f);								// 将坐标系绕Z轴旋转ms_Angle角度 控制月亮自转

	//******************************************************火箭主体 
	glPushMatrix();
		
	//	glutSolidCube(2.0);
		ROTATEF();
//		glRotatef(90.0, -1.0, 0.0, 0.0);
		glScalef(0.2,0.2,0.2);  //缩小函数
		glTranslatef(0,0,disx);

		gluCylinder(quadric, 1.0, 1.0, 10.0, 120, 120);     //主体圆柱 
		glTranslatef(0.0, 0.0, 10.0);						//移到顶 
		gluCylinder(quadric, 1.0, 0.1, 1.5, 120, 120);
		
		glTranslatef(0.0, 0.0, -10.5);						
		gluCylinder(quadric, 0.7, 0.1, 1.0, 120, 120);		//发动机 		
	glPopMatrix();	
		//******************************************************推进器1号 
	glPushMatrix();
		ROTATEF();
		
	//	glRotatef(90.0, -1.0, 0.0, 0.0);
		glScalef(0.2,0.2,0.2);  //缩小函数	
		glTranslatef(0,0,disx);	

		glTranslatef(0.0, 0.0, -4.5);						//移到顶,绘制B曲面 
	
		glTranslatef(2.0, 0.0, 4.5);					//
		gluCylinder(quadric, 0.5, 0.5, 4.5, 120, 120);		//圆柱 
		glTranslatef(0.0, 0.0, 4.5);						//移到顶 
		gluCylinder(quadric, 0.5, 0.1, 2.0, 120, 120);
		glTranslatef(0.0, 0.0, -5.0);						
		gluCylinder(mySphere, 0.3, 0.1, 1.0, 120, 120);		//发动机 
		glTranslatef(0.5, 0.0, 0.5);
		glBegin(GL_POLYGON); 
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.7f,0.0f,0.0f);
			glVertex3f(0.7f,0.0f,0.7f);  
			glVertex3f(0.0f,0.0f,1.5f); 
			glVertex3f(0.0, 0.0, 0.0);	
		glEnd();
		
	glPopMatrix();	
	
	
	//******************************************************推进器2号 
	glPushMatrix();
		ROTATEF();
//		glRotatef(90.0, -1.0, 0.0, 0.0);
		glScalef(0.2,0.2,0.2);  //缩小函数
		glTranslatef(0,0,disx);

		glTranslatef(-2.0, 0.0, 0.0);
		gluCylinder(quadric, 0.5, 0.5, 4.5, 120, 120);
		glTranslatef(0.0, 0.0, 4.5);						//移到顶
		gluCylinder(quadric, 0.5, 0.1, 2.0, 120, 120);     //圆锥头 
		glTranslatef(0.0, 0.0, -5.0);						
		gluCylinder(quadric, 0.3, 0.1, 1.0, 120, 120);		//发动机
		glTranslatef(-0.5, 0.0, 0.5);
		glBegin(GL_POLYGON); 
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(-0.7f,0.0f,0.0f);
			glVertex3f(-0.7f,0.0f,0.7f);  
			glVertex3f(0.0f,0.0f,1.5f); 
			glVertex3f(0.0, 0.0, 0.0);	
		glEnd();		
	glPopMatrix();	
	
	//******************************************************推进器3号 
	glPushMatrix();
		ROTATEF();
//		glRotatef(90.0, -1.0, 0.0, 0.0);
		glScalef(0.2,0.2,0.2);  //缩小函数
		glTranslatef(0,0,disx);

		glTranslatef(0.0, 2.0, 0.0);
		gluCylinder(quadric, 0.5, 0.5, 4.5, 120, 120);
		glTranslatef(0.0, 0.0, 4.5);						//移到顶
		gluCylinder(quadric, 0.5, 0.1, 2.0, 120, 120);		//圆锥头 
		glTranslatef(0.0, 0.0, -5.0);						
		gluCylinder(quadric, 0.3, 0.1, 1.0, 120, 120);		//发动机
	
		glTranslatef(0.0, 0.5, 0.5);
		glBegin(GL_POLYGON); 
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0f,0.7f,0.0f);
			glVertex3f(0.0f,0.7f,0.7f);  
			glVertex3f(0.0f,0.0f,1.5f); 
			glVertex3f(0.0, 0.0, 0.0);	
		glEnd();		
	glPopMatrix();	
		
	//******************************************************推进器4号 
	glPushMatrix();
		ROTATEF();
//		glRotatef(90.0, -1.0, 0.0, 0.0);
		glScalef(0.2,0.2,0.2);  //缩小函数
		glTranslatef(0,0,disx);
		glTranslatef(0.0, -2.0, 0.0);

		gluCylinder(quadric, 0.5, 0.5, 4.5, 120, 120);
		glTranslatef(0.0, 0.0, 4.5);						//移到顶
		gluCylinder(quadric, 0.5, 0.1, 2.0, 120, 120);
		glTranslatef(0.0, 0.0, -5.0);						
		gluCylinder(quadric, 0.3, 0.1, 1.0, 120, 120);		//发动机
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

	//************************************************************ 推进器2号头 
    //绘制控制点与控制线
  //	glColor3ub(200,200,200);
  
	glPushMatrix();					
		ROTATEF();
		
		glRotatef(90.0, -1.0, 0.0, 0.0);
		glTranslatef(-2.0, 0.0, 4.5);					//移动函数 
		glRotatef(-90.0, -1.0, 0.0, 0.0);	
		
		glRotatef(90.0, 0.0, -1.0, 0.0);	
		
		glScalef(0.5,0.5,0.5);  //缩小函数

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
	

	//************************************************************ 推进器1号头 
	glPushMatrix();
	//	ROTATEF();
		
		glRotatef(90.0, -1.0, 0.0, 0.0);
		glTranslatef(2.0, 0.0, 4.5);					//移动函数 
		glRotatef(-90.0, -1.0, 0.0, 0.0);	
		
		glRotatef(90.0, 0.0, 1.0, 0.0);	
		glScalef(0.2,0.2,0.2);  //缩小函数
		glScalef(0.5,0.5,0.5);  //缩小函数

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
	
	
	//************************************************************ 推进器3号头 
	glPushMatrix();
		ROTATEF();
		
		glRotatef(90.0, -1.0, 0.0, 0.0);
		glTranslatef(0.0, 2.0, 4.5);					//移动函数 
		glRotatef(-90.0, -1.0, 0.0, 0.0);	
		
		glRotatef(180.0, 0.0, 1.0, 0.0);	
		
		glScalef(0.5,0.5,0.5);  //缩小函数

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
	    //绘制控制线
	    
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
	//************************************************************ 推进器4号头 
	glPushMatrix();
		ROTATEF();
		
		glRotatef(90.0, -1.0, 0.0, 0.0);
		glTranslatef(0.0, -2.0, 4.5);					//移动函数 
		glRotatef(-90.0, -1.0, 0.0, 0.0);	
		
		glRotatef(0.0, 0.0, 1.0, 0.0);	
		
		glScalef(0.5,0.5,0.5);  //缩小函数

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
	    //绘制控制线
	    
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

	glTranslatef(15.0f, 0.0f, 0.0f);										// 将坐标系右移10.0f
	

	//===============================绘制地球

	glDisable(GL_LIGHT0);
	glRotatef(ep_Angle, 0.0f, 1.0f, 0.0f);								// 将坐标系绕Y轴旋转ep_Angle角度  控制地球公转
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);								// 将坐标系绕X轴旋转-90度
	glTranslatef(10.0f, 10.0f, 0.0f);										// 将坐标系右移10.0f
	glBindTexture(GL_TEXTURE_2D, texture[0]);			
	glPushMatrix ();													
	glRotatef(es_Angle, 0.0f, 0.0f, 1.0f);								// 将坐标系绕Z轴旋转es_Angle角度  控制地球自转
	gluSphere(quadric, 6.3f, 32, 32);									// 地球球体
	glPopMatrix ();					
	//=====================绘制月亮
	glRotatef(mp_Angle, 0.0f, 0.0f, 1.0f);								// 将坐标系绕Z轴旋转mp_Angle角度 控制月亮公转
	glBindTexture(GL_TEXTURE_2D, texture[3]);						
	glTranslatef(7.5f, 0.0f, 0.0f);										// 右移0.5f
	glRotatef(ms_Angle, 0.0f, 0.0f, 1.0f);								// 将坐标系绕Z轴旋转ms_Angle角度 控制月亮自转
	gluSphere(quadric, 0.9, 32, 32);									// 绘制月亮星体
	//***********************************************************************




	// 变量更新
	ep_Angle += 0.01f;
	mp_Angle += 0.15f;
	es_Angle += 0.12f;
	ms_Angle += 0.15f;
	angle_Z += 0.01f;
	xun();
	gluLookAt(0,100,0,0,0,0,0,0,0);
	glutSwapBuffers();		// 交换双缓存
}
// 设置窗口改变大小时的处理函数
void Reshape(int width, int height)
{
	if (height==0)
	{
		height=1;
	}
	glViewport(0,0,width,height);
	// 设置投影矩阵
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
// 键盘按键动作的处理函数（有对应ASCII码的按键）
void Keyboard (unsigned char key, int x, int y)
{
	switch(key) {
	case 27:				// 按ESC键时退出程序
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
// 键盘按键动作的处理函数（无对应ASCII码的按键）
void arrow_keys(int a_keys, int x, int y)
{
	switch(a_keys) {
		case GLUT_KEY_F1:		// 按F1键时切换窗口/全屏模式
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
//时钟控制
void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000000,TimerFunc,1);
}
// 程序主函数
void main(int argc, char** argv)
{
	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);					
	glutInitWindowPosition(30,30);								
	glutCreateWindow("地球的公转及自转以及地月旋转");			
	InitGL();					
	glutDisplayFunc(Display);	
	glutReshapeFunc(Reshape);	
	glutKeyboardFunc(Keyboard);	
	glutSpecialFunc(arrow_keys);
	glutIdleFunc(Display);		
	glutMainLoop();				
}