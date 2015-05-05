//
// Created by Stefan B. on 11.04.15.
//
#include <GLFW/glfw3.h>
#include "Quarter.h"
#include "utils.h"
#include "Plane.h"
#include "vec3.hpp"
#include <stdio.h>
#include <iostream>
#include <cmath>

/**
 * Class for draw a simple quater
 *
 * middlePoint = (0,0,0) Point for the position of the quarter
 * l = 2 edge length
 */

/**
 *
 1   | A       R       B
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
Quarter::Quarter(Vec3 &middlePoint, double &l){
    this->middlePoint = middlePoint;
    this->openPercentage = 0;
    this->middlePointSphere = Vec3(this->middlePoint);
    this->translate_vec_sphere = Vec3(0,0,0);

    Vec3 Left   =   this->middlePoint +  l * Vec3(-1,0,0);
    Vec3 Right  =   this->middlePoint +  l * Vec3(1,0,0);
    Vec3 Front  =   this->middlePoint +  l * Vec3(0,1,0);
    Vec3 Back   =   this->middlePoint +  l * Vec3(0,-1,0);
    Vec3 Top    =   this->middlePoint +  l * Vec3(0,0,1);
    Vec3 Bottom =   this->middlePoint +  l * Vec3(0,0,-1);

    //Create all needed planes
    this->top       = new Plane(Top,l);
    this->bottom    = new Plane(Bottom,l);
    this->left      = new Plane(Left,l);
    this->right     = new Plane(Right,l);
    this->back      = new Plane(Back,l);
    this->front     = new Plane(Front,l);
    this->sphere    = new Sphere(this->middlePoint,l);


    //Rotate the planes in right position for lighting
    this->top->setInitRotation(0,Vec3(1,0,0));
    this->bottom->setInitRotation(180,Vec3(1,0,0));
    this->left->setInitRotation(-90,Vec3(0,1,0));
    this->right->setInitRotation(90,Vec3(0,1,0));
    this->back->setInitRotation(90,Vec3(1,0,0));
    this->front->setInitRotation(-90,Vec3(1,0,0));

    //Set up cover side

    //Set rotation to y-axis
    Vec3 rotateVec = Vec3(0,1,0);

    //Set Center Position to this:
    /*
     *
     *      y
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
     */
    Vec3 rotateVecCenter = Vec3(1,0,0);


    //Set angle
    double alpha = 0;

    //Apply vars to panel
    //If you change the alpha value the panel use your new value
    this->top->setRotateCenterVec(rotateVecCenter);
    this->top->setRotateVec(rotateVec);
    this->top->setRotateAlpha(alpha);
};
void Quarter::setTranslateSphere(Vec3 v) {
    this->translate_vec_sphere = v;
}
void Quarter::setOpenPercentage(double a){
    this->openPercentage = a;
}
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

bool Quarter::checkCollision(Plane p) {

    Vec3 A = p.getA();
    Vec3 B = p.getB();
    Vec3 C = p.getC();
    Vec3 D = p.getD();
    std::cout << "A:" << A.p[0] << std::endl;
    std::cout << "B:" << B.p[0] << std::endl;
    std::cout << "C:" << C.p[0] << std::endl;
    std::cout << "D:" << D.p[0] << std::endl;
    bool checkX = false;
    bool checkY = false;
    bool checkZ = false;

    //Top and down
    int distanceTop   = std::abs(this->sphere->getMiddle().p[1] - A.p[1]);
    int distanceDown  = std::abs(this->sphere->getMiddle().p[1] - D.p[1]);

    //Left and right
    int distanceRight = std::abs(this->sphere->getMiddle().p[0] - B.p[1]);
    int distanceLeft  = std::abs(this->sphere->getMiddle().p[0] - D.p[1]);

    std::cout << "R:" << this->sphere->getR() << std::endl;
    std::cout << "distanceTop:" << distanceTop << std::endl;
    std::cout << "distanceDown:" << distanceDown << std::endl;
    std::cout << "distanceRight:" << distanceRight << std::endl;
    std::cout << "distanceLeft:" << distanceLeft << std::endl;
    //y check
    if(distanceDown <= this->sphere->getR() ||  distanceTop <= this->sphere->getR()){
        checkX = true;
    }
    //check x
    if(distanceRight <= this->sphere->getR()|| distanceLeft <= this->sphere->getR()){
        checkY = true;
    }
    return  checkY && checkX;



}
void Quarter::draw() {

    /*
    / Move sphere
    */
    this->sphere->setMiddle(this->translate_vec_sphere);

    glPushMatrix();
    glTranslated( this->translate_vec.p[0], this->translate_vec.p[1], this->translate_vec.p[2]);
    glRotated(this->rotate_alpha, this->rotate_vec.p[0], this->rotate_vec.p[1], this->rotate_vec.p[2]);
    glScalef(this->scale, this->scale, this->scale);


    double alpha = 269.0 / 100.0 * this->openPercentage ;
    this->top->setRotateAlpha(alpha);


    std::cout << "this->middlePointSphere: " << this->middlePointSphere.p[0] << std::endl;
    std::cout << "this->this->translate_vec_sphere: " << this->translate_vec_sphere.p[0] << std::endl;
    Utils::drawAxis(this->translate_vec_sphere,1);
    this->sphere->draw();
    this->top->draw();
    //this->bottom->draw();
    //this->left->draw();
    //this->right->draw();
    //this->back->draw();
    this->front->draw();

    if(this->checkCollision(*this->top)){
        std::cout<< "yeeeeeeah "<< std::endl;
    };
    glPopMatrix();
}
