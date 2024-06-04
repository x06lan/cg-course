
/*** freeglut***/
#ifdef _MSC_VER
#include "windows.h"
#pragma comment(lib, "opengl32.lib")
#endif

#include <GLTools.h> // OpenGL toolkit
#include <math3d.h>
#include <GL/gl.h>
#include <stdio.h>
#include <freeglut.h>
#include <freeglut_std.h>

#include "time.h"

#include "obj.hpp"
#include "matrix.hpp"
#include <vector>
#include <random>

#include <iostream>
#include <math.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Shadow.cpp
// OpenGL SuperBible
// Demonstrates simple planar shadows
// Program by Richard S. Wright Jr.

// #include "../../shared/gltools.h"
// #include "../../shared/math3d.h"

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

// These values need to be available globally
// Light values and coordinates
int lightId = 0;
GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
GLfloat diffuseLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat lightPos[4][4] = {{-75.0f, 200.0f, -50.0f, 0.0f},
                          {-75.0f, 150.0f, -50.0f, 0.0f},
                          {-75.0f, 100.0f, -50.0f, 0.0f},
                          {-75.0f, 50.0f, -50.0f, 0.0f}};
GLfloat specref[] = {1.0f, 1.0f, 1.0f, 1.0f};

// Transformation matrix to project shadow
M3DMatrix44f shadowMat;

void cube()
{
  {
    // Define the vertices for the cube
    // M3DVector3f vCube[8] = {
    //     {0.0f, 0.0f, 0.0f},    // 0 Bottom back left
    //     {15.0f, 0.0f, 0.0f},   // 1 Bottom back right
    //     {15.0f, 15.0f, 0.0f},  // 2 Top back right
    //     {0.0f, 15.0f, 0.0f},   // 3 Top back left
    //     {0.0f, 0.0f, 15.0f},   // 4 Bottom front left
    //     {15.0f, 0.0f, 15.0f},  // 5 Bottom front right
    //     {15.0f, 15.0f, 15.0f}, // 6 Top front right
    //     {0.0f, 15.0f, 15.0f}   // 7 Top front left
    // };
    M3DVector3f vCube[8] = {
        {-7.5f, -7.5f, -7.5f}, // 0 Bottom back left
        {7.5f, -7.5f, -7.5f},  // 1 Bottom back right
        {7.5f, 7.5f, -7.5f},   // 2 Top back right
        {-7.5f, 7.5f, -7.5f},  // 3 Top back left
        {-7.5f, -7.5f, 7.5f},  // 4 Bottom front left
        {7.5f, -7.5f, 7.5f},   // 5 Bottom front right
        {7.5f, 7.5f, 7.5f},    // 6 Top front right
        {-7.5f, 7.5f, 7.5f}    // 7 Top front left
    };

    M3DVector3f vNormal;

    // Front face
    m3dFindNormal(vNormal, vCube[4], vCube[5], vCube[6]);
    glNormal3fv(vNormal);
    glVertex3fv(vCube[4]);
    glVertex3fv(vCube[5]);
    glVertex3fv(vCube[6]);
    m3dFindNormal(vNormal, vCube[4], vCube[6], vCube[7]);
    glNormal3fv(vNormal);
    glVertex3fv(vCube[4]);
    glVertex3fv(vCube[6]);
    glVertex3fv(vCube[7]);

    // Back face
    m3dFindNormal(vNormal, vCube[1], vCube[0], vCube[3]);
    glNormal3fv(vNormal);
    glVertex3fv(vCube[1]);
    glVertex3fv(vCube[0]);
    glVertex3fv(vCube[3]);
    m3dFindNormal(vNormal, vCube[1], vCube[3], vCube[2]);
    glNormal3fv(vNormal);
    glVertex3fv(vCube[1]);
    glVertex3fv(vCube[3]);
    glVertex3fv(vCube[2]);

    // Left face
    m3dFindNormal(vNormal, vCube[0], vCube[4], vCube[7]);
    glNormal3fv(vNormal);
    glVertex3fv(vCube[0]);
    glVertex3fv(vCube[4]);
    glVertex3fv(vCube[7]);
    m3dFindNormal(vNormal, vCube[0], vCube[7], vCube[3]);
    glNormal3fv(vNormal);
    glVertex3fv(vCube[0]);
    glVertex3fv(vCube[7]);
    glVertex3fv(vCube[3]);

    // Right face
    m3dFindNormal(vNormal, vCube[5], vCube[1], vCube[2]);
    glNormal3fv(vNormal);
    glVertex3fv(vCube[5]);
    glVertex3fv(vCube[1]);
    glVertex3fv(vCube[2]);
    m3dFindNormal(vNormal, vCube[5], vCube[2], vCube[6]);
    glNormal3fv(vNormal);
    glVertex3fv(vCube[5]);
    glVertex3fv(vCube[2]);
    glVertex3fv(vCube[6]);

    // Top face
    m3dFindNormal(vNormal, vCube[3], vCube[7], vCube[6]);
    glNormal3fv(vNormal);
    glVertex3fv(vCube[3]);
    glVertex3fv(vCube[7]);
    glVertex3fv(vCube[6]);
    m3dFindNormal(vNormal, vCube[3], vCube[6], vCube[2]);
    glNormal3fv(vNormal);
    glVertex3fv(vCube[3]);
    glVertex3fv(vCube[6]);
    glVertex3fv(vCube[2]);

    // Bottom face
    m3dFindNormal(vNormal, vCube[4], vCube[0], vCube[1]);
    glNormal3fv(vNormal);
    glVertex3fv(vCube[4]);
    glVertex3fv(vCube[0]);
    glVertex3fv(vCube[1]);
    m3dFindNormal(vNormal, vCube[4], vCube[1], vCube[5]);
    glNormal3fv(vNormal);
    glVertex3fv(vCube[4]);
    glVertex3fv(vCube[1]);
    glVertex3fv(vCube[5]);
  }
}
////////////////////////////////////////////////
// This function just specifically draws the jet
void DrawJet(int nShadow)
{
  M3DVector3f vNormal; // Storeage for calculated surface normal

  // Nose Cone /////////////////////////////
  // Set material color, note we only have to set to black
  // for the shadow once
  if (nShadow == 0)
    glColor3ub(255, 0, 0);
  else
    glColor3ub(100, 0, 0);

  // Nose Cone - Points straight down
  // Set material color
  glPushMatrix();
  glTranslatef(0, 80, 0);

  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);

  glBegin(GL_TRIANGLES);
  glNormal3f(0.0f, -1.0f, 0.0f);
  glNormal3f(0.0f, -1.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 60.0f);
  glVertex3f(-15.0f, 0.0f, 30.0f);
  glVertex3f(15.0f, 0.0f, 30.0f);

  // Verticies for this panel
  {
    M3DVector3f vPoints[3] = {{15.0f, 0.0f, 30.0f},
                              {0.0f, 15.0f, 30.0f},
                              {0.0f, 0.0f, 60.0f}};

    // Calculate the normal for the plane
    m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
    glNormal3fv(vNormal);
    glVertex3fv(vPoints[0]);
    glVertex3fv(vPoints[1]);
    glVertex3fv(vPoints[2]);
  }

  {
    M3DVector3f vPoints[3] = {{0.0f, 0.0f, 60.0f},
                              {0.0f, 15.0f, 30.0f},
                              {-15.0f, 0.0f, 30.0f}};

    m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
    glNormal3fv(vNormal);
    glVertex3fv(vPoints[0]);
    glVertex3fv(vPoints[1]);
    glVertex3fv(vPoints[2]);
  }

  // Body of the Plane ////////////////////////
  {
    M3DVector3f vPoints[3] = {{-15.0f, 0.0f, 30.0f},
                              {0.0f, 15.0f, 30.0f},
                              {0.0f, 0.0f, -56.0f}};

    m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
    glNormal3fv(vNormal);
    glVertex3fv(vPoints[0]);
    glVertex3fv(vPoints[1]);
    glVertex3fv(vPoints[2]);
  }

  {
    M3DVector3f vPoints[3] = {{0.0f, 0.0f, -56.0f},
                              {0.0f, 15.0f, 30.0f},
                              {15.0f, 0.0f, 30.0f}};

    m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
    glNormal3fv(vNormal);
    glVertex3fv(vPoints[0]);
    glVertex3fv(vPoints[1]);
    glVertex3fv(vPoints[2]);
  }

  glNormal3f(0.0f, -1.0f, 0.0f);
  glVertex3f(15.0f, 0.0f, 30.0f);
  glVertex3f(-15.0f, 0.0f, 30.0f);
  glVertex3f(0.0f, 0.0f, -56.0f);

  ///////////////////////////////////////////////
  // Left wing
  // Large triangle for bottom of wing
  {
    M3DVector3f vPoints[3] = {{0.0f, 2.0f, 27.0f},
                              {-60.0f, 2.0f, -8.0f},
                              {60.0f, 2.0f, -8.0f}};

    m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
    glNormal3fv(vNormal);
    glVertex3fv(vPoints[0]);
    glVertex3fv(vPoints[1]);
    glVertex3fv(vPoints[2]);
  }

  {
    M3DVector3f vPoints[3] = {{60.0f, 2.0f, -8.0f},
                              {0.0f, 7.0f, -8.0f},
                              {0.0f, 2.0f, 27.0f}};

    m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
    glNormal3fv(vNormal);
    glVertex3fv(vPoints[0]);
    glVertex3fv(vPoints[1]);
    glVertex3fv(vPoints[2]);
  }

  {
    M3DVector3f vPoints[3] = {{60.0f, 2.0f, -8.0f},
                              {-60.0f, 2.0f, -8.0f},
                              {0.0f, 7.0f, -8.0f}};

    m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
    glNormal3fv(vNormal);
    glVertex3fv(vPoints[0]);
    glVertex3fv(vPoints[1]);
    glVertex3fv(vPoints[2]);
  }

  {
    M3DVector3f vPoints[3] = {{0.0f, 2.0f, 27.0f},
                              {0.0f, 7.0f, -8.0f},
                              {-60.0f, 2.0f, -8.0f}};

    m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
    glNormal3fv(vNormal);
    glVertex3fv(vPoints[0]);
    glVertex3fv(vPoints[1]);
    glVertex3fv(vPoints[2]);
  }

  // Tail section///////////////////////////////
  // Bottom of back fin
  glNormal3f(0.0f, -1.0f, 0.0f);
  glVertex3f(-30.0f, -0.50f, -57.0f);
  glVertex3f(30.0f, -0.50f, -57.0f);
  glVertex3f(0.0f, -0.50f, -40.0f);

  {
    M3DVector3f vPoints[3] = {{0.0f, -0.5f, -40.0f},
                              {30.0f, -0.5f, -57.0f},
                              {0.0f, 4.0f, -57.0f}};

    m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
    glNormal3fv(vNormal);
    glVertex3fv(vPoints[0]);
    glVertex3fv(vPoints[1]);
    glVertex3fv(vPoints[2]);
  }

  {
    M3DVector3f vPoints[3] = {{0.0f, 4.0f, -57.0f},
                              {-30.0f, -0.5f, -57.0f},
                              {0.0f, -0.5f, -40.0f}};

    m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
    glNormal3fv(vNormal);
    glVertex3fv(vPoints[0]);
    glVertex3fv(vPoints[1]);
    glVertex3fv(vPoints[2]);
  }

  {
    M3DVector3f vPoints[3] = {{30.0f, -0.5f, -57.0f},
                              {-30.0f, -0.5f, -57.0f},
                              {0.0f, 4.0f, -57.0f}};

    m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
    glNormal3fv(vNormal);
    glVertex3fv(vPoints[0]);
    glVertex3fv(vPoints[1]);
    glVertex3fv(vPoints[2]);
  }

  {
    M3DVector3f vPoints[3] = {{0.0f, 0.5f, -40.0f},
                              {3.0f, 0.5f, -57.0f},
                              {0.0f, 25.0f, -65.0f}};

    m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
    glNormal3fv(vNormal);
    glVertex3fv(vPoints[0]);
    glVertex3fv(vPoints[1]);
    glVertex3fv(vPoints[2]);
  }

  {
    M3DVector3f vPoints[3] = {{0.0f, 25.0f, -65.0f},
                              {-3.0f, 0.5f, -57.0f},
                              {0.0f, 0.5f, -40.0f}};

    m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
    glNormal3fv(vNormal);
    glVertex3fv(vPoints[0]);
    glVertex3fv(vPoints[1]);
    glVertex3fv(vPoints[2]);
  }

  {
    M3DVector3f vPoints[3] = {{3.0f, 0.5f, -57.0f},
                              {-3.0f, 0.5f, -57.0f},
                              {0.0f, 25.0f, -65.0f}};

    m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
    glNormal3fv(vNormal);
    glVertex3fv(vPoints[0]);
    glVertex3fv(vPoints[1]);
    glVertex3fv(vPoints[2]);
  }

  glEnd();
  glPopMatrix();

  float x = 0, y = 0, z = 0;
  float rotX = 0, rotY = 0, rotZ = 0;
  //
  // Create the robot body
  // glPushMatrix();
  // glTranslatef(0, 0, 0);
  // glRotatef(rotX, 1.0f, 0.0f, 0.0f);
  // glRotatef(rotY, 0.0f, 1.0f, 0.0f);
  // glRotatef(rotZ, 0.0f, 0.0f, 1.0f);
  // glBegin(GL_TRIANGLES);
  // cube();
  // glEnd();
  // glPopMatrix();

  glPushMatrix();

  // Apply transformations for the whole robot
  glTranslatef(0, 0, 0);
  glRotatef(xRot, 1.0f, 0.0f, 0.0f);

  // body
  glPushMatrix();
  glTranslatef(0, 0, 0);
  glScalef(2, 4, 1);
  // glRotatef(rotX, 1.0f, 0.0f, 0.0f);
  // glRotatef(rotY, 0.0f, 1.0f, 0.0f);
  // glRotatef(rotZ, 0.0f, 0.0f, 1.0f);
  glBegin(GL_TRIANGLES);
  cube();
  glEnd();
  glPopMatrix();

  // head
  glPushMatrix();
  glTranslatef(0, 40, 0);
  glScalef(2, 1, 1);
  // glRotatef(rotX, 1.0f, 0.0f, 0.0f);
  // glRotatef(rotY, 0.0f, 1.0f, 0.0f);
  // glRotatef(rotZ, 0.0f, 0.0f, 1.0f);
  glBegin(GL_TRIANGLES);
  cube();
  glEnd();
  glPopMatrix();

  // left arm
  glPushMatrix();
  glRotatef(yRot, 1.0f, 0.0f, 0.0f);

  glTranslatef(23, 10, 0);
  glScalef(0.7, 2, 1);

  glBegin(GL_TRIANGLES);
  cube();
  glEnd();

  glPopMatrix();

  // right arm
  glPushMatrix();
  glRotatef(yRot, 1.0f, 0.0f, 0.0f);

  glTranslatef(-23, 10, 0);
  glScalef(0.7, 2, 1);

  glBegin(GL_TRIANGLES);
  cube();
  glEnd();
  glPopMatrix();

  // left leg
  glPushMatrix();
  glTranslatef(10, -40, 0);
  glScalef(0.7, 2, 1);

  glBegin(GL_TRIANGLES);
  cube();
  glEnd();
  glPopMatrix();

  // right leg
  glPushMatrix();
  glTranslatef(-10, -40, 0);
  glScalef(0.7, 2, 1);
  // glRotatef(rotX, 1.0f, 0.0f, 0.0f);
  // glRotatef(rotY, 0.0f, 1.0f, 0.0f);
  // glRotatef(rotZ, 0.0f, 0.0f, 1.0f);
  glBegin(GL_TRIANGLES);
  cube();
  glEnd();
  glPopMatrix();

  glPopMatrix();
}

// Called to draw scene
void RenderScene(void)
{
  // Clear the window with current clearing color
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Draw the ground, we do manual shading to a darker green
  // in the background to give the illusion of depth
  glBegin(GL_QUADS);
  glColor3ub(0, 32, 0); // light green ground
  glVertex3f(400.0f, -150.0f, -200.0f);
  glVertex3f(-400.0f, -150.0f, -200.0f);
  glColor3ub(0, 255, 0); // make it in green gradient
  glVertex3f(-400.0f, -150.0f, 200.0f);
  glVertex3f(400.0f, -150.0f, 200.0f);
  glEnd();

  // Save the matrix state and do the rotations
  glPushMatrix();

  // Draw jet at new orientation, put light in correct position
  // before rotating the jet
  glEnable(GL_LIGHTING);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos[lightId]);

  DrawJet(0);

  // Restore original matrix state
  glPopMatrix();

  // Get ready to draw the shadow and the ground
  // First disable lighting and save the projection state
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glPushMatrix();

  // Multiply by shadow projection matrix
  glMultMatrixf((GLfloat *)shadowMat);

  // // Now rotate the jet around in the new flattend space
  // glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  // glRotatef(yRot, 0.0f, 1.0f, 0.0f);

  // Pass true to indicate drawing shadow
  DrawJet(1);

  // Restore the projection to normal
  glPopMatrix();

  // Draw the light source
  glPushMatrix();
  glTranslatef(lightPos[lightId][0], lightPos[lightId][1], lightPos[lightId][2]);
  glColor3ub(255, 0, 0);
  glutSolidSphere(5.0f, 10, 10);
  glPopMatrix();

  // Restore lighting state variables
  glEnable(GL_DEPTH_TEST);

  // Display the results
  glutSwapBuffers();
}

// This function does any needed initialization on the rendering
// context.
void SetupRC()
{
  // Any three points on the ground (counter clockwise order)
  M3DVector3f points[3] = {{-30.0f, -149.0f, -20.0f},
                           {-30.0f, -149.0f, 20.0f},
                           {40.0f, -149.0f, 20.0f}};

  glEnable(GL_DEPTH_TEST); // Hidden surface removal
  glFrontFace(GL_CCW);     // Counter clock-wise polygons face out
  glEnable(GL_CULL_FACE);  // Do not calculate inside of jet

  // Setup and enable light 0
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos[lightId]);
  glEnable(GL_LIGHT0);

  // Enable color tracking
  glEnable(GL_COLOR_MATERIAL);

  // Set Material properties to follow glColor values
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

  // All materials hereafter have full specular reflectivity
  // with a high shine
  glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
  glMateriali(GL_FRONT, GL_SHININESS, 128);

  // Light blue background
  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

  // Get the plane equation from three points on the ground
  M3DVector4f vPlaneEquation;
  m3dGetPlaneEquation(vPlaneEquation, points[0], points[1], points[2]);

  // Calculate projection matrix to draw shadow on the ground
  m3dMakePlanarShadowMatrix(shadowMat, vPlaneEquation, lightPos[lightId]);

  glEnable(GL_NORMALIZE);
}

void SpecialKeys(int key, int x, int y)
{
  if (key == GLUT_KEY_UP)
    xRot -= 5.0f;

  if (key == GLUT_KEY_DOWN)
    xRot += 5.0f;

  if (key == GLUT_KEY_LEFT)
    yRot -= 5.0f;

  if (key == GLUT_KEY_RIGHT)
    yRot += 5.0f;

  if (key > 356.0f)
    xRot = 0.0f;

  if (key < -1.0f)
    xRot = 355.0f;

  if (key > 356.0f)
    yRot = 0.0f;

  if (key < -1.0f)
    yRot = 355.0f;

  // Refresh the Window
  glutPostRedisplay();
}
void NormalKeyHandler(unsigned char key, int x, int y)
{
  if (key == '1')
    lightId = 0;
  if (key == '2')
    lightId = 1;
  if (key == '3')
    lightId = 2;
  if (key == '4')
    lightId = 3;
  printf("lightId: %d\n", lightId);
  SetupRC();
  glutPostRedisplay();
}
void ChangeSize(int w, int h)
{
  GLfloat fAspect;

  // Prevent a divide by zero
  if (h == 0)
    h = 1;

  // Set Viewport to window dimensions
  glViewport(0, 0, w, h);

  // Reset coordinate system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  fAspect = (GLfloat)w / (GLfloat)h;
  gluPerspective(60.0f, fAspect, 200.0, 500.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Move out Z axis so we can see everything
  glTranslatef(0.0f, 0.0f, -400.0f);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos[lightId]);
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Shadow");
  glutReshapeFunc(ChangeSize);
  glutSpecialFunc(SpecialKeys);
  glutKeyboardFunc(NormalKeyHandler);
  glutDisplayFunc(RenderScene);
  SetupRC();
  glutMainLoop();

  return 0;
}
