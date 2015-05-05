//
// Created by Stefan B. on 04.05.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_UTILS_H
#define GLFW3_DEMO_WITH_CMAKE_UTILS_H

#include  "vec3.hpp"

class Utils {

public:
    static void setGlobalCoords(Vec3 &local, Vec3 &global);
    static void drawAxis(Vec3 &point, double length);
};
#endif //GLFW3_DEMO_WITH_CMAKE_UTILS_H
