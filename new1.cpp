//Compile with this commmand g++ new1.cpp -o p -L/usr/X11R6/lib/ -lGL -lGLU -lglut


#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>



GLuint textureID = 0;
void * data;
int w,h;
float ratio;
char * cur_file="";
bool l0_on=1;
bool l1_on=1;
float angular_speed=1.0f;
float x=0.0f,y=1.75f,z=5.0f;
float lx=0.0f,ly=0.0f,lz=-1.0f;



GLfloat green_light_ambient[] =
{0.0, 1.0, 0.0, 1.0},green_light_diffuse[] =
{0.0, 1.0, 0.0, 1.0},green_light_specular[] =
{0.0, 1.0, 0.0, 1.0}, white_light_ambient[] =
{1.0, 1.0, 1.0, 1.0}, white_light_diffuse[] =
{1.0, 1.0, 1.0, 1.0}, white_light_specular[] =
{1.0, 1.0, 1.0, 1.0};



GLfloat white_light_position[] =
{2.0, 2.0, 0.0, 0.0}, green_light_position[] =
{-2.0, 2.0, 0.0, 0.0};


GLfloat mat1_ambient[] =
{1.0f, 1.0f, 1.0f, 1.0f}, mat1_diffuse[] =
{1.0f, 1.0f, 1.0f, 1.0f}, mat1_specular[] =
{1.0f, 1.0f, 1.0f, 1.0f};
GLfloat mat2_ambient[] =
{1.0f, 1.0f, 1.0f, 1.0f}, mat2_diffuse[] =
{1.0f, 1.0f, 1.0f, 1.0f}, mat2_specular[] =
{0.0f, 0.0f, 0.0f, 1.0f};
GLfloat const mat1_shininess = 32.0f;
GLfloat const mat2_shininess = 32.0f;
GLfloat const  mat3_shininess = 32.0f;
GLfloat const mat4_shininess = 32.0f;
GLfloat const mat5_shininess = 32.0f;


GLfloat mat3_ambient[] =
{0.2, 0.2, 0.2}, mat3_diffuse[] =
{0.8, 0.0, 0.0}, mat3_specular[] =
{0.0, 0.0, 0.0};
GLfloat mat4_ambient[] =
{0.2, 0.2, 0.2}, mat4_diffuse[] =
{0.0, 0.0, 0.0}, mat4_specular[] =
{0.0, 0.0, 0.0}; 
GLfloat mat5_ambient[] =
{0.2, 0.2, 0.2}, mat5_diffuse[] =
{0.8, 0.0, 0.0}, mat5_specular[] =
{1.0, 1.0, 1.0}; 


float _angle=0.0;
float _cameraangle=30.0;


void selectMaterial(int a){
	switch(a){
	case 1:
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat1_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat1_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat1_diffuse);
	
    glShadeModel (GL_SMOOTH);
	break;
	case 2:
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat2_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat2_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat2_diffuse);
	
    glShadeModel (GL_SMOOTH);
	break;
	case 3:
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat3_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat3_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat3_diffuse);
	
    glShadeModel (GL_SMOOTH);
	case 4:
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat4_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat4_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat4_diffuse);
	
    glShadeModel (GL_SMOOTH);
	break;
	case 5:
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat5_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat5_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat5_diffuse);
	
    glShadeModel (GL_SMOOTH);
	default:
	return;
	}


}





void initWindow();

void changeSize(int w1, int h1)
 {

 if(h1 == 0)
  h1 = 1;

 w = w1;
 h = h1;
 ratio = 1.0f * w / h;
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
    glViewport(0, 0, w, h);
 gluPerspective(90.0f,ratio,0.5,10);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 gluLookAt(x, y, z,
       x + lx,1.0f,z + lz,
    0.0f,1.0f,0.0f);


 }








void initScene() {

  glMatrixMode(GL_PROJECTION);
  glLightfv(GL_LIGHT0, GL_AMBIENT, white_light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white_light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, white_light_position);


  glLightfv(GL_LIGHT1, GL_AMBIENT, green_light_ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, green_light_diffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, green_light_specular);
  glLightfv(GL_LIGHT1, GL_POSITION, green_light_position);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_DEPTH_TEST);

}



void orientMeStart(float ang) {


 lx = sin(-0.8f);
 lz = -cos(-0.8f);
 x=2.0f;
 y=2.0f;
 z=2.0f;
 glLoadIdentity();
 gluLookAt(x, y, z,
       x + lx,y+ly,z + lz,
    0.0f,0.1f,0.0f);
}


void resetPerspectiveProjection() {
 glMatrixMode(GL_PROJECTION);
 glPopMatrix();
 glMatrixMode(GL_MODELVIEW);
}


GLuint LoadTexture(char * filename)
{
if(cur_file==filename)
	return textureID;
cur_file=filename;
int i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];

    // read the 54-byte header
    fread(info, sizeof(unsigned char), 54, f); 

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    // allocate 3 bytes per pixel
    int size = 3 * width * height;
    unsigned char* data = new unsigned char[size];

    // read the rest of the data at once
    fread(data, sizeof(unsigned char), size, f); 
    fclose(f);

   
    const GLsizei width1 = width;
    const GLsizei height1 = height;

    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
    return textureID;
}



void renderScene(void) {
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 glRotatef(angular_speed,0.0f,1.0f,0.0f);

 	glBegin(GL_POLYGON);
	

	selectMaterial(4);
	// FACE 2

	glNormal3d(0, 0, -1);
	selectMaterial(4);
	glVertex3f( 1.0f, 0.0f, -0.5f);
	glVertex3f(0.0f, 0.0f, -0.5f);
	glVertex3f(-0.8f, 0.0f,  0.0f);
	glVertex3f(0.0f, 0.0f,  0.5f);
	glVertex3f( 1.0f, 0.0f,  0.5f);
	glEnd();	  
	glBegin(GL_POLYGON);
	selectMaterial(1);
	glNormal3d(0, 1, 0);
  
  
  
 glEnd();


	glBegin(GL_QUADS);
	//FACE 4
	glNormal3d(0, 0, -1);
	selectMaterial(5);
	glVertex3f( 1.0f, 1.0f, -0.5f);
	glVertex3f( 0.0f, 1.0f,  -0.5f);
	glVertex3f(0.0f, 0.0f, -0.5f);
	glVertex3f(1.0f, 0.0f,  -0.5f);
	
	


  	//FACE 3
  	selectMaterial(5);	
	glNormal3d(1, 0, 0);
	glVertex3f( 1.0f, 1.0f,  0.5f);
	glVertex3f( 1.0f, 1.0f,  -0.5f);
	glVertex3f( 1.0f, 0.0f,  -0.5f);	
	glVertex3f( 1.0f, 0.0f,  0.5f);
	

	glPopMatrix();

	glEnd();


  GLuint texture = LoadTexture("BLU.BMP");
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texture);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);





	glBegin(GL_QUADS);
	glEnable(GL_TEXTURE_2D);
	selectMaterial(2);
	glNormal3d(0, 0, 1);
	glTexCoord2d( 0.0, 0.0 );
	glVertex3f(0.0f, 0.0f, 0.5f);
	glTexCoord2d( 0.0, 1.0 );
	glVertex3f( 0.0f, 1.0f,  0.5f);
	glTexCoord2d( 1.0, 1.0 );
	glVertex3f( 1.0f, 1.0f, 0.5f);
	glTexCoord2d( 1.0, 0.0 );
	glVertex3f(1.0f, 0.0f,  0.5f);
	glDisable(GL_TEXTURE_2D);
	
	glEnd();


 texture = LoadTexture("YEL.BMP");
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texture);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);


glBegin(GL_QUADS);
	selectMaterial(1);
	glNormal3f( -0.9055, 0,-0.9135);
	glTexCoord2d( 0.0, 0.0 );
	glVertex3f(-0.8f, 0.0f,  0.0f);
	glTexCoord2d( 0.0, 1.0 );
	glVertex3f(0.0f, 0.0f, -0.5f);
	glTexCoord2d( 1.0, 1.0 );
	glVertex3f(0.0f, 1.0f, -0.5f);
	glTexCoord2d( 1.0, 0.0 );
	glVertex3f(-0.8f, 1.0f,  0.0f);
	glDisable(GL_TEXTURE_2D);
glEnd();


texture = LoadTexture("TRU256.BMP");
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texture);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);
glBegin(GL_QUADS);
	
	
	selectMaterial(2);
	glNormal3f( -0.9055, 0,0.9135);
	glTexCoord2d( 0.0, 0.0 );
	glVertex3f(-0.8f, 0.0f,  0.0f);
	glTexCoord2d( 0.0, 1.0 );
	glVertex3f(0.0f, 0.0f, 0.5f);
	glTexCoord2d( 1.0, 1.0 );
	glVertex3f(0.0f, 1.0f, 0.5f);
	glTexCoord2d( 1.0, 0.0 );
	glVertex3f(-0.8f, 1.0f,  0.0f);
	glDisable(GL_TEXTURE_2D);
	glEnd();

texture = LoadTexture("FLAG.BMP");
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texture);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);

glBegin(GL_QUADS);
	
  	selectMaterial(1);
	glNormal3d(0,0,1);
	glTexCoord2d( 0.0, 0.0 );
	glVertex3f( 1.0f, 1.0f,  0.5f);

	glTexCoord2d( 0.0, 1.0 );
  	glVertex3f( 1.0f, 1.0f, -0.5f);

	glTexCoord2d( 1.0, 1.0 );
	glVertex3f(0.0f, 1.0f,  -0.5f);
	glTexCoord2d( 1.0, 0.0 );
	glVertex3f(0.0f, 1.0f, 0.5f);
	glEnd();
	glBegin(GL_TRIANGLES);
	selectMaterial(1);
	glNormal3d(0,0,1);
	glTexCoord2f( 0.0, 0.0 );
	glVertex3f(0.0f,1.0f, -0.5f);
	glTexCoord2f( 0.0, 0.5 );
	glVertex3f(-0.8f,1.0f,0.0f);
	glTexCoord2d( 1.0, 0.0 );
	glVertex3f(0.0f,1.0f,0.5f);
	glDisable(GL_TEXTURE_2D);
	glEnd();
	



 resetPerspectiveProjection();

 glDisable(GL_TEXTURE_2D);

 glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {

 switch(key){
    case 32:
	if(angular_speed==0)
		angular_speed=1.0f;
	else	
		angular_speed=0;
    break;
    case 's':
    case 'S':
      if(l1_on==1){
          glDisable(GL_LIGHT1);
          l1_on=0;
          }
       else{
        glEnable(GL_LIGHT1);
        l1_on=1;
       }
       break;
 
    case 'a':
    case 'A':
      if(l0_on==1){
          glDisable(GL_LIGHT0);
          l0_on=0;
          }
       else{
        glEnable(GL_LIGHT0);
        l0_on=1;
       }
       break;
       default:
       return;
 }
}

void update(int value){

	glutPostRedisplay();
	glutTimerFunc(25,update,0);

}

void initWindow() {
 glutIgnoreKeyRepeat(1);
 glutKeyboardFunc(processNormalKeys);
 glutDisplayFunc(renderScene);
 glutIdleFunc(renderScene);
 glutTimerFunc(25,update,0);
 glutReshapeFunc(changeSize);
 initScene();

}





int main(int argc, char **argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
 glutInitWindowPosition(100,100);
 glutInitWindowSize(640,360);


 glutCreateWindow("Assignment");
 orientMeStart(0.0f);
 initWindow();

 glutMainLoop();

 return(0);
}




