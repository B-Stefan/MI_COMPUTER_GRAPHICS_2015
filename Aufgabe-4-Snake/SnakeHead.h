//
// Created by Stefan B. on 16.06.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_SNAKEHEAD_H
#define GLFW3_DEMO_WITH_CMAKE_SNAKEHEAD_H


#import "GlObject.h"
#import "Rectangle.h"
#import "Triangle.h"
#import "Rectangle.h"
#include "SnakePart.h"

class SnakeHead : public SnakePart{
public:
    SnakeHead(double l,Point *origin);
    void draw();
    void  setVelocity(double v);
private:
    double velocity;
    void saveValuesToTrack();
    Rectangle* side_a ;
    Triangle* top ;
    Triangle* bottom ;
    Rectangle* side_c ;
};


#endif //GLFW3_DEMO_WITH_CMAKE_SNAKEHEAD_H
