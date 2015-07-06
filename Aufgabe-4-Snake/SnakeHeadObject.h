//
// Created by Stefan B. on 05.07.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_SnakeHeadObject_H
#define GLFW3_DEMO_WITH_CMAKE_SnakeHeadObject_H


#include "GlObject.h"
#include "TriangleCuboid.h"
#include "Cuboid.h"

class SnakeHeadObject : public GlObject {
public:
    SnakeHeadObject(double width,double  height, Point * origin);
    bool colidate(Vec3 * point);
    void draw();
    void setOpenPercent(double percent);
    double  getOpenPercent();

private:
    double openPercent;
    Point * rotationPointForTop;
    TriangleCuboid* top ;
    TriangleCuboid* bottom ;
};


#endif //GLFW3_DEMO_WITH_CMAKE_SnakeHeadObject_H
