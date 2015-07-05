//
// Created by Stefan B. on 05.07.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_TRIANGLECUBOID_H
#define GLFW3_DEMO_WITH_CMAKE_TRIANGLECUBOID_H


#include "GlObject.h"
#include "Triangle.h"
#include "Rectangle.h"

class TriangleCuboid : public GlObject {
public:
    TriangleCuboid(double l, Point * origin);
    bool colidate(Vec3 * point);
    void draw();

private:
    double length;
    Rectangle* side_a ;
    Triangle* top ;
    Triangle* bottom ;
    Rectangle* side_c ;
};


#endif //GLFW3_DEMO_WITH_CMAKE_TRIANGLECUBOID_H
