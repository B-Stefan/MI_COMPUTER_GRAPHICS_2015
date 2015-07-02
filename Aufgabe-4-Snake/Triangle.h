//
// Created by Stefan B. on 02.07.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_TRIANGLE_H
#define GLFW3_DEMO_WITH_CMAKE_TRIANGLE_H


#include "GlObject.h"
#include "Rectangle.h"

class Triangle :GlObject {
private:
    Point * pointA;
    Point * pointB;
    Point * pointC;
public:
    Triangle(double l, Point *origin);
    void draw();
};


#endif //GLFW3_DEMO_WITH_CMAKE_TRIANGLE_H
