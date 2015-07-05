//
// Created by Stefan B. on 09.06.15.
//

#include "Rectangle.h"
#include "./../_lib/utils.h"
#include "GlObject.h"
#include <iostream>
#include <GLFW/glfw3.h>
using namespace std;
Rectangle::Rectangle(double height, double width, Point *origin)
        :GlObject(origin){
    this->height = height;
    this->width= width;
    double h = this->height;
    double b = this->width;

    /**
     *
     *
     *
     * M= middle and after translate coords (0,0,0)
     * A = (-1,1,0) B = ...
     *     y
     *  1   | B               C
     *      |
     *      |
     *      |
     *  0   |         M
     *      |
     *      |
     * -1   | A               D
     *      |
     *      | _________________X
     *       -1      0       1
     */

    this->A = new Point(this->originPoint,-b/2.0,-h/2.0,0);
    this->B = new Point(this->originPoint,-b/2.0, h/2.0,0);
    this->C = new Point(this->originPoint, b/2.0, h/2.0,0);
    this->D = new Point(this->originPoint, b/2.0,-h/2.0,0);


}
bool Rectangle::colidate(Vec3* postition) {
    Vec3 * p = new Vec3(*this->A->getPosition());
    Vec3 * q = new Vec3(*this->B->getPosition());
    Vec3 * r = new Vec3(*this->C->getPosition());
    Vec3 * vecToCenter = new Vec3(*postition  - * this->originPoint->getPosition());

    Vec3 u = *p-*q;
    Vec3 v = *r-*p;
    Vec3 n = u%v;

    double distanceToLayer = fabs((*postition - *p) * n)/n.Length();
    double distanceToCenter = vecToCenter->Length();
    //std::cout << "distanceToCenter" <<distanceToCenter << std::endl;
    if(round(distanceToLayer*100)/100  == 0 && distanceToCenter <= this->width/2){
        return true;
    }
    return false;

}
void Rectangle::draw() {
    GlObject::draw();

    Vec3 normal = Vec3(0,0,1);
    //Begin to draw the plane
    glBegin(GL_QUADS);
    glEnable(GL_NORMALIZE);
    glNormal3dv(normal.p);
    glVertex3f(this->A->getPosition()->p[0],this->A->getPosition()->p[1],this->A->getPosition()->p[2]);
    glVertex3f(this->B->getPosition()->p[0],this->B->getPosition()->p[1],this->B->getPosition()->p[2]);
    glVertex3f(this->C->getPosition()->p[0],this->C->getPosition()->p[1],this->C->getPosition()->p[2]);
    glVertex3f(this->D->getPosition()->p[0],this->D->getPosition()->p[1],this->D->getPosition()->p[2]);
    glEnd();


}