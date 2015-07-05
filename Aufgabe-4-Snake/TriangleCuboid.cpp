//
// Created by Stefan B. on 02.07.15.
//

#include "TriangleCuboid.h"
#include "./../_lib/utils.h"
#include <GLFW/glfw3.h>

TriangleCuboid::TriangleCuboid(double widht, double height, Point *origin) :GlObject(origin){

    this->topArea = new Point(this->originPoint, 0,0,+height/2);
    this->bottomArea = new Point(this->originPoint, 0,0,-height/2);

    this->pointA = new Point(this->topArea, -widht,-widht/2,0);
    this->pointB = new Point(this->topArea, 0,widht,0);
    this->pointC = new Point(this->topArea, widht,-widht/2,0);

    this->pointA_bottom = new Point(this->bottomArea, -widht,-widht/2,0);
    this->pointB_bottom = new Point(this->bottomArea, 0,widht,0);
    this->pointC_bottom = new Point(this->bottomArea, widht,-widht/2,0);



}
bool TriangleCuboid::colidate(Vec3 *point) {
    return false;
}
void TriangleCuboid::draw() {
    GlObject::draw();
    glBegin(GL_TRIANGLES);
    glVertex3f(this->pointA->getPosition()->p[0], this->pointA->getPosition()->p[1], this->pointA->getPosition()->p[2]);
    glVertex3f(this->pointB->getPosition()->p[0], this->pointB->getPosition()->p[1], this->pointB->getPosition()->p[2]);
    glVertex3f(this->pointC->getPosition()->p[0], this->pointC->getPosition()->p[1], this->pointC->getPosition()->p[2]);
    glEnd();


    Utils::drawPoint(this->originPoint,5);
    glBegin(GL_TRIANGLES);
    glVertex3f(this->pointA_bottom->getPosition()->p[0], this->pointA_bottom->getPosition()->p[1], this->pointA_bottom->getPosition()->p[2]);
    glVertex3f(this->pointB_bottom->getPosition()->p[0], this->pointB_bottom->getPosition()->p[1], this->pointB_bottom->getPosition()->p[2]);
    glVertex3f(this->pointC_bottom->getPosition()->p[0], this->pointC_bottom->getPosition()->p[1], this->pointC_bottom->getPosition()->p[2]);
    glEnd();



    glBegin(GL_QUADS);
    glEnable(GL_NORMALIZE);
    glVertex3f(this->pointA_bottom->getPosition()->p[0],this->pointA_bottom->getPosition()->p[1],this->pointA_bottom->getPosition()->p[2]);
    glVertex3f(this->pointA->getPosition()->p[0],this->pointA->getPosition()->p[1],this->pointA->getPosition()->p[2]);
    glVertex3f(this->pointB->getPosition()->p[0],this->pointB->getPosition()->p[1],this->pointB->getPosition()->p[2]);
    glVertex3f(this->pointB_bottom->getPosition()->p[0],this->pointB_bottom->getPosition()->p[1],this->pointB_bottom->getPosition()->p[2]);
    glEnd();



    glBegin(GL_QUADS);
    glEnable(GL_NORMALIZE);
    glVertex3f(this->pointC_bottom->getPosition()->p[0],this->pointC_bottom->getPosition()->p[1],this->pointC_bottom->getPosition()->p[2]);
    glVertex3f(this->pointC->getPosition()->p[0],this->pointC->getPosition()->p[1],this->pointC->getPosition()->p[2]);
    glVertex3f(this->pointB->getPosition()->p[0],this->pointB->getPosition()->p[1],this->pointB->getPosition()->p[2]);
    glVertex3f(this->pointB_bottom->getPosition()->p[0],this->pointB_bottom->getPosition()->p[1],this->pointB_bottom->getPosition()->p[2]);
    glEnd();



    glBegin(GL_QUADS);
    glEnable(GL_NORMALIZE);
    glVertex3f(this->pointA_bottom->getPosition()->p[0],this->pointA_bottom->getPosition()->p[1],this->pointA_bottom->getPosition()->p[2]);
    glVertex3f(this->pointA->getPosition()->p[0],this->pointA->getPosition()->p[1],this->pointA->getPosition()->p[2]);
    glVertex3f(this->pointC->getPosition()->p[0],this->pointC->getPosition()->p[1],this->pointC->getPosition()->p[2]);
    glVertex3f(this->pointC_bottom->getPosition()->p[0],this->pointC_bottom->getPosition()->p[1],this->pointC_bottom->getPosition()->p[2]);
    glEnd();
}