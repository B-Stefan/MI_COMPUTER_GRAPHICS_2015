//
// Created by Stefan B. on 11.04.15.
//
#include <GLFW/glfw3.h>
#include "Quarter.h"
#include "Plane.h"
#include "vec3.hpp"

Quarter::Quarter(Vec3 &middlePoint, double &l){
    this->middlePoint = middlePoint;

    Vec3 Left   =   this->middlePoint +  l * Vec3(-1,0,0);
    Vec3 Right  =   this->middlePoint +  l * Vec3(1,0,0);
    Vec3 Front  =   this->middlePoint +  l * Vec3(0,1,0);
    Vec3 Back   =   this->middlePoint +  l * Vec3(0,-1,0);
    Vec3 Top    =   this->middlePoint +  l * Vec3(0,0,1);
    Vec3 Bottom =   this->middlePoint +  l * Vec3(0,0,-1);

    //Create new planes
    this->top       = new Plane(Top,l);
    this->bottom    = new Plane(Bottom,l);
    this->left      = new Plane(Left,l);
    this->right     = new Plane(Right,l);
    this->back      = new Plane(Back,l);
    this->front     = new Plane(Front,l);


    //Rotate the planes in right position
    this->top->setInitRotation(0,Vec3(1,0,0));
    this->bottom->setInitRotation(180,Vec3(1,0,0));
    this->left->setInitRotation(-90,Vec3(0,1,0));
    this->right->setInitRotation(90,Vec3(0,1,0));
    this->back->setInitRotation(90,Vec3(1,0,0));
    this->front->setInitRotation(-90,Vec3(1,0,0));

    //Set up cover side
    Vec3 rotateVec = Vec3(0,1,0);
    Vec3 rotateVecCenter = Plane::getSide(Plane::POINTS::A) - Plane::getSide(Plane::POINTS::B);
    double alpha = 30.40;
    this->top->setRotateCenterVec(rotateVecCenter);
    this->top->setRotateVec(rotateVec);
    this->top->setRotateAlpha(alpha);
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
void Quarter::drawNormals() {
}
void Quarter::drawNormal(Vec3 &A, Vec3 &B, Vec3 &C, Vec3 &D) {
    glEnable(GL_NORMALIZE);
    Vec3 normal = ((A % B) % (C % D));
    glBegin(GL_LINES);
    glNormal3f(normal.p[0],normal.p[1],normal.p[2]);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(this->middlePoint.p[0], this->middlePoint.p[1], this->middlePoint.p[2]);
    glVertex3f(this->middlePoint.p[0]+normal.p[0], this->middlePoint.p[1]+normal.p[1], this->middlePoint.p[2]+normal.p[2]);
    glEnd();          // Start Drawing A Triangle
}
void Quarter::draw() {
    glPushMatrix();
    glTranslated( this->translate_vec.p[0], this->translate_vec.p[1], this->translate_vec.p[2]);
    glRotated(this->rotate_alpha, this->rotate_vec.p[0], this->rotate_vec.p[1], this->rotate_vec.p[2]);
    glScalef(this->scale, this->scale, this->scale);

    this->top->draw();
    this->bottom->draw();
    this->left->draw();
    this->right->draw();
    this->back->draw();
    this->front->draw();

    glPopMatrix();
}
