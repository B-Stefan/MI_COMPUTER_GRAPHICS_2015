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
Cuboid::Cuboid(double height, double width, Point *origin)
        :GlObject(origin){

    double h = height;
    double w = width;

    Point* top    = new Point(this->originPoint,   h/2.0   ,0      ,0);
    Point* bottom = new Point(this->originPoint,   -h/2.0  ,0      ,0);
    Point* side_a = new Point(this->originPoint,   0       ,0      ,-w/2.0);
    Point* side_b = new Point(this->originPoint,   0       ,-w/2.0  ,0);
    Point* side_c = new Point(this->originPoint,   0       ,0      ,w/2.0);
    Point* side_d = new Point(this->originPoint,   0       ,w/2.0  ,0);

    this->top = new Rectangle(w,w,top);
    this->bottom = new Rectangle(w,w,bottom);

    this->side_a = new Rectangle(w,h,side_a);
    this->side_b = new Rectangle(w,h,side_b);
    this->side_c = new Rectangle(w,h,side_c);
    this->side_d = new Rectangle(w,h,side_d);

    double defaultAngle = M_PI *0.5;
    this->top->setRotation(defaultAngle , 0, -1, 0);
    this->bottom->setRotation(defaultAngle , 0, 1, 0);
    this->side_b->setRotation(defaultAngle , -1, 0, 0);
    this->side_d->setRotation(defaultAngle , 1, 0, 0);

    this->top->setMaterialColor(GlObject::MATERIAL_SIDES::FRONT,this->material_front);
    this->top->setMaterialColor(GlObject::MATERIAL_SIDES::BACK,this->material_back);


    this->bottom->setMaterialColor(GlObject::MATERIAL_SIDES::FRONT,this->material_front);
    this->bottom->setMaterialColor(GlObject::MATERIAL_SIDES::BACK,this->material_back);


    this->side_b->setMaterialColor(GlObject::MATERIAL_SIDES::FRONT,this->material_front);
    this->side_b->setMaterialColor(GlObject::MATERIAL_SIDES::BACK,this->material_back);

    this->side_d->setMaterialColor(GlObject::MATERIAL_SIDES::FRONT,this->material_front);
    this->side_d->setMaterialColor(GlObject::MATERIAL_SIDES::BACK,this->material_back);


}
bool Cuboid::colidate(Vec3 *position) {
    if(this->side_a->colidate(position)){
        return true;
    }
    if(this->side_b->colidate(position)){
        return true;
    }
    if(this->side_c->colidate(position)){
        return true;
    }
    if(this->side_d->colidate(position)){
        return true;
    }
}
void Cuboid::draw() {
    GlObject::draw();

    Utils::drawPoint(this->originPoint,4);



    this->top->draw();
    this->bottom->draw();
    this->side_a->draw();
    this->side_b->draw();
    this->side_c->draw();
    this->side_d->draw();

}