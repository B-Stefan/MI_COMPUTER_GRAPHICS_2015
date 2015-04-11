#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

#include "../_lib/vec3.hpp"
#include "../_lib/DarwQuarter.h"

using namespace std;

static double alpha_ = 0;
static double window_width_ = 1024;
static double window_height_ = 768;
static double zoom;
double rotateX = 0.0;
double rotateY = 0.0;
double rotateZ = 0.0;

//Method which listen to defined keys on Keybord with glfw_action (key == GLFW_KEY_W && action == GLFW_REPEAT)
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

  if(action == GLFW_RELEASE){
      if(rotateX != 0){
        rotateY = 0;
      }
      if(rotateY != 0){
      rotateX = 0;
      }
      //alpha_ += 0;




  }

  if (key == GLFW_KEY_W && action == GLFW_REPEAT || key == GLFW_KEY_W && action == GLFW_PRESS){
    cout << "w"<<endl;
    rotateX = 1;
    alpha_ += 10;
  }
  if (key == GLFW_KEY_A && action == GLFW_REPEAT || key == GLFW_KEY_A && action == GLFW_PRESS){
    cout << "a"<<endl;
    rotateY = -1;
    alpha_ += 10;

  }
  if (key == GLFW_KEY_S && action == GLFW_REPEAT|| key == GLFW_KEY_S && action == GLFW_PRESS){
    cout << "s"<<endl;
    rotateX = -1;
    alpha_ += 10;

  }
  if (key == GLFW_KEY_D && action == GLFW_REPEAT|| key == GLFW_KEY_D && action == GLFW_PRESS){
    cout << "d"<<endl;
      rotateY = 1;
      alpha_ += 10;

  }
  if (key == GLFW_KEY_O && action == GLFW_REPEAT|| key == GLFW_KEY_O && action == GLFW_PRESS){
    cout << "o"<<endl;
  }
  if (key == GLFW_KEY_C && action == GLFW_REPEAT|| key == GLFW_KEY_C && action == GLFW_PRESS){
    cout << "c"<<endl;
  }



}


// draw a sphere composed of triangles
void DrawSphere(const Vec3& ctr, double r){
  int     i, j,
          n1 = 24, n2 = 32;
  Vec3    normal, v1;
  double  a1, a1d = M_PI / n1,
          a2, a2d = M_PI / n2,
          s1, s2,
          c1, c2;

  glShadeModel(GL_SMOOTH);
  for(i = 0; i < n1; i++){
    a1 = i * a1d;

    glBegin(GL_TRIANGLE_STRIP);
    for(j = 0; j <= n2; j++){
      a2 = (j + .5 * (i % 2)) * 2 * a2d;

      s1 = sin(a1);
      c1 = cos(a1);
      s2 = sin(a2);
      c2 = cos(a2);
      normal = c1 * XVec3 + s1 * (c2 * YVec3 + s2 * ZVec3);
      v1 = ctr + r * normal;
      glNormal3dv(normal.p);
      glVertex3dv(v1.p);

      s1 = sin(a1 + a1d);
      c1 = cos(a1 + a1d);
      s2 = sin(a2 + a2d);
      c2 = cos(a2 + a2d);
      normal = c1 * XVec3 + s1 * (c2 * YVec3 + s2 * ZVec3);
      v1 = ctr + r * normal;
      glNormal3dv(normal.p);
      glVertex3dv(v1.p);
    }
    glEnd();
  }
}

void SetMaterialColor(int side, double r, double g, double b) {
  float	amb[4], dif[4], spe[4];
  int mat;

  dif[0] = r;
  dif[1] = g;
  dif[2] = b;

  for(int i = 0; i < 3; i++) {
    amb[i] = .1 * dif[i];
    spe[i] = .5;
  }
  amb[3] = dif[3] = spe[3] = 1.0;

  switch(side){
    case 1:	mat = GL_FRONT;
      break;
    case 2:	mat = GL_BACK;
      break;
    default: mat = GL_FRONT_AND_BACK;
  }

  glMaterialfv(mat, GL_AMBIENT, amb);
  glMaterialfv(mat, GL_DIFFUSE, dif);
  glMaterialfv(mat, GL_SPECULAR, spe);
  glMaterialf( mat, GL_SHININESS, 20);
}



// set viewport transformations and draw objects
void InitLighting() {
  GLfloat lp1[4]  = { 10,  5,  10,  0};
  GLfloat lp2[4]  = { -5,  5, -10,  0};
  GLfloat red[4]  = {10, .8,  .8,  1};
  GLfloat blue[4] = { 0, 10, 1.0,  1};

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glShadeModel(GL_SMOOTH);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
  glEnable(GL_LIGHTING);

  glLightfv(GL_LIGHT1, GL_POSITION, lp1);
  glLightfv(GL_LIGHT1, GL_DIFFUSE,  red);
  glLightfv(GL_LIGHT1, GL_SPECULAR, red);
  glEnable(GL_LIGHT1);

  glLightfv(GL_LIGHT2, GL_POSITION, lp2);
  glLightfv(GL_LIGHT2, GL_DIFFUSE,  blue);
  glLightfv(GL_LIGHT2, GL_SPECULAR, blue);
  glEnable(GL_LIGHT2);

  glClearColor(1, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // init viewport to canvassize
  glViewport(0, 0, window_width_, window_height_);

  // init coordinate system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-15, 15, -10, 10, -20, 20);


  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void drawTriangle(const Vec3& A,const Vec3& B,const Vec3& Top){
  glBegin(GL_TRIANGLES);            // Start Drawing A Triangle
  glNormal3f( 0.0,  0.0, 1.0);			// Set Top Point Of Triangle To Red
  glVertex3f( A.p[0],  A.p[1], A.p[2]);
  glVertex3f( Top.p[0], Top.p[1], Top.p[2]);  // First Point Of The Triangle
  glVertex3f( B.p[0],  B.p[1], B.p[2]);      // First Point Of The Triangle
  glEnd();
}



void drawPyramid(){
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();						    // Reset The Current Modelview Matrix
  glTranslated(-7, -7, -10.0);      // Move 10 units backwards in z,
  // since camera is at origin

  glRotated(alpha_, rotateX, rotateY, rotateZ);

  double Size = 4;

  Vec3 A = Size * Vec3(1,2,0) ;
  Vec3 B = Size * Vec3(2,2,0);
  Vec3 C = Size * Vec3(2,1,0);
  Vec3 D = Size * Vec3(1,1,0);

  Vec3 Top = Size * Vec3(1.5,1.5,1);


  SetMaterialColor(1, 1, 0, 0);
  SetMaterialColor(2, 0, 1, 0);
  zoom = 5;
  glBegin(GL_QUADS);            // Start Drawing A Triangle
  glVertex3f(A.p[0],A.p[1],A.p[2]);
  glVertex3f(B.p[0],B.p[1],B.p[2]);
  glVertex3f(C.p[0],C.p[1],C.p[2]);
  glVertex3f(D.p[0],D.p[1],D.p[2]);
  glEnd();


  SetMaterialColor(2, 1, 0, 0);
  SetMaterialColor(1, 1, 0, 0);
  drawTriangle(A,B,Top);
  SetMaterialColor(2, 0, 1, 0);
  SetMaterialColor(1, 0, 1, 0);
  drawTriangle(B,C,Top);
  SetMaterialColor(2, 0, 0, 1);
  SetMaterialColor(1, 0, 0, 1);
  drawTriangle(C,D,Top);

  SetMaterialColor(2, 0, 1, 1);
  SetMaterialColor(1, 0, 1, 1);
  drawTriangle(D,A,Top);
  glTranslated(7, 7, 10.0);      // Move 10 units backwards in z,

}



// draw the entire scene
void Preview() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();						    // Reset The Current Modelview Matrix
  glTranslated(0, 0, -10.0);      // Move 10 units backwards in z,
                                  // since camera is at origin
  glRotated(alpha_, rotateX, rotateY, rotateZ);


  Vec3 point = Vec3(0,0,1);
  double l = 5;
  DarwQuarter::drawQuarter(point,l);
}



int main() {
  GLFWwindow* window = NULL;

  printf("Here we go!\n");

  if(!glfwInit()){
    return -1;
  }

  window = glfwCreateWindow(window_width_, window_height_,
                            "Simple 3D Animation", NULL, NULL);
  if(!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  while(!glfwWindowShouldClose(window)) {


    //Method that ask the key_callback method for Key inputs
    glfwSetKeyCallback(window, key_callback);


    // switch on lighting (or you don't see anything)
    InitLighting();

    // set background color
    glClearColor(0.8, 0.8, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw the scene

    //alpha_ += 10;
    Preview();

    // make it appear (before this, it's hidden in the rear buffer)
    glfwSwapBuffers(window);

    glfwPollEvents();

  }

  glfwTerminate();

  printf("Goodbye!\n");

  return 0;
}