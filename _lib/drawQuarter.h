//
// Created by Stefan B. on 11.04.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_GLQUARTER_H
#define GLFW3_DEMO_WITH_CMAKE_GLQUARTER_H


#include "vec3.hpp"

class DrawQuarter {

public:
    static void drawQuarter(Vec3& middlePoint, double &l);
    static void drawPlane(Vec3 &A, Vec3 &B, Vec3 &C,Vec3 &D);

};


#endif //GLFW3_DEMO_WITH_CMAKE_GLQUARTER_H
