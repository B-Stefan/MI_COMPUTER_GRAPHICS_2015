//
// Created by Stefan B. on 21.04.15.
//

#include "Plane.h"
#include "utils.h"
#include <GLFW/glfw3.h>
#include <GLUT/glut.h>
#include "vec3.hpp"
#include <iostream>


//To set up static vars you should do it like:
Vec3 SIDE_A = Vec3(-1,1,0);
Vec3 SIDE_B = Vec3(1,1,0);
Vec3 SIDE_C = Vec3(1,-1,0);
Vec3 SIDE_D = Vec3(-1,-1,0);


//Set up Static getter
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

/*
 * Plane  class to draw, move and rotate a plane
 */
Plane::Plane(Vec3 &middle, double l) {
    this->middle = middle;
    this->rotateCenterVec = Vec3(0,0,0);
    this->rotate_alpha =0.0;
    this->rotate_vec = Vec3(0,0,0);
    this->initRotationVector = Vec3(0,0,0);
    this->initAlpha =0.0;
    this->length = l;
    this->globalA = Vec3(0,0,0);
    this->globalB = Vec3(0,0,0);
    this->globalC = Vec3(0,0,0);
    this->globalD = Vec3(0,0,0);
}

/**
 * Set the initial rotation to rotate the whole plane
 * This is important for reflection @see Quater.cpp
 *
 * Example:
 *
 * alpha = 90
 * vector = (0,1,0)
 *
 * The plane draw like this
 *     y
 *  1   | D               A
 *      |
 *      |
 *      |
 *  0   |         M
 *      |
 *      |
 * -1   | C               B
 *      |
 *      | _________________X
 *       -1      0       1
 *
 */
void Plane::setInitRotation(double alpha, Vec3 vector) {
    this->initAlpha= alpha;
    this->initRotationVector= vector;
}

/**
 * Set the vector for rotation
 * This is important to rotate not only over the center point see usage @plan.cpp
 *
 * Example:
 *
 * a = (0,1,0)
 * a = (1,1) = Point B
 * a = (-1,1) = Point A
 *
 * The center of the system is move like this
 *
 * R = Rotation point so the plan can rotated over this point
 *     y
 *  1   | A       R       B
 *      |
 *      |
 *      |
 *  0   |         M
 *      |
 *      |
 * -1   | D               C
 *      |
 *      | _________________X
 *       -1      0       1
 *
 */
void Plane::setRotateCenterVec(Vec3 &a) {
    this->rotateCenterVec = a;
}

/**
 * Set the normal rotation to rotate the whole plane
 *
 * Example:
 *
 * a = (0,1,0)
 */
void Plane::setRotateVec(Vec3 &a) {
    this->rotate_vec = a;
}

/**
 * Set angle for rotation.
 *
 * Example:
 *
 * b = 90
 */
void Plane::setRotateAlpha(double &b) {
    this->rotate_alpha = b;
}

//Paint a line from the current center
void Plane::drawAxis() {

    Vec3 point = Vec3(0,0,0.5);
    Utils::drawAxis(point,1);


}

//Rotate the complete plane System
void Plane::drawRotation() {
    Vec3 transVec = Vec3(this->rotateCenterVec.p[0],this->rotateCenterVec.p[1],this->rotateCenterVec.p[2]) * (this->length);
    glTranslated(transVec.p[0], transVec.p[1], transVec.p[2]);
    glRotated(this->rotate_alpha, this->rotate_vec.p[0], this->rotate_vec.p[1], this->rotate_vec.p[2]);//Init Rotation
    transVec = transVec *-1;
    glTranslated(transVec.p[0], transVec.p[1], transVec.p[2]);
}

//Draw the whole plane element
void Plane::draw() {
    Vec3 A = Plane::getSide(Plane::POINTS::A)* this->length;
    Vec3 B = Plane::getSide(Plane::POINTS::B)* this->length;
    Vec3 C = Plane::getSide(Plane::POINTS::C)* this->length;
    Vec3 D = Plane::getSide(Plane::POINTS::D)* this->length;


    //Create new Matrix
    glPushMatrix();
    /**
     * Move the middle point so the system looks like
     *
     * M= middle and after translate coords (0,0,0)
     * A = (-1,1,0) B = ...
     *     y
     *  1   | A               B
     *      |
     *      |
     *      |
     *  0   |         M
     *      |
     *      |
     * -1   | D               C
     *      |
     *      | _________________X
     *       -1      0       1
     */
    glTranslated( this->middle.p[0]-this->length/2, this->middle.p[1]-this->length/2, this->middle.p[2]-this->length/2);
    glRotated(this->initAlpha, this->initRotationVector.p[0], this->initRotationVector.p[1], this->initRotationVector.p[2]);//Init Rotation


    //Rotate the system around a local point
    this->drawRotation();


    //Draw Axis for debug
    this->drawAxis();

    Vec3 normal = Vec3(0,0,1);
    //Begin to draw the plane
    glBegin(GL_QUADS);
    glEnable(GL_NORMALIZE);
    glNormal3dv(normal.p);
    glVertex3f(A.p[0],A.p[1],A.p[2]);
    glVertex3f(B.p[0],B.p[1],B.p[2]);
    glVertex3f(C.p[0],C.p[1],C.p[2]);
    glVertex3f(D.p[0],D.p[1],D.p[2]);
    glEnd();

    //Set global coords to the props of the panel
    //Important: Do this inside the push/pop matrix
    this->updateGlobalCoords(A,B,C,D);

    glPopMatrix();
}

/**
 * Update the props on the class to the new global coords.
 * Helpful for object collision
 */
void Plane::updateGlobalCoords(Vec3 &A,Vec3 &B,Vec3 &C,Vec3 &D ) {

    Utils::setGlobalCoords(A,this->globalA);
    Utils::setGlobalCoords(B,this->globalB);
    Utils::setGlobalCoords(C,this->globalC);
    Utils::setGlobalCoords(D,this->globalD);
}
/**
 * Get Globak A
 */
Vec3 Plane::getA(){
    return Plane::getSide(Plane::POINTS::A)* this->length;
}

/**
 * Get Globak B
 */
Vec3 Plane::getB(){
    return Plane::getSide(Plane::POINTS::B)* this->length;
}

/**
 * Get Globak C
 */
Vec3 Plane::getC(){
    return Plane::getSide(Plane::POINTS::C)* this->length;
}

/**
 * Get Globak D
 */
Vec3 Plane::getD(){
    return Plane::getSide(Plane::POINTS::D)* this->length;
}