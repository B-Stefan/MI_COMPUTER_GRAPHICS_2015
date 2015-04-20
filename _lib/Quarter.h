//
// Created by Stefan B. on 11.04.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_GLQUARTER_H
#define GLFW3_DEMO_WITH_CMAKE_GLQUARTER_H


#include "vec3.hpp"

class Quarter {

public:
    static void drawPlane(Vec3 &A, Vec3 &B, Vec3 &C,Vec3 &D);
    Quarter(Vec3& middlePoint, double &l);
    void draw();

private:
    Vec3 left_A;
    Vec3 left_B;
    Vec3 left_C;
    Vec3 left_D;

    Vec3 right_A;
    Vec3 right_B;
    Vec3 right_C;
    Vec3 right_D;

    Vec3 front_A;
    Vec3 front_B;
    Vec3 front_C;
    Vec3 front_D;


    Vec3 back_A;
    Vec3 back_B;
    Vec3 back_C;
    Vec3 back_D;


    Vec3 top_A;
    Vec3 top_B;
    Vec3 top_C;
    Vec3 top_D;

    Vec3 bottom_A;
    Vec3 bottom_B;
    Vec3 bottom_C;
    Vec3 bottom_D;
};



#endif //GLFW3_DEMO_WITH_CMAKE_GLQUARTER_H
