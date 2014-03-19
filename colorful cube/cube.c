/*在彩色立方体的六个面上贴上棋盘*/
#include<glut.h>
//#include <stdlib.h>
#define checkImageWidth 64
#define checkImageHeight 64
	GLfloat vertices[][3] = {
			-1.0,	-1.0,	-1.0,
			1.0,	-1.0,	-1.0,
			1.0,	1.0,	-1.0, 
			-1.0,	1.0,	-1.0, 
			-1.0,	-1.0,	1.0, 
			1.0,	-1.0,	1.0, 
			1.0,	1.0,	1.0, 
			-1.0,	1.0,	1.0
	};
	GLfloat colors[][4]={
	0.0,0.0,0.0,0.5,
	1.0,0.0,0.0,0.5,
	1.0,1.0,0.0,0.5,
	0.0,1.0,0.0,0.5,
	0.0,0.0,1.0,0.5,
	1.0,0.0,1.0,0.5,
	1.0,1.0,1.0,0.5,
	0.0,1.0,1.0,0.5
	};
void polygon(int a,int b,int c,int d)
{
glBegin(GL_POLYGON);
glColor4fv(colors[a]);
 glTexCoord2f(0.0,0.0);
 glVertex3fv(vertices[a]);
 glColor4fv(colors[b]);
 glTexCoord2f(0.0,1.0);
 glVertex3fv(vertices[b]);
 glColor4fv(colors[c]);
 glTexCoord2f(1.0,1.0);
 glVertex3fv(vertices[c]);
 glColor4fv(colors[d]);
 glTexCoord2f(1.0,0.0);
 glVertex3fv(vertices[d]);
 glEnd();
}
void colorcube()
{
/*把顶点与多边形的表面对应起来*/
 polygon(0,3,2,1);
 polygon(2,3,7,6);
 polygon(0,4,7,3);
 polygon(1,2,6,5);
 polygon(4,5,6,7);
 polygon(0,1,5,4);
}
static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;
void display(void)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
//	gluLookAt(1.0,1.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);
//	glTranslatef(0.0, 3.0, 0.0);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
    colorcube();	
    glutSwapBuffers(); 
}

void spinCube()
{
	int i;
	double acc = 0.999999999;

	theta[axis] += 0.3;
	if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
	for(i=0; i<327670;i++) acc = 1.0 / acc;
	glutPostRedisplay();
}

void keyboard(unsigned char btn,int x, int y)
{

	if(btn=='a')
	{
    
		axis = 0;
			
	}
	if(btn=='b') 
	{	
		axis = 1;
		

	}
	if(btn=='c') 
	{
		axis = 2;
		
	}
	
	

}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-4.0, 4.0, -3.0 * (GLfloat) h / (GLfloat) w,
            5.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-4.0 * (GLfloat) w / (GLfloat) h,
            4.0 * (GLfloat) w / (GLfloat) h, -3.0, 5.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{  
  GLubyte checkImage [checkImageWidth][ checkImageHeight][4];
// static GLuint texName;
 int i,j,c;
 for(i=0;i<checkImageWidth;i++)
	{
		for(j=0;j<checkImageHeight;j++)
		{
		 c=(((i&0x8)==0)^((j&0x8))==0)*255;
		 checkImage[i][j][0]=(GLubyte)c;
		 checkImage[i][j][1]=(GLubyte)c;
		 checkImage[i][j][2]=(GLubyte)c;
		 checkImage[i][j][3]=(GLubyte)255;
		}
     }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("彩色旋转立方体");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(spinCube);    
 	//glutMouseFunc(mouse);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
 glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,checkImageWidth,checkImageHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,checkImage);
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
 glutKeyboardFunc(keyboard);
 glClearColor(0.0,0.0,0.0,0.0); 
 glClear(GL_COLOR_BUFFER_BIT);
 glutMainLoop();
}

