
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
#include "matrix.hpp"
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

// std::vector<Vector2d> points = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}, {0, 1}};
// std::vector<Vector2d> points = {{0, 0}, {1, 0}, {1, 1}, {0.0, 1}, {-1, 1}, {-1, 0}, {1, -1}, {0.0, -1}, {-1, -1}};
std::vector<Vector2d> points = {};
// int windowx = 1920 / 2;
// int windowy = 1080 - 40;
int windowx = 1080 - 40;
int windowy = 1080 - 40;
float lines = 100;
float padding = 0.05;

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
    float mousex = ((float)x / (float)windowx) * 2 - 1;
    float mousey = -2 * ((float)y / (float)windowy) + 1;
    mousex = clamp(mousex * (1.0 + padding), -1, 1);
    mousey = clamp(mousey * (1.0 + padding), -1, 1);

    // points.insert(points.begin(), {mousex, mousey});
    // points.pop_back();
    points.push_back({mousex, mousey});
  }
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
  {
    // mousex = ((float)x / (float)windowx) * 2 - 1;
    // mousey = -2 * ((float)y / (float)windowy) + 1;
  }
  // printf("mouse x=%.2f,y=%.2f\n", mousex, mousey);
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
  case 100:
    lines = 100;
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

float remap(float value, float padding, float lines)
{
  float v = floor((value + 1) * 0.5 * lines);
  v = clamp(v, 0, lines - 1);
  float unlines = 1.0 / lines;
  v = v * unlines * 2.0 - 1 + unlines;
  return v;
}
float blockId(float value, float padding, float lines)
{
  float v = floor((value + 1) * 0.5 * lines);
  v = clamp(v, 0, lines - 1);
  return v;
}
float blockIdCoord(float v)
{
  // v = clamp(v, 0, lines - 1);
  float unlines = 1.0 / lines;
  v = v * unlines * 2.0 - 1 + unlines;
  return v;
}
void drawLine(Vector2d a, Vector2d b)
{
  float x1 = blockId(a.x, padding, lines);
  float y1 = blockId(a.y, padding, lines);
  float x2 = blockId(b.x, padding, lines);
  float y2 = blockId(b.y, padding, lines);

  float x = x1;
  float y = y1;
  float dx = x2 - x1;
  float dy = y2 - y1;

  bool flip = false;
  if (abs(dy / dx) > 1.0)
  {
    float temp = x1;
    x1 = y1;
    y1 = temp;

    temp = x2;
    x2 = y2;
    y2 = temp;

    dx = x2 - x1;
    dy = y2 - y1;

    x = x1;
    y = y1;
    flip = true;
  }

  float d = dx > 0 ? 1 : -1;
  while ((d > 0 && x < x2) || (d < 0 && x > x2))
  {

    float floorY = floor(y);

    y = y1 + dy / dx * (x - x1);
    if (abs(floor(y) - floorY) > 0.5)
      glColor3f(0.0, 0.0, 1.0);
    else
      glColor3f(0.0, 1.0, 0.0);

    float px = blockIdCoord(floor(x));
    float py = blockIdCoord(floor(y));

    if (flip)
    {
      float temp = px;
      px = py;
      py = temp;
    }

    glBegin(GL_POINTS);
    glVertex3f(px, py, 10);
    glEnd();
    x += d;
  }
}

bool isLeft(Vector2d l1, Vector2d l2, Vector2d p)
{
  return (l2.x - l1.x) * (p.y - l1.y) - (l2.y - l1.y) * (p.x - l1.x) > 0.0;
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
  glutAddMenuEntry("100", 100);

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
  glOrtho(1.0 + padding, -1.0 - padding,
          -1.0 - padding, 1.0 + padding,
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
  // x axis line
  for (int i = 0; i <= lines; i++)
  {
    glBegin(GL_LINES);
    float x = 2 * static_cast<float>(i) / lines - 1.0;

    glVertex3f(x, -1, 0);
    glVertex3f(x, 1, 0);
    glEnd();
  }
  // y axis line
  for (int i = 0; i <= lines; i++)
  {
    glBegin(GL_LINES);
    float y = 2 * static_cast<float>(i) / lines - 1.0;
    glVertex3f(-1, y, 0);
    glVertex3f(1, y, 0);
    glEnd();
  }
  float unlines = 1.0 / lines;

  // red points
  for (int i = points.size() - 1; i >= 0; i--)
  {
    float pointx = remap(points[i].x, padding, lines);
    float pointy = remap(points[i].y, padding, lines);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(windowx / (1.0 + padding) * unlines);
    glBegin(GL_POINTS);
    glVertex3f(pointx, pointy, 1);
    glEnd();
  }

  // green lines
  for (int i = 0; i < points.size() / 3; i++)
  {
    Vector2d a = points[i * 3];
    Vector2d b = points[i * 3 + 1];
    Vector2d c = points[i * 3 + 2];

    drawLine(a, b);
    drawLine(b, c);
    drawLine(c, a);

    BoundBox box;
    box.push_point({a.x, a.y, 0});
    box.push_point({b.x, b.y, 0});
    box.push_point({c.x, c.y, 0});

    printf("center=(%.2f,%.2f,%.2f)\n", box.right_top.x, box.right_top.y, box.right_top.z);
    Vector2d right_top = {box.right_top.x, box.right_top.y};
    Vector2d left_bottom = {box.left_bottom.x, box.left_bottom.y};

    auto x = blockId(left_bottom.x, padding, lines);
    auto xb = blockId(right_top.x, padding, lines);

    auto y = blockId(left_bottom.y, padding, lines);
    auto yb = blockId(right_top.y, padding, lines);
    printf("x=%.2f,xb=%.2f,y=%.2f,yb=%.2f\n", x, xb, y, yb);
    for (int j = x; j <= xb; j++)
    {
      for (int k = y; k <= yb; k++)
      {
        float px = blockIdCoord(floor(j));
        float py = blockIdCoord(floor(k));

        if (isLeft(a, b, {px, py}) && isLeft(b, c, {px, py}) && isLeft(c, a, {px, py}))
        {
          glColor3f(1.0, 0.0, 1.0);
          glBegin(GL_POINTS);
          glVertex3f(px, py, 11);
          glEnd();
        }
        else if (!isLeft(a, b, {px, py}) && !isLeft(b, c, {px, py}) && !isLeft(c, a, {px, py}))
        {
          glColor3f(0.5, 1.0, 1.0);
          glBegin(GL_POINTS);
          glVertex3f(px, py, 11);
          glEnd();
        }
      }
    }
  }

  glutSwapBuffers();
}
