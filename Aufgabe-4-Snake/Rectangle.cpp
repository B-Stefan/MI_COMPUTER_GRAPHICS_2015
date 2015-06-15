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
    this->defaultRotationVec = new Vec3(0,0,0);
    this->defaultRotationAngle = new double();
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
    this->A = new Point(origin,-b/2.0,-h/2.0,0);
    this->B = new Point(origin,-b/2.0, h/2.0,0);
    this->C = new Point(origin, b/2.0, h/2.0,0);
    this->D = new Point(origin, b/2.0,-h/2.0,0);

    this->A->setDefaultRotation(this->defaultRotationAngle, this->defaultRotationVec);
    this->B->setDefaultRotation(this->defaultRotationAngle, this->defaultRotationVec);
    this->C->setDefaultRotation(this->defaultRotationAngle, this->defaultRotationVec);
    this->D->setDefaultRotation(this->defaultRotationAngle, this->defaultRotationVec);
}
void Rectangle::setDefaultRotation(double angle, double x, double y, double z) {
    this->defaultRotationVec->p[0] = x;
    this->defaultRotationVec->p[1] = y;
    this->defaultRotationVec->p[2] = z;
    *this->defaultRotationAngle = angle;
}
void Rectangle::rotate(double *angle, Vec3 *rotationVec, Point *origin) {
    this->A->setDynamicRotate(angle, rotationVec, origin->getPosition());
    this->B->setDynamicRotate(angle, rotationVec, origin->getPosition());
    this->C->setDynamicRotate(angle, rotationVec, origin->getPosition());
    this->D->setDynamicRotate(angle, rotationVec, origin->getPosition());
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