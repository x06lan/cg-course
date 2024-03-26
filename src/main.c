
#include "freeglut_std.h"
#include <GL/gl.h>
#include <stdio.h>
/*** freeglut***/
#include <freeglut.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "pryamid.h"

void ChangeSize(int, int);
void RenderScene(void);
void MenuCallback(int);

GLenum glShadeType = GL_SMOOTH;
float yangle = 45;
float xangle = 0;
float zangle = 0;

float xtrans = 0;
float ytrans = 0;
float ztrans = 0;

float xscale = 1;
float yscale = 1;
float zscale = 1;

float ydelta = .2f;
float xdelta = .2f;
float mousex = 0;
float mousey = 0;

float mousexl = 0;
float mouseyl = 0;

float ak = 10;
const int windowx = 1920 / 2;
const int windowy = 1080 - 40;
void Loop()
{
  // yangle += ydelta;
  // xangle += xdelta;
  glutPostRedisplay();
}

void SpecialKeyHandler(int key, int x, int y)
{
  switch (key)
  {
  case GLUT_KEY_RIGHT:
    yangle += 10.0f;
    break;
  case GLUT_KEY_LEFT:
    yangle -= 10.0f;
    break;
  case GLUT_KEY_UP:
    xangle += 10.0f;
    break;
  case GLUT_KEY_DOWN:
    xangle -= 10.0f;
    break;
  }
}
void MouseHandler(int button, int state, int x, int y)
{

  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    mousexl = mousex;
    mouseyl = mousey;
    mousex = ((float)x / (float)windowx) * 2 - 1;
    mousey = -2 * ((float)y / (float)windowy) + 1;
  }
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
  {
    mousexl = mousex;
    mouseyl = mousey;
    mousex = ((float)x / (float)windowx) * 2 - 1;
    mousey = -2 * ((float)y / (float)windowy) + 1;
  }
  printf("x=%.2f,y=%.2f\n", mousex, mousey);
  printf("w=%d,h=%d\n", windowx, windowy);
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

void scale(GLfloat x, GLfloat y, GLfloat z)
{
  GLfloat m[16] = {
      x, 0, 0, 0,
      0, y, 0, 0,
      0, 0, z, 0,
      0, 0, 0, 1};
  glMultMatrixf(m);
}
void ark(GLfloat x, GLfloat y, GLfloat z, GLfloat angel)
{
  float c = cos(angel);
  float s = sin(angel);
  GLfloat m[16] = {
      (1 - c) * x * x + c, (1 - c) * x * y - s * z, (1 - c) * x * z + s * y, 0,
      (1 - c) * x * y + s * z, (1 - c) * y * y + c, (1 - c) * y * z - s * x, 0,
      (1 - c) * x * z - s * y, (1 - c) * y * z + s * x, (1 - c) * z * z + c, 0,
      0, 0, 0, 1};
  glMultMatrixf(m);
}
void NormalKeyHandler(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'w':
    xangle += 0.05f;
    break;
  case 'q':
    xangle -= 0.05f;
    break;
  case 's':
    yangle += 0.05f;
    break;
  case 'a':
    yangle -= 0.05f;
    break;
  case 'x':
    zangle += 0.05f;
    break;
  case 'z':
    zangle -= 0.05f;
    break;

  case 'r':
    xtrans += 0.1f;
    break;
  case 'e':
    xtrans -= 0.1f;
    break;
  case 'f':
    ytrans += 0.1f;
    break;
  case 'd':
    ytrans -= 0.1f;
    break;
  case 'v':
    ztrans += 0.1f;
    break;
  case 'c':
    ztrans -= 0.1f;
    break;

  case 'y':
    xscale += 0.1f;
    break;
  case 't':
    xscale -= 0.1f;
    break;
  case 'h':
    yscale += 0.1f;
    break;
  case 'g':
    yscale -= 0.1f;
    break;
  case 'n':
    zscale += 0.1f;
    break;
  case 'b':
    zscale -= 0.1f;
    break;
  case '1':
    xangle = 0;
    yangle = 0;
    zangle = 0;
    xtrans = 0;
    ytrans = 0;
    ztrans = 0;
    xscale = 1;
    yscale = 1;
    zscale = 1;
    break;
  }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(windowx, windowy);
  glutInitWindowPosition(600, 80);
  glutCreateWindow("Simple Triangle");

  glutCreateMenu(MenuCallback);
  glutAddMenuEntry("GL_SMOOTH", 1);
  glutAddMenuEntry("GL_FLAT", 2);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

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
  // printf("Window Size= %d X %d\n", w, h);
  // windowx = w;
  // windowy = h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-10, 10, -10, 10,
          -10, 100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
void RenderScene(void)
{
  GLuint texture;
  int width, height, channels;
  unsigned char *imageData = stbi_load("../kjy01601.png", &width, &height, &channels, 0);

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  if (imageData)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 width, height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    stbi_image_free(imageData);
  }
  else
  {
    printf("nmsl");
  }

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);

  // glBegin(GL_QUADS); // Example: Drawing a textured quad
  //   glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);
  //   glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  0.0f);
  //   glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  0.0f);
  //   glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  0.0f);
  // glEnd();
  // glBindTexture(GL_TEXTURE_2D, 0);

  glClearColor(0, 0, 0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();
  gluLookAt(
      0, 0, 10,
      0, 0, 0,
      0, 1, 0);
  glShadeModel(glShadeType);

  glBegin(GL_LINES);
  glVertex3f(100, 0, 0);
  glVertex3f(-100, 0, 0);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f(0, -100, 0);
  glVertex3f(0, 100, 0);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f(0, 0, -100);
  glVertex3f(0, 0, 100);
  glEnd();

  // point
  glColor3f(1.0, 0.0, 0.0);
  glPointSize(10);
  glBegin(GL_POINTS);
  glVertex2f(mousex * 10, mousey * 10);
  glEnd();
  // last point line
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_LINES);
  glVertex3f(mousex * 10, mousey * 10, 5);
  glVertex3f(mousexl * 10, mouseyl * 10, 5);
  glEnd();

  glColor3f(1.0, 1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  float vx = (mousex - mousexl);
  float vy = (mousey - mouseyl);
  float l = sqrtf(vx * vx + vy * vy);
  vx /= l;
  vy /= l;
  scale(xscale, yscale, zscale);
  translate(xtrans, ytrans, ztrans);
  // rotateX(xangle);
  // rotateY(yangle);
  // rotateZ(zangle);
  rotateZ(asin(vx));
  rotateY(xangle);
  rotateZ(-asin(vx));
  // ak += 0.01;
  // ark(10 * (mousex - mousexl), 10 * (mousey - mouseyl), 0, ak);
  glBegin(GL_TRIANGLES);
  // glColor3f(1,1,0);
  glTexCoord2f(0.5f, 0.0f);
  glVertex3fv(PRYAMID_POINTS[0]);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3fv(PRYAMID_POINTS[1]);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3fv(PRYAMID_POINTS[2]);
  glEnd();
  glBegin(GL_TRIANGLES);
  // glColor3f(0,1,1);
  glTexCoord2f(0.5f, 0.0f);
  glVertex3fv(PRYAMID_POINTS[0]);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3fv(PRYAMID_POINTS[2]);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3fv(PRYAMID_POINTS[3]);
  glEnd();
  glBegin(GL_TRIANGLES);
  // glColor3f(1,0,1);
  glTexCoord2f(0.5f, 0.0f);
  glVertex3fv(PRYAMID_POINTS[0]);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3fv(PRYAMID_POINTS[3]);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3fv(PRYAMID_POINTS[4]);
  glEnd();
  glBegin(GL_TRIANGLES);
  // glColor3f(1,0,0);
  glTexCoord2f(0.5f, 0.0f);
  glVertex3fv(PRYAMID_POINTS[0]);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3fv(PRYAMID_POINTS[4]);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3fv(PRYAMID_POINTS[1]);
  glEnd();
  glutSwapBuffers();
}

void MenuCallback(int value)
{
  switch (value)
  {
  case 1:
    glShadeType = GL_SMOOTH;
    break;
  case 2:
    glShadeType = GL_FLAT;
    break;
  }
  glutPostRedisplay();
}
