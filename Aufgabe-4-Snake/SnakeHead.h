//
// Created by Stefan B. on 16.06.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_SNAKEHEAD_H
#define GLFW3_DEMO_WITH_CMAKE_SNAKEHEAD_H


#import "GlObject.h"
#import "Triangle.h"
#import "Rectangle.h"
class SnakeHead : public GlObject{
public:
    SnakeHead(double l,Point *origin);
    void draw();
private:
    Triangle* top;
    Rectangle* side_a ;
    Rectangle* side_b ;
    Rectangle* side_c ;
    Triangle* bottom ;
};


#endif //GLFW3_DEMO_WITH_CMAKE_SNAKEHEAD_H
