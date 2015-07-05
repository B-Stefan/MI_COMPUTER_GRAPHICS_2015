//
// Created by Stefan B. on 02.07.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_TRIANGLE_CUBOID_H
#define GLFW3_DEMO_WITH_CMAKE_TRIANGLE_CUBOID_H


#include "GlObject.h"
#include "Rectangle.h"

class TriangleCuboid :public GlObject {
private:

    Point * topArea;
    Point * bottomArea;

    Point * pointA;
    Point * pointB;
    Point * pointC;

    Point * pointA_bottom;
    Point * pointB_bottom;
    Point * pointC_bottom;
public:
    TriangleCuboid(double widht, double height, Point *origin);
    void draw();
    bool colidate(Vec3 * point);
};


#endif //GLFW3_DEMO_WITH_CMAKE_TRIANGLE_CUBOID_H
