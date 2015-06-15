//
// Created by Stefan B. on 09.06.15.
//

#include "Cuboid.h"
#include "Rectangle.h"
#include "./../_lib/utils.h"
#include "GlObject.h"
#include <iostream>
#include <GLFW/glfw3.h>
using namespace std;
double angle = M_PI*0.5;
Vec3* rotateVec = new Vec3(0,1,0);
Cuboid::Cuboid(double height, double width, Point *origin)
        :GlObject(origin){

    double h = height;
    double w = width;

    Point* top    = new Point(origin,   h/2.0   ,0      ,0);
    Point* bottom = new Point(origin,   -h/2.0  ,0      ,0);
    Point* side_a = new Point(origin,   0       ,0      ,-w/2.0);
    Point* side_b = new Point(origin,   0       ,-w/2.0  ,0);
    Point* side_c = new Point(origin,   0       ,0      ,w/2.0);
    Point* side_d = new Point(origin,   0       ,w/2.0  ,0);

    this->top = new Rectangle(w,w,top);
    this->bottom = new Rectangle(w,w,bottom);

    this->side_a = new Rectangle(w,h,side_a);
    this->side_b = new Rectangle(w,h,side_b);
    this->side_c = new Rectangle(w,h,side_c);
    this->side_d = new Rectangle(w,h,side_d);

    this->top->setDefaultRotation(angle, 0, -1, 0);
    this->bottom->setDefaultRotation(angle, 0, 1, 0);
    this->side_b->setDefaultRotation(angle, -1, 0, 0);
    this->side_d->setDefaultRotation(angle, 1, 0, 0);


}
void Cuboid::draw() {
    GlObject::draw();

    Utils::drawAxis(*this->originPoint->getPosition(),2);
    angle = angle + 0.01;

    this->top->rotate(&angle,    rotateVec ,this->originPoint);
    this->bottom->rotate(&angle, rotateVec,this->originPoint);
    this->side_a->rotate(&angle, rotateVec,this->originPoint);
    this->side_b->rotate(&angle, rotateVec,this->originPoint);
    this->side_c->rotate(&angle, rotateVec,this->originPoint);
    this->side_d->rotate(&angle, rotateVec,this->originPoint);


    this->top->draw();
    this->bottom->draw();
    this->side_a->draw();
    this->side_b->draw();
    this->side_c->draw();
    this->side_d->draw();

}