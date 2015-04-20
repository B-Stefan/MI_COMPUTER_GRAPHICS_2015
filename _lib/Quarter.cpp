//
// Created by Stefan B. on 11.04.15.
//
#include <GLFW/glfw3.h>
#include "Quarter.h"
#include "vec3.hpp"


void Quarter::drawPlane(Vec3 &A, Vec3 &B, Vec3 &C,Vec3 &D) {

    glEnable(GL_NORMALIZE);
    Vec3 normal = ((A % B) % (C % D));

    glBegin(GL_LINES);
    glNormal3f(normal.p[0],normal.p[1],normal.p[2]);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(A.p[0], A.p[1], A.p[2]);
    glVertex3f(A.p[0]+normal.p[0], A.p[1]+normal.p[1], A.p[2]+normal.p[2]);
    glEnd();          // Start Drawing A Triangle




    glBegin(GL_QUADS);
    glNormal3dv(normal.p);
    glVertex3f(A.p[0],A.p[1],A.p[2]);
    glVertex3f(B.p[0],B.p[1],B.p[2]);
    glVertex3f(C.p[0],C.p[1],C.p[2]);
    glVertex3f(D.p[0],D.p[1],D.p[2]);
    glEnd();
}
 Quarter::Quarter(Vec3& middlePoint, double &l){

    Vec3 pointTopLeftCorner = Vec3(middlePoint.p[0]-l/2,
                                   middlePoint.p[1]+l/2,
                                   middlePoint.p[2]-l/2);

    //Front Plane
    Vec3 A = l * Vec3(0,0,0)  + pointTopLeftCorner;
    Vec3 B = l * Vec3(1,0,0)  + pointTopLeftCorner;
    Vec3 C = l * Vec3(1,-1,0) + pointTopLeftCorner;
    Vec3 D = l * Vec3(0,-1,0) + pointTopLeftCorner;

    //Back Plane
    Vec3 T = Vec3(0,0,l);
    Vec3 A_BACK =   A +T;
    Vec3 B_BACK =   B +T;
    Vec3 C_BACK =   C +T;
    Vec3 D_BACK =   D +T;


    this->front_A = A;
    this->front_B = B;
    this->front_C = C;
    this->front_D = D;

    this->back_A = A_BACK;
    this->back_B = B_BACK;
    this->back_C = C_BACK;
    this->back_D = D_BACK;


    this->left_A = A;
    this->left_B = A_BACK;
    this->left_C = D_BACK;
    this->left_D = D;

    this->right_A = B;
    this->right_B = B_BACK;
    this->right_C = C_BACK;
    this->right_D = C;


    this->top_A = A;
    this->top_B = A_BACK;
    this->top_C = B_BACK;
    this->top_D = B;

    this->bottom_A = D;
    this->bottom_B = D_BACK;
    this->bottom_C = C_BACK;
    this->bottom_D = C;

};
void Quarter::setRotateAlpha(double &a) {
    this->rotate_alpha = a;
}
void Quarter::setRotateVec(Vec3 &a) {
    this->rotate_vec = a;
}
void Quarter::setScale(double &s) {
    this->scale = s;
}
void Quarter::setTranslateVec(Vec3 &a) {
    this->translate_vec  = a;
}
void Quarter::draw() {
    glPushMatrix();

    glTranslated( this->translate_vec.p[0], this->translate_vec.p[1], this->translate_vec.p[2]);
    glRotated(this->rotate_alpha, this->rotate_vec.p[0], this->rotate_vec.p[1], this->rotate_vec.p[2]);
    glScalef(this->scale, this->scale, this->scale);

    Quarter::drawPlane(this->front_A,this->front_B,this->front_C,this->front_D); //FRONT
    Quarter::drawPlane(this->back_A,this->back_B,this->back_C,this->back_D); //back
    Quarter::drawPlane(this->left_A,this->left_B,this->left_C,this->left_D);//left
    Quarter::drawPlane(this->top_A,this->top_B,this->top_C,this->top_D);//TOP
    Quarter::drawPlane(this->right_A,this->right_B,this->right_C,this->right_D);//right
    Quarter::drawPlane(this->bottom_A,this->bottom_B,this->bottom_C,this->bottom_D);//Bottom

    glPopMatrix();
}
