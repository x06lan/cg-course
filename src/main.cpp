
#include <GL/gl.h>
#include <stdio.h>
/*** freeglut***/
#ifdef _MSC_VER
#include "windows.h"
#pragma comment(lib, "opengl32.lib")
#endif


#include <freeglut.h>
#include <freeglut_std.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "pryamid.h"
#include "obj.hpp"
#include <vector>
#include <random>

void ChangeSize(int, int);
void RenderScene(void);
void MenuCallback1(int);
void MenuCallback2(int);
void MenuCallback3(int);

GLenum shadeType = GL_SMOOTH;
GLenum renderMode = GL_TRIANGLES;

std::string filename ="./obj/gourd.obj";
// std::string filename = "../obj/teapot.obj";

int renderColor= 1;


Vector3d angle = {0, 0, 0};

Vector3d trans = {0, 0, 0};

Vector3d scale = {1, 1, 1};

Vector3d arbitray = {1, 1, 0};

Vector3d camera = {1, 1, 1};
Vector3d target = {0, 0, 0};

float wangle = 0;

float ydelta = .2f;
float xdelta = .2f;
float mousex = 0;
float mousey = 0;


std::vector<Vector3d> vertices;
std::vector<FaceIndices> faces;
BoundBox box;

int windowx = 1920 / 2;
int windowy = 1080 - 40;
void Loop()
{
  RenderScene();
  // glutPostRedisplay();
  // angle.y += ydelta;
  // xangle += xdelta;
  glutPostRedisplay();
}

void SpecialKeyHandler(int key, int x, int y)
{
  switch (key)
  {
  case GLUT_KEY_RIGHT:
    angle.y += 10.0f;
    break;
  case GLUT_KEY_LEFT:
    angle.y -= 10.0f;
    break;
  case GLUT_KEY_UP:
    angle.x += 10.0f;
    break;
  case GLUT_KEY_DOWN:
    angle.x -= 10.0f;
    break;
  }
}
void MouseHandler(int button, int state, int x, int y)
{

  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    mousex = ((float)x / (float)windowx) * 2 - 1;
    mousey = -2 * ((float)y / (float)windowy) + 1;
  }
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
  {
    mousex = ((float)x / (float)windowx) * 2 - 1;
    mousey = -2 * ((float)y / (float)windowy) + 1;
  }
  printf("mouse x=%.2f,y=%.2f\n", mousex, mousey);
  // printf("w=%d,h=%d\n", windowx, windowy);
}

void translate(GLfloat x, GLfloat y, GLfloat z)
{
  GLfloat m[16] = {
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      x, y, z, 1};
  glMultMatrixf(m);
}

void rotateX(GLfloat x)
{
  GLfloat m[16] = {
      1, 0, 0, 0,
      0, cos(x), -sin(x), 0,
      0, sin(x), cos(x), 0,
      0, 0, 0, 1};
  glMultMatrixf(m);
}

void rotateY(GLfloat y)
{
  GLfloat m[16] = {
      cos(y), 0, sin(y), 0,
      0, 1, 0, 0,
      -sin(y), 0, cos(y), 0,
      0, 0, 0, 1};
  glMultMatrixf(m);
}

void rotateZ(GLfloat z)
{
  GLfloat m[16] = {
      cos(z), -sin(z), 0, 0,
      sin(z), cos(z), 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1};
  glMultMatrixf(m);
}

void Scale(GLfloat x, GLfloat y, GLfloat z)
{
  GLfloat m[16] = {
      x, 0, 0, 0,
      0, y, 0, 0,
      0, 0, z, 0,
      0, 0, 0, 1};
  glMultMatrixf(m);
}

void NormalKeyHandler(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'q':
    trans.x += 0.01f*box.get_radius();
    break;
  case 'a':
    trans.y += 0.01f*box.get_radius();
    break;
  case 'z':
    trans.z += 0.01f*box.get_radius();
    break;

  case 'w':
    angle.x += 0.05f;
    break;
  case 's':
    angle.y += 0.05f;
    break;
  case 'x':
    angle.z += 0.05f;
    break;
  
  case 'e':
    scale.x += 0.05f;
    break;
  case 'd':
    scale.y += 0.05f;
    break;
  case 'c':
    scale.z += 0.05f;
    break;

  case 'r':
    camera.x += 0.05f*box.get_radius();
    break;
  case 'f':
    camera.y += 0.05f*box.get_radius();
    break;
  case 'v':
    camera.z += 0.05f*box.get_radius();
    break;

  case 't':
    target.x += 0.05f*box.get_radius();
    break;
  case 'g':
    target.y += 0.05f*box.get_radius();
    break;
  case 'b':
    target.z += 0.05f*box.get_radius();
    break;

  case 'y':
    arbitray.x += 0.05f*box.get_radius();
    break;
  case 'h':
    arbitray.y += 0.05f*box.get_radius();
    break;
  case 'n':
    arbitray.z += 0.05f*box.get_radius();
    break;

  case 'u':
    arbitray.x -= 0.05f*box.get_radius();
    break;
  case 'j':
    arbitray.y -= 0.05f*box.get_radius();
    break;
  case 'm':
    arbitray.z -= 0.05f*box.get_radius();
    break;

  case 'i':
    wangle += 0.05f;
    break;


  

  
  case '1':
    // reset
    angle ={0, 0, 0};
    trans ={0, 0, 0};
    scale= {1, 1, 1};

    float radius=box.get_radius()*1.1;
    camera={0,0,radius};
    target={0,0,0};
    arbitray={1,1,0};
    wangle=0;


    break;
  }
}

void drawObj( std::vector<Vector3d>& vertices, std::vector<FaceIndices>& faces,unsigned int renderMode,int renderColor){

    if(renderMode==GL_TRIANGLES || renderMode==GL_LINES){
        for(int i=0;i<faces.size();i++){
            Vector3d v1 = vertices[faces[i].v1 - 1];
            Vector3d v2 = vertices[faces[i].v2 - 1];
            Vector3d v3 = vertices[faces[i].v3 - 1];
            if(renderMode==GL_TRIANGLES){
                glBegin(renderMode);
                if (renderColor == 0)
                    glColor3f(1.0, 1.0, 1.0);
                else 
                    glColor3f(generateRandomFloat(i*3),generateRandomFloat(i*3+1),generateRandomFloat(i*3+2));
                // glTexCoord2f(1.0f, 1.0f);
                glVertex3f(v1.x, v1.y, v1.z);
                // glTexCoord2f(1.0f, 1.0f);
                glVertex3f(v2.x, v2.y, v2.z);
                // glTexCoord2f(1.0f, 1.0f);
                glVertex3f(v3.x, v3.y, v3.z);
                glEnd();
            }
            else if(renderMode ==GL_LINES){
                glBegin(renderMode);

                if (renderColor == 0)
                    glColor3f(1.0, 1.0, 1.0);
                else 
                    glColor3f(generateRandomFloat(i*3),generateRandomFloat(i*3+1),generateRandomFloat(i*3+2));
                glVertex3f(v1.x, v1.y, v1.z);
                glVertex3f(v2.x, v2.y, v2.z);
                glEnd();

                glBegin(renderMode);
                glVertex3f(v2.x, v2.y, v2.z);
                glVertex3f(v3.x, v3.y, v3.z);
                glEnd();

                glBegin(renderMode);
                glVertex3f(v1.x, v1.y, v1.z);
                glVertex3f(v2.x, v2.y, v2.z);
                glEnd();
            }
        }
    }
    else if (renderMode == GL_POINTS){
        for(int i=0;i<vertices.size();i++){
            Vector3d v = vertices[i];
            glPointSize(10);
            if (renderColor == 0)
                glColor3f(1.0, 1.0, 1.0);
            else 
                glColor3f(generateRandomFloat(i*3),generateRandomFloat(i*3+1),generateRandomFloat(i*3+2));

            glBegin(renderMode);
            glVertex3f(v.x, v.y, v.z);
            glEnd();
        }
    }

}
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(windowx, windowy);
  glutInitWindowPosition(600, 80);
  glutCreateWindow("Simple Triangle");

  box.right_top={-100.0,-100.0,-100.0};
  box.left_bottom={100.0,100.0,100.0};

  if (argc>1)
    readObj(argv[1], vertices, faces,box); 
  else
    readObj(filename, vertices, faces,box); 

  // target={box.center.x,box.center.y,box.center.z};
  target={0,0,0};
  camera={box.get_radius(),box.get_radius(),box.get_radius()};
  // printf("center=(%.2f,%.2f,%.2f)\n", box.center.x, box.center.y, box.center.z);
  // printf("radius=%.2f\n", box.get_radius());
  int sub1=glutCreateMenu(MenuCallback1);
  glutAddMenuEntry("point", 1);
  glutAddMenuEntry("line", 2);
  glutAddMenuEntry("face", 3);

  int sub2=glutCreateMenu(MenuCallback2);
  glutAddMenuEntry("single color", 1);
  glutAddMenuEntry("random color", 2);

  int sub3=glutCreateMenu(MenuCallback3);
  glutAddMenuEntry("gourd", 1);
  glutAddMenuEntry("octahedron", 2);
  glutAddMenuEntry("teapot", 3);
  glutAddMenuEntry("teddy", 4);

  glutCreateMenu(nullptr);
  glutAddSubMenu("render mode",sub1);
  glutAddSubMenu("render color",sub2);
  glutAddSubMenu("render obj",sub3);

  glutAttachMenu(GLUT_RIGHT_BUTTON);

  RenderScene();
  glutSpecialFunc(SpecialKeyHandler);
  glutKeyboardFunc(NormalKeyHandler);
  glutMouseFunc(MouseHandler);

  glutReshapeFunc(ChangeSize);
  glutDisplayFunc(RenderScene);
  glutIdleFunc(Loop);
  
  glutMainLoop(); // http://www.programmer-club.com.tw/ShowSameTitleN/opengl/2288.html
  return 0;
}
void ChangeSize(int w, int h)
{
  printf("Window Size= %d X %d\n", w, h);
  
  glEnable(GL_DEPTH_TEST);
  glShadeModel(shadeType);
  glViewport(0, 0, w, h);
  windowx=w;
  windowy=h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  float radius=box.get_radius()*1.1;
  glOrtho(box.center.x -radius, box.center.x +radius,
          box.center.y -radius, box.center.y +radius,
          0.01, 10000);
  camera={0,0,radius};
  // camera={radius,radius,radius};
  // gluPerspective(90, (float)w / (float)h, 0.01, 10000);
}
void RenderScene(void)
{

  glClearColor(0, 0, 0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  float r=1.1;
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(
      camera.x, camera.y, camera.z,
      target.x,target.y,target.z,
      0, 1, 0);

  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex3f(100, 0, 0);
  glVertex3f(0, 0, 0);
  glEnd();
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_LINES);
  glVertex3f(0,0, 0);
  glVertex3f(0, 100, 0);
  glEnd();
  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_LINES);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 100);
  glEnd();

  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_LINES);
  glVertex3f(0,0,0);
  glVertex3f(arbitray.x, arbitray.y, arbitray.z);
  glEnd();

  float lxy=sqrtf(pow(arbitray.x,2)+pow(arbitray.y,2));
  float lxz=sqrtf(pow(arbitray.x,2)+pow(arbitray.z,2));

  Scale(scale.x, scale.y, scale.z);
  translate(trans.x, trans.y, trans.z);
  rotateX(angle.x);
  rotateY(angle.y);
  rotateZ(angle.z);

  rotateZ(-atan2(arbitray.y,arbitray.x));
  rotateY(-atan2(arbitray.z,arbitray.x));
  rotateX(wangle);
  rotateY(atan2(arbitray.z,arbitray.x));
  rotateZ(atan2(arbitray.y,arbitray.x));

  glColor3f(1.0, 1.0, 0.0);
  drawObj(vertices, faces,renderMode,renderColor);
  
  // printf("len=%d\n", vertices.size());
  glutSwapBuffers();
}


void MenuCallback1(int value)
{
  switch (value)
  {
  case 1:
    renderMode= GL_POINTS;
    break;
  case 2:
    renderMode= GL_LINES;
    break;
  case 3:
    renderMode= GL_TRIANGLES;
    break;
  }
  glutPostRedisplay();
}

void MenuCallback2(int value)
{
  switch (value)
  {
  case 1:
    renderColor = 0;
    break;
  case 2:
    renderColor = 1;
    break;
  }
  glutPostRedisplay();
}
void MenuCallback3(int value)
{
  switch (value)
  {
  case 1:
    filename = "gourd.obj";
    break;
  case 2:
    filename = "octahedron.obj";
    break;
  case 3:
    filename = "teapot.obj";
    break;
  case 4:
    filename = "teddy.obj";
    break;
  }

  filename="./obj/"+filename;
  box.right_top={-100.0,-100.0,-100.0};
  box.left_bottom={100.0,100.0,100.0};
  printf("filename=%s\n", filename.c_str());
  vertices.clear();
  faces.clear();
  readObj(filename, vertices, faces,box);
  box.update_center();
  printf("radius=%.2f\n", box.get_radius());
  printf("right_top=(%.2f,%.2f,%.2f)\n", box.right_top.x, box.right_top.y, box.right_top.z);
  printf("left_bottom=(%.2f,%.2f,%.2f)\n", box.left_bottom.x, box.left_bottom.y, box.left_bottom.z);
  printf("center=(%.2f,%.2f,%.2f)\n", box.center.x, box.center.y, box.center.z);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  float radius=box.get_radius()*1.1;
  glOrtho(box.center.x -radius, box.center.x +radius,
          box.center.y -radius, box.center.y +radius,
          0.01, 10000);
  camera={0,0,radius};
  glutPostRedisplay();
}