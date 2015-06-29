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
    double h = height;
    double b = width;

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
    double x = postition->p[0];
    double y = postition->p[0];
    double z = postition->p[0];

    Vec3* borderLeftTopCorner = new Vec3();
    borderLeftTopCorner->p[0] = this->B->getPosition()->p[0];
    borderLeftTopCorner->p[0] = this->B->getPosition()->p[1];
    borderLeftTopCorner->p[0] = this->B->getPosition()->p[2];

    Vec3* borderRightBottomCorner = new Vec3();
    borderRightBottomCorner->p[0] = this->D->getPosition()->p[0];
    borderRightBottomCorner->p[0] = this->D->getPosition()->p[1];
    borderRightBottomCorner->p[0] = this->D->getPosition()->p[2];


    if(z != borderLeftTopCorner->p[2]){
        return false;
    }
    if(x <= borderLeftTopCorner->p[0] && x >= borderRightBottomCorner->p[0]){
        return false;
    }
    if(y <= borderLeftTopCorner->p[1] && y >= borderRightBottomCorner->p[1]){
        return false;
    }
    return true;
}
void Rectangle::draw() {
    GlObject::draw();

    Vec3 normal = Vec3(0,0,1);
    Utils::drawPoint(this->originPoint,1);
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