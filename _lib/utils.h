//
// Created by Stefan B. on 04.05.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_UTILS_H
#define GLFW3_DEMO_WITH_CMAKE_UTILS_H

#include  "vec3.hpp"
#include <iostream>
using  namespace std;
class Utils {

public:
    static void setGlobalCoords(Vec3 &local, Vec3 &global);
    static void logMatrix(double m[16]);
    static void drawAxis(Vec3 &point, double length);
    static void printVec3(Vec3 &point);
    static void printVec3(Vec3 &point, string desc);
};
#endif //GLFW3_DEMO_WITH_CMAKE_UTILS_H
