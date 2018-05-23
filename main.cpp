#include<Windows.h>
#include<gl/GLUT.H>
#include<math.h>
GLUnurbsObj *pNurb=NULL;

// 定义窗口的宽度、高度
const int WIN_WIDTH = 600;
const int WIN_HEIGHT = 480;
BOOL isFullScreen = FALSE;

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

static GLfloat xRot=0.0f;
static GLfloat yRot=0.0f;
static GLfloat Rot=0.0f;

void Initial()
{
	glClearColor(1.0f,1.0f,1.0f,1.0f);
	//************************************************************************定义NURBS参数
	pNurb=gluNewNurbsRenderer();
	gluNurbsProperty(pNurb,GLU_SAMPLING_TOLERANCE,25.0f);
	gluNurbsProperty(pNurb,GLU_DISPLAY_MODE,(GLfloat)GLU_OUTLINE_POLYGON);
	//gluNurbsProperty(pNurb,GLU_DISPLAY_MODE,(GLfloat)GLU_FILL);
}

void ROTATEF()
{
	//glRotatef(330.0f,1.0f,0.0f,0.0f);
	glRotatef(xRot,0.0f,0.0f,1.0f);
	glRotatef(Rot,1.0f,0.0f,0.0f);
}

void ReDraw(void)
{
	GLUquadricObj *mySphere;
	mySphere = gluNewQuadric();
	gluQuadricDrawStyle(mySphere,  GLU_LINE);
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//************************************************************ 开启深度测试 实现遮挡关系
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);


	glMatrixMode(GL_MODELVIEW);
	
	glColor3ub(200,200,200);
//	glutSolidCone(3.0,3.0,12,12);

	
	
	//******************************************************火箭主体 
	glPushMatrix();
		
	//	glutSolidCube(2.0);
		ROTATEF();
		
	
		glRotatef(90.0, -1.0, 0.0, 0.0);
		
		gluCylinder(mySphere, 1.0, 1.0, 10.0, 120, 120);     //主体圆柱 
		glTranslatef(0.0, 0.0, 10.0);						//移到顶 
		gluCylinder(mySphere, 1.0, 0.1, 1.5, 120, 120);
		
		glTranslatef(0.0, 0.0, -10.5);						
		gluCylinder(mySphere, 0.7, 0.1, 1.0, 120, 120);		//发动机 		
			
	
	glPopMatrix();
 
	
	
	//******************************************************推进器1号 
	glPushMatrix();
		ROTATEF();
		glRotatef(90.0, -1.0, 0.0, 0.0);	
		glTranslatef(0.0, 0.0, -4.5);						//移到顶,绘制B曲面 
	
		glTranslatef(2.0, 0.0, 4.5);					//
		gluCylinder(mySphere, 0.5, 0.5, 4.5, 120, 120);		//圆柱 
		glTranslatef(0.0, 0.0, 4.5);						//移到顶 
//		gluCylinder(mySphere, 0.5, 0.1, 2.0, 120, 120);
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
		glRotatef(90.0, -1.0, 0.0, 0.0);
		glTranslatef(-2.0, 0.0, 0.0);
		gluCylinder(mySphere, 0.5, 0.5, 4.5, 120, 120);
		glTranslatef(0.0, 0.0, 4.5);						//移到顶
//		gluCylinder(mySphere, 0.5, 0.1, 2.0, 120, 120);     //圆锥头 
		glTranslatef(0.0, 0.0, -5.0);						
		gluCylinder(mySphere, 0.3, 0.1, 1.0, 120, 120);		//发动机
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
		glRotatef(90.0, -1.0, 0.0, 0.0);
		glTranslatef(0.0, 2.0, 0.0);
		gluCylinder(mySphere, 0.5, 0.5, 4.5, 120, 120);
		glTranslatef(0.0, 0.0, 4.5);						//移到顶
//		gluCylinder(mySphere, 0.5, 0.1, 2.0, 120, 120);		//圆锥头 
		glTranslatef(0.0, 0.0, -5.0);						
		gluCylinder(mySphere, 0.3, 0.1, 1.0, 120, 120);		//发动机
	
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
		glRotatef(90.0, -1.0, 0.0, 0.0);
		glTranslatef(0.0, -2.0, 0.0);
		gluCylinder(mySphere, 0.5, 0.5, 4.5, 120, 120);
		glTranslatef(0.0, 0.0, 4.5);						//移到顶
//		gluCylinder(mySphere, 0.5, 0.1, 2.0, 120, 120);
		glTranslatef(0.0, 0.0, -5.0);						
		gluCylinder(mySphere, 0.3, 0.1, 1.0, 120, 120);		//发动机
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
	
	
		
	

	//************************************************************ 推进器2号头 
    //绘制控制点与控制线
  	glColor3ub(200,200,200);
  
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
		ROTATEF();
		
		glRotatef(90.0, -1.0, 0.0, 0.0);
		glTranslatef(2.0, 0.0, 4.5);					//移动函数 
		glRotatef(-90.0, -1.0, 0.0, 0.0);	
		
		glRotatef(90.0, 0.0, 1.0, 0.0);	
		
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
		
		*/ 
	
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
		
		*/ 
	
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





	glutSwapBuffers();
}

void SpecialKeys(int key,int x,int y)
{
	if(key==GLUT_KEY_UP)	xRot+=5.0f;
	if(key==GLUT_KEY_DOWN)	xRot-=5.0f;
	if(key==GLUT_KEY_LEFT)
	{
		Rot-=5.0f;
	}
	if(key==GLUT_KEY_RIGHT)
	{
		Rot+=5.0f;
	}
//	if(xRot>360.0f)	xRot=0.0f;
//	if(xRot<-360.0f)	xRot=0.0f;
//	if(Rot>360.0f)	Rot=0.0f;
//	if(Rot<-360.0f)	Rot=0.0f;
	glutPostRedisplay();
}

void ChangeSize(int w,int h)
{
	if(h==0)
		h=1;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLdouble)w/(GLdouble)h,1.0,80.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f,-0.0f,-20.0f);//***********************************************************
}

void arrow_keys(int a_keys, int x, int y)   //F1满屏操作 
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
		default:
			break;
	}
}

int main(int argc,char* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowPosition(100, 100);     
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT); 
	glutCreateWindow("  ");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(ReDraw);
	glutSpecialFunc(SpecialKeys);
//	glutSpecialFunc(arrow_keys);		//指定特殊的按键回调函数。按F1满屏操作 
	Initial();
	glutMainLoop();
	return 0;
}
