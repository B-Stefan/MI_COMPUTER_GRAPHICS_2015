//
// Created by Stefan B. on 02.07.15.
//

#include "Triangle.h"
#include <GLFW/glfw3.h>

Triangle::Triangle(double l, Point *origin) :GlObject(origin){

    this->pointA = new Point(this->originPoint, -l/2,-l/2,0);
    this->pointB = new Point(this->originPoint, 0,l/2,0);
    this->pointC = new Point(this->originPoint, l/2,l/2,0);
}
void Triangle::draw() {
    glBegin(GL_TRIANGLES);
    glVertex3f(this->pointA->getPosition()->p[0], this->pointA->getPosition()->p[1], this->pointA->getPosition()->p[2]);
    glVertex3f(this->pointB->getPosition()->p[0], this->pointB->getPosition()->p[1], this->pointB->getPosition()->p[2]);
    glVertex3f(this->pointC->getPosition()->p[0], this->pointC->getPosition()->p[1], this->pointC->getPosition()->p[2]);
    glEnd();
}