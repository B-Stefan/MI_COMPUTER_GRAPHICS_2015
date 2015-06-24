#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "Cuboid.h"
#include "SnakeHead.h"
#include "Snake.h"
#include "Point.h"
#include "../_lib/vec3.hpp"
#include "../_lib/utils.h"
#include "../_lib/Quarter.h"
#include "../_lib/Sphere.h"


void drawPoint(Point *point, double length) {

  length = length /2;

  Vec3 * origin = point->getPosition();
  Point* z = new Point(point,0,0,length);
  Vec3 * vecZ = z->getPosition();
  //Normal z-axis
  glBegin(GL_LINES);
  glColor3f(0, 1, 0.0);
  glVertex3f(origin->p[0],origin->p[1], origin->p[2]);
  glVertex3f(vecZ->p[0],vecZ->p[1], vecZ->p[2]);
  glEnd();

  Point* x = new Point(point,length,0,0);
  Vec3 * vecX = x->getPosition();
  x->setName(point->getName() + "-x");

  //x-axis
  glBegin(GL_LINES);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(origin->p[0],origin->p[1], origin->p[2]);
  glVertex3f(vecX->p[0],vecX->p[1], vecX->p[2]);
  glEnd();

  Point* y = new Point(point,0,length,0);
  y->setName(point->getName() + "-y");
  Vec3 * vecY = y->getPosition();

  //y-axis
  glBegin(GL_LINES);
  glColor3f(1.0, 0.0, 1.0);
  glVertex3f(origin->p[0],origin->p[1], origin->p[2]);
  glVertex3f(vecY->p[0],vecY->p[1], vecY->p[2]);
  glEnd();


  return;

  cout << "=====> "<< point->getName() << "<====="<< endl;
  Vec3 * vecNormal = point->getNormal();
  Vec3 vecAbsolutPosition = *vecNormal + *point->getPosition();
  Utils::printVec3(*vecNormal, "normal: ");
  glBegin(GL_LINES);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(origin->p[0],origin->p[1], origin->p[2]);
  glVertex3f(vecAbsolutPosition.p[0]*2,vecAbsolutPosition.p[1]*2, vecAbsolutPosition.p[2]*2);
  glEnd();

}

using namespace std;

Vec3* originVec = new Vec3(0,0,-1);
Point* origin = new Point(originVec);
//Cuboid* cube = new Cuboid(1,1,origin);
//cube->setRotationVec()
//SnakeHead* head = new SnakeHead(4,origin);
//Snake * snake = new Snake(origin);
static double alpha_ = 0;
static int window_width_ = 1024;
static int window_height_ = 768;
static double zoom;
double rotateX = 0.0;
double rotateY = 0;
double rotateZ = 0.0;
double translateX = 0;
double translateY = M_PI * 0.5;
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


//versuch by Kai
double const conZ = 0.0;


//Sphere radius
double sRad = 1;
Vec3 A = Vec3(0, 0, 0.0);
double h = 10;
double b = 5;

std::vector<double> test;

double rx = .1;
double ry = .2;

Vec3 point = Vec3(0,0,0);
Vec3* v1= new Vec3(0,0,0);

Vec3* rotationVec = new Vec3(1,0,0);
Vec3* rotationVec2 = new Vec3(0,1,0);


Point* p1 = new Point(v1);
Point* p2 = new Point(p1, 1,0,0);
Point* p3 = new Point(p2, 1,0,0);
Rectangle* rec = new Rectangle(1,1,p3);

double l = 1;
Quarter *box        = new Quarter(point,l);
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
            rotateY =rotateY +0.1;
            break;
      case GLFW_KEY_S:
        std::cout << "s"<<std::endl;
            rotateX = -1;
            break;
      case GLFW_KEY_D:
        std::cout << "d"<<std::endl;
            rotateY = 1;
            break;
      case GLFW_KEY_O:
        std::cout << "open"<<std::endl;
            if(openPercent < 100.0){
              box->setOpenPercentage(openPercent);
              openPercent += 0.5;

            }
            break;
      case GLFW_KEY_C:
        std::cout << "close"<<std::endl;
            if(openPercent > -0.5){
              box->setOpenPercentage(openPercent);
              openPercent -= 0.5;
            }
            break;
      case GLFW_KEY_UP:
        std::cout << "up"<<std::endl;
            translateZ = 0.01;
            sy += step;
            break;
      case GLFW_KEY_LEFT:
        std::cout << "left"<<std::endl;
            translateY = 0.01;
            sx -= step;
            break;
      case GLFW_KEY_DOWN:
        std::cout << "down"<<std::endl;
            translateY -= 0.01;
            sy -= step;
            break;
      case GLFW_KEY_RIGHT:
        std::cout << "down"<<std::endl;
            translateX = 0.01;
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

      }
  }else if(action == GLFW_RELEASE) {
    translateX = 0;
    translateY = 0;
    translateZ = 0;
    rotateX = 0;
    //rotateY = 0;
    rotateZ = 0;
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
void resize_callback(GLFWwindow* window){
  glfwGetWindowSize(window,&window_width_,&window_height_);
}

void frameBufffer_callback(GLFWwindow* window, int width, int height){
  window_width_ = width;
  window_height_ = height;

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

  glClear (GL_COLOR_BUFFER_BIT);
  glColor3f (1.0, 1.0, 1.0);
  glLoadIdentity ();             /* clear the matrix */
  /* viewing transformation  */
  gluLookAt (0.0, 0.0, 15, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0);
  glScalef (1.0, 2.0, 1.0);      /* modeling transformation */
  glutWireCube (1.0);
  glFlush ();


  //glViewport (0, 0, window_width_, window_height_);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glFrustum (-10.0, 10.0, -10.0, 10.0, 10, 20.0);
  glMatrixMode (GL_MODELVIEW);


}


// draw the entire scene
void DrawBox() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  alpha_ +=0.3;
  SetMaterialColor(1,1,0,0);
  Vec3 r = Vec3(rotateX, rotateY, rotateZ);
  Vec3 t = Vec3(translateX, translateY, translateZ);

  box->setTranslateSphere(t);
  box->setRotateVec(r);
  box->setRotateAlpha(alpha_);
  box->setScale(zoomValue);
  box->draw();
  
}


// draw the entire scene
void DrawObjectTest() {
  glRotated(45,1,0,0);
  glRotated(alpha_,0,1,0);
  alpha_ = alpha_ + 0.1;
  /*originVec->p[0] = originVec->p[0] + translateX;
  originVec->p[1] = originVec->p[1] + translateY;
  originVec->p[2] = originVec->p[2] + translateZ;
*/
  Vec3 translationVec = *new Vec3(translateX, translateY, translateZ);
  //drawPoint(p1,1);
  //p2->setDynamicTranslationVec(&translationVec);
  //Utils::printVec3(*p2->getPosition(), "P2");
  //Utils::printVec3(*p1->getPosition(), "P1");
  drawPoint(p1,1);
  drawPoint(p2,1);
  drawPoint(p3,2);
  //drawPoint(p3,3);

  //drawPoint(p2,2);
  //Utils::drawAxis(*p3->getPosition(),3);
  //origin->setDynamicRotate(&rotateY,rotationVec,origin->getPosition());
  rec->draw();

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

  p1->setName("p1");
  p2->setName("p2");
  p1->setDynamicRotate(&rotateY,rotationVec,p1->getPosition());
  p2->setDynamicRotate(&alpha_,rotationVec2,p2->getPosition());
  double angleRec = M_PI*0.5;
  rec->rotate(&angleRec,new Vec3(0,1,0),p3);
  while(!glfwWindowShouldClose(window)) {

    //Method that ask the key_callback method for Key inputs
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, mouse_scroll_callback);
    glfwSetWindowRefreshCallback(window, resize_callback);
    glfwSetFramebufferSizeCallback(window, frameBufffer_callback);
    // switch on lighting (or you don't see anything)
    InitLighting();

    // set background color
    glClearColor(0.8, 0.8, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    DrawObjectTest();

    // make it appear (before this, it's hidden in the rear buffer)
    glfwSwapBuffers(window);

    glfwPollEvents();



  }

  glfwTerminate();

  printf("Goodbye!\n");

  return 0;
}
