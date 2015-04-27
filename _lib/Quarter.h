//
// Created by Stefan B. on 11.04.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_GLQUARTER_H
#define GLFW3_DEMO_WITH_CMAKE_GLQUARTER_H


#include "vec3.hpp"
#import "Plane.h"

class Quarter {

public:
    Quarter(Vec3 &middlePoint, double &l);
    void draw();
    void drawNormals();
    void setRotateAlpha(double  &a);
    void setRotateVec(Vec3  &a);
    void setScale(double  &s);
    void setTranslateVec(Vec3  &a);

private:
    void drawNormal(Vec3 &A,Vec3 &B, Vec3 &C, Vec3 &D);
    Vec3 middlePoint;
    Plane *left;
    Plane *right;
    Plane *front;
    Plane *top;
    Plane *bottom;
    Plane *back;
    double scale;
    double rotate_alpha;
    Vec3 rotate_vec;
    Vec3 translate_vec;
};



#endif //GLFW3_DEMO_WITH_CMAKE_GLQUARTER_H
