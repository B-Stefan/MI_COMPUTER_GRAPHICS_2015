//
// Created by Stefan B. on 21.04.15.
//

#include "Plane.h"
#include <GLFW/glfw3.h>
#include "vec3.hpp"


//To set up static vars you should do it like:
Vec3 SIDE_A = Vec3(-1,1,0);
Vec3 SIDE_B = Vec3(1,1,0);
Vec3 SIDE_C = Vec3(1,-1,0);
Vec3 SIDE_D = Vec3(-1,-1,0);


Vec3 Plane::getSide(POINTS point) {
    switch (point){
        case POINTS::A:
            return SIDE_A;
            break;
        case POINTS::B:
            return SIDE_B;
            break;
        case POINTS::C:
            return SIDE_C;
            break;
        case POINTS::D:
            return SIDE_D;
            break;
    }
}
Plane::Plane(Vec3 &middle, double l) {
    this->middle = middle;
    this->rotateCenterVec = Vec3(0,0,0);
    this->rotate_alpha =0.0;
    this->rotate_vec = Vec3(0,0,0);
    this->initRotationVector = Vec3(0,0,0);
    this->initAlpha =0.0;
    this->length = l;
}

void Plane::setInitRotation(double alpha, Vec3 vector) {
    this->initAlpha= alpha;
    this->initRotationVector= vector;
}
void Plane::setRotateCenterVec(Vec3 &a) {
    this->rotateCenterVec = a;
}
void Plane::setRotateVec(Vec3 &a) {
    this->rotate_vec = a;
}
void Plane::setRotateAlpha(double &b) {
    this->rotate_alpha = b;
}
void Plane::setTranslateVec(Vec3 &a) {
    this->translate_vec  = a;
}

void Plane::drawNormal(Vec3 normal) {
    glBegin(GL_LINES);
    glNormal3f(normal.p[0],normal.p[1],normal.p[2]);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0, 0, 0);
    glVertex3f(normal.p[0], normal.p[1], normal.p[2]);
    glEnd();
}

void Plane::drawRotation() {
    glTranslated(this->rotateCenterVec.p[0], this->rotateCenterVec.p[1], this->rotateCenterVec.p[2]);
    glRotated(this->rotate_alpha, this->rotate_vec.p[0], this->rotate_vec.p[1], this->rotate_vec.p[2]);//Init Rotation
    glTranslated(this->rotateCenterVec.p[0]*-1, this->rotateCenterVec.p[1]*-1, this->rotateCenterVec.p[2]*-1);
}
void Plane::draw() {
    Vec3 A = Plane::getSide(Plane::POINTS::A) * this->length;
    Vec3 B = Plane::getSide(Plane::POINTS::B)* this->length;
    Vec3 C = Plane::getSide(Plane::POINTS::C)* this->length;
    Vec3 D = Plane::getSide(Plane::POINTS::D)* this->length;


    glPushMatrix();
    glTranslated( this->middle.p[0]-this->length/2, this->middle.p[1]-this->length/2, this->middle.p[2]-this->length/2);
    glRotated(this->initAlpha, this->initRotationVector.p[0], this->initRotationVector.p[1], this->initRotationVector.p[2]);//Init Rotation

    glEnable(GL_NORMALIZE);
    Vec3 normal = Vec3(0,0,1);
    this->drawNormal(normal);

    //Rotate the system around a local point
    this->drawRotation();


    glBegin(GL_QUADS);
    glNormal3dv(normal.p);
    glVertex3f(A.p[0],A.p[1],A.p[2]);
    glVertex3f(B.p[0],B.p[1],B.p[2]);
    glVertex3f(C.p[0],C.p[1],C.p[2]);
    glVertex3f(D.p[0],D.p[1],D.p[2]);
    glEnd();
    glPopMatrix();
}