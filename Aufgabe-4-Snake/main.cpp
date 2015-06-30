#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>


#include "../_lib/vec3.hpp"
#include "../_lib/utils.h"
#include "../_lib/Quarter.h"
#include "../_lib/Sphere.h"
#include "Playground.h"
#include "Snake.h"
#include "Cuboid.h"
#include "Rectangle.h"
#include "Point.h"
#include <unistd.h>
using namespace std;


static double alpha_ = 0;
static double window_width_ = 1024;
static double window_height_ = 768;
static double zoom;
double rotateX = 0.0;
double rotateY = 0.0;
double rotateZ = 0.0;
double translateX = 0;
double translateY = 0;
double translateZ = 0;
double previewX = 0;
double previewYOffset = 0;
double previewY = 0;
double zoomValue = 1;
double openPercent = 0;
double sx = 2;
double sy = 2;
const int sz = 1.0;
double step = .5;
bool  gameStarted = false;

//Sphere radius
double sRad = 1;
Vec3 A = Vec3(0, 0, 0.0);
double h = 10;
double b = 5;

std::vector<double> test;

double rx = .1;
double ry = .2;

double zoomINOUT = 0;


Playground * pl = new Playground(10,10,0,0);
Point * origin = new Point(new Vec3(0,0,0));
Cuboid * cuboid = new Cuboid(1,3,origin);
Snake * snake = nullptr;
bool mouseClicked = false;


//Method which listen to defined keys on Keybord with glfw_action (key == GLFW_KEY_W && action == GLFW_REPEAT)
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

  if(action == GLFW_REPEAT  || action == GLFW_PRESS){
    switch (key) {
      case GLFW_KEY_W:
        std::cout << "w"<<std::endl;
            rotateX = 1;
            break;
      case GLFW_KEY_A:
            std::cout << "a"<<std::endl;
            rotateY =  rotateY  -0.1;
            break;
      case GLFW_KEY_S:
        std::cout << "s"<<std::endl;
            rotateX = -1;
            break;
      case GLFW_KEY_D:
        std::cout << "d"<<std::endl;
            rotateY = rotateY + 0.1;
            break;
      case GLFW_KEY_O:
        std::cout << "open"<<std::endl;
            if(openPercent < 100.0){
              openPercent += 0.5;

            }
            break;
      case GLFW_KEY_C:
        std::cout << "close"<<std::endl;
            if(openPercent > -0.5){
              openPercent -= 0.5;
            }
            break;
      case GLFW_KEY_UP:
        std::cout << "up"<<std::endl;
            translateY += 1;
            sy += step;
            break;
      case GLFW_KEY_LEFT:
        std::cout << "left"<<std::endl;
            translateX -= 1;
            sx -= step;
            break;
      case GLFW_KEY_DOWN:
        std::cout << "down"<<std::endl;
            translateY -= 1;
            sy -= step;
            break;
      case GLFW_KEY_RIGHT:
        std::cout << "down"<<std::endl;
            translateX += 1;
            sx +=step;
            break;
      case GLFW_KEY_RIGHT_BRACKET:
        std::cout << "zoom +"<<std::endl;
            zoomValue += 0.2;
            break;
      case GLFW_KEY_SLASH:
        std::cout << "zoom -" <<std::endl;
            zoomValue -= 0.2;
            break;

      case GLFW_KEY_SPACE:
        std::cout << "spalce " <<std::endl;
            gameStarted = true;
            snake = new Snake(origin);
            break;

      case GLFW_KEY_P:
        std::cout << "ZOOM ++" <<std::endl;
      zoomINOUT += 1;
      break;

      case GLFW_KEY_L:
        std::cout << "ZOOM --" <<std::endl;
            zoomINOUT -= 1;
            break;
  }
  }else if(action == GLFW_RELEASE) {
    //rotateX = 0;
    //rotateY = 0;
    //rotateZ = 0;
    //mouseClicked = false;

  }



}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {
    mouseClicked = true;
    std::cout << "ds" << std::endl;
  }else if(button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE) {
    mouseClicked = false;
  }
}

void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset){

  if(previewYOffset < yoffset){
    std::cout << "zoom in" << std::endl;
    zoomValue += 0.02;
  }else {
    std::cout << "zoom out" << std::endl;
    zoomValue -= 0.02;
  }
  previewYOffset = yoffset;
}


void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{

  glfwGetCursorPos(window, &xpos, &ypos);

  if(previewX > xpos && mouseClicked) {
    zoomValue += 0.02;
    std::cout << xpos << std::endl;
  }else if (previewX < xpos && mouseClicked){
    zoomValue -= 0.02;
  }
  previewX = xpos;

}

// set viewport transformations and draw objects
void InitLighting() {
  GLfloat lp1[4]  = { 10,  5,  10,  0};
  GLfloat lp2[4]  = { -5,  5, -10,  0};
  GLfloat red[4]  = {1.0, .8,  .8,  1};
  GLfloat blue[4] = { .8, .8, 1.0,  1};

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
  //glOrtho(-15, 15, -10, 10, -20, 20);
  glOrtho(-15 + zoomINOUT, 15 + zoomINOUT, -10 + zoomINOUT, 10 + zoomINOUT, -20, 20);


  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
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

/*
std::vector<double> distanceFromSIdes(Vec3 k){
  std::vector<double> distances;
    double o = (h-(k.p[1]-A.p[1]))-sRad;
    double l = (k.p[0]-A.p[0])-sRad;
    double r = (b-(k.p[0]-A.p[0]))-sRad;
    double u = (k.p[1]-A.p[1])-sRad;

  distances.push_back(o);
  distances.push_back(l);
  distances.push_back(r);
  distances.push_back(u);
  return distances;
}

std::vector<double> distanceFromSides(Vec3 k){
  std::vector<double> distances;
  //distance from k to top
  double o = (fieldHeight- k.p[1]);
  //distance from k to left side
  double l = (0 + k.p[0]);
  //distance from k to right side
  double r = (fieldWidth-k.p[0]);
  //distance from k to down
  double u = (0+k.p[1]);

  //add distances to vector
  distances.push_back(o);
  distances.push_back(l);
  distances.push_back(r);
  distances.push_back(u);
  return distances;
}
*/

/*
void drawPlayGround(){

  //ground
  glBegin(GL_QUADS);
  SetMaterialColor(1,0,1,0);
  SetMaterialColor(2,0,1,0);
  glVertex3f(0,0,0);
  glVertex3f(fieldWidth,0,0);
  glVertex3f(fieldWidth,fieldHeight,0);
  glVertex3f(0,fieldHeight,0);
  glEnd();
  glFlush();

  //left
  glBegin(GL_QUAD_STRIP);
  SetMaterialColor(1,0,1,0);
  SetMaterialColor(2,0,1,0);
  glVertex3f(0,0,0);
  glVertex3f(0,fieldHeight,0);
  glVertex3f(0,0,fieldZ);
  glVertex3f(0,fieldHeight,fieldZ);
  glEnd();
  glFlush();

  //right
  glBegin(GL_QUAD_STRIP);
  SetMaterialColor(1,0,1,0);
  SetMaterialColor(2,0,1,0);
  glVertex3f(fieldWidth,0,0);
  glVertex3f(fieldWidth,0,fieldZ);
  glVertex3f(fieldWidth,fieldHeight,fieldZ);
  glVertex3f(fieldWidth,fieldHeight,0);
  glEnd();
  glFlush();

  //down
  glBegin(GL_QUAD_STRIP);
  SetMaterialColor(1,0,1,0);
  SetMaterialColor(2,0,1,0);
  glVertex3f(0,0,0);
  glVertex3f(fieldWidth,0,0);
  glVertex3f(fieldWidth,0,fieldZ);
  glVertex3f(0,0,fieldZ);
  glEnd();
  glFlush();

  //Top
  glBegin(GL_QUAD_STRIP);
  SetMaterialColor(1,0,1,0);
  SetMaterialColor(2,0,1,0);
  glVertex3f(0,fieldHeight,0);
  glVertex3f(fieldWidth,fieldHeight,0);
  glVertex3f(fieldWidth,fieldHeight,fieldZ);
  glVertex3f(0,fieldHeight,fieldZ);
  glEnd();
  glFlush();
  //--> Table End

}
 */

int main() {
  GLFWwindow* window = NULL;

  printf("Here we go!\n");

  if(!glfwInit()){
    return -1;
  }

  window = glfwCreateWindow(window_width_, window_height_, "Simple 3D Animation",NULL , NULL);
  // x von -15 -> 15
  // y von -10 -> 10

  if(!window) {
    glfwTerminate();
    return -1;
  }
  //int visible = glfwGetWindowAttrib(window, GLFW_VISIBLE);
  glfwMakeContextCurrent(window);

  //origin->setRotate(new double(M_PI*0.25), new Vec3(1,0,0));

  usleep(1000);
  while(!glfwWindowShouldClose(window)) {

    Point::currentLoopNumber ++;
    //Method that ask the key_callback method for Key inputs
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, mouse_scroll_callback);

    // switch on lighting (or you don't see anything)
    InitLighting();


    // set background color
    glClearColor(0.8, 0.8, 0.8, 1.0);
    //glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRotated(45,1,0,0);
    //glRotated(45,0,0,1);
    alpha_ += 0.1;

    //testing collision
    double x = 0.0;
    double y = 0.0;
    double z = 1.0;
    Vec3 a = Vec3(sx,sy,sz);


    pl->drawPlaygrounD();

    GlObject::setMaterialColorStatic(GlObject::MATERIAL_SIDES::FRONT, 0, 0, 0);
    GlObject::setMaterialColorStatic(GlObject::MATERIAL_SIDES::BACK, 0, 0, 0);

    cuboid->setMaterialColor(GlObject::MATERIAL_SIDES::FRONT,1,0,0);
    cuboid->setMaterialColor(GlObject::MATERIAL_SIDES::BACK,0,0,1);

    cuboid->draw();

    if(gameStarted){
      snake->setRotation(rotateY,*new Vec3(0,1,0));
      snake->draw();
    }

    DrawSphere(a,1);

    //std::vector<double> test = distanceFromSides(a);
    /*std::vector<double> test = pl->distanceFromSideS(a);
    cout <<"O: "<< test[0]<< endl;
    cout <<"L: "<< test[1]<< endl;
    cout <<"R: "<< test[2]<< endl;
    cout <<"U: "<< test[3]<< endl;
*/


    // make it appear (before this, it's hidden in the rear buffer)
    glfwSwapBuffers(window);

    glfwPollEvents();



  }

  glfwTerminate();

  printf("Goodbye!\n");

  return 0;
}
