//
// Created by Stefan B. on 16.06.15.
//

#include "SnakeHead.h"
#include <iostream>
SnakeHead::SnakeHead(double l, Point *origin)
        :GlObject(origin){

        std::cout << l << std::endl;
        this->originPoint = origin;

        Point* top = new Point(this->originPoint, 0,0,l/2.0);
        Point* bottom = new Point(this->originPoint, 0,0,-l/2.0);
        Point* left = new Point(this->originPoint, -l/2.0,0,0);

        this->top = new Triangle(l, top);
        this->bottom = new Triangle(l, bottom);
        this->side_a = new Rectangle(l,l, left);
        //
  //      this->top->setDefaultRotation(M_PI*0.25,0,0,1);
    //    this->bottom->setDefaultRotation(M_PI*0.25,0,0,1);



}
void SnakeHead::draw() {
    GlObject::draw();
    this->top->draw();
    this->bottom->draw();

}