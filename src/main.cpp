
/*** freeglut***/
#ifdef _MSC_VER
#include "windows.h"
#pragma comment(lib, "opengl32.lib")
#endif

#include <GL/gl.h>
#include <stdio.h>
#include <freeglut.h>
#include <freeglut_std.h>

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

std::vector<Vector3d> vertices;
std::vector<FaceIndices> faces;
BoundBox box;

// int windowx = 1920 / 2;
int windowx = 1080 - 40;
int windowy = 1080 - 40;
float mousex = 0;
float mousey = 0;
float lines = 15;

Vector3d camera = {0, 0, -1};
Vector3d target = {0, 0, 0};
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
    // angle.y += 10.0f;
    break;
  case GLUT_KEY_LEFT:
    // angle.y -= 10.0f;
    break;
  case GLUT_KEY_UP:
    // angle.x += 10.0f;
    break;
  case GLUT_KEY_DOWN:
    // angle.x -= 10.0f;
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
    // mousex = ((float)x / (float)windowx) * 2 - 1;
    // mousey = -2 * ((float)y / (float)windowy) + 1;
  }
  printf("mouse x=%.2f,y=%.2f\n", mousex, mousey);
  // printf("w=%d,h=%d\n", windowx, windowy);
}

void MenuCallback1(int value)
{
  switch (value)
  {
  case 10:
    lines = 10;
    break;
  case 15:
    lines = 15;
    break;
  case 20:
    lines = 20;
    break;
  }
  glutPostRedisplay();
}

void ScaleMatrix(GLfloat x, GLfloat y, GLfloat z)
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
    // trans.x += 0.01f * box.get_radius();
    break;

  case '1':
    // reset
    break;
  }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(windowx, windowy);
  glutInitWindowPosition(600, 80);
  glutCreateWindow("2d grid");

  // printf("center=(%.2f,%.2f,%.2f)\n", box.center.x, box.center.y, box.center.z);
  // printf("radius=%.2f\n", box.get_radius());
  int sub1 = glutCreateMenu(MenuCallback1);
  glutAddMenuEntry("10", 10);
  glutAddMenuEntry("15", 15);
  glutAddMenuEntry("20", 20);

  glutCreateMenu(nullptr);
  glutAddSubMenu("grid", sub1);

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
  // windowx = w;
  // windowy = h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(1.001, -1.001,
          -1.001, 1.001,
          0.01, 10000);
}
void RenderScene(void)
{

  glClearColor(0, 0, 0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(
      camera.x, camera.y, camera.z,
      target.x, target.y, target.z,
      0, 1, 0);

  glColor3f(1.0, 1.0, 1.0);
  for (int i = 0; i <= lines; i++)
  {
    glBegin(GL_LINES);
    float x = 2 * static_cast<float>(i) / lines - 1.0;

    glVertex3f(x, -1, 0);
    glVertex3f(x, 1, 0);
    glEnd();
  }
  for (int i = 0; i <= lines; i++)
  {
    glBegin(GL_LINES);
    float y = 2 * static_cast<float>(i) / lines - 1.0;
    glVertex3f(-1, y, 0);
    glVertex3f(1, y, 0);
    glEnd();
  }
  float unlines = 1.0 / lines;
  float pointx = floor((mousex + 1) * 0.5 * lines);
  float pointy = floor((mousey + 1) * 0.5 * lines);
  // printf("%.2f,%.2f\n", mousex, mousey);
  // printf("pointx=%.2f,pointy=%.2f %f \n", pointx, pointy, lines);
  pointx *= unlines * 2.0;
  pointy *= unlines * 2.0;

  pointx += -1;
  pointy += -1;
  pointx += unlines * 1.0;
  pointy += unlines * 1.0;
  glColor3f(1.0, 1.0, 1.0);
  glPointSize(windowx * unlines);
  glBegin(GL_POINTS);
  glVertex3f(pointx, pointy, 0.0);

  glEnd();

  // glVertex3f(-1, y, 0);
  // glVertex3f(1, y, 0);
  // glBegin(GL_LINES);
  // glVertex3f(100, 0, 0);
  // glVertex3f(0, 0, 0);
  // glEnd();

  glColor3f(1.0, 1.0, 0.0);

  glutSwapBuffers();
}
