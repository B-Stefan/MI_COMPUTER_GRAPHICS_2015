//
// Created by Stefan B. on 11.04.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_GLQUARTER_H
#define GLFW3_DEMO_WITH_CMAKE_GLQUARTER_H


#include "vec3.hpp"
#import "Plane.h"
#include "SphereOld.h"

class Quarter {

public:
    Quarter(Vec3 &middlePoint, double &l);
    void draw();
    void drawNormals();
    void setRotateAlpha(double  &a);
    void setRotateVec(Vec3  &a);
    void setScale(double  &s);
    void setTranslateVec(Vec3  &a);
    void setOpenPercentage(double a);
    void setTranslateSphere(Vec3 v);

private:
    void drawNormal(Vec3 &A,Vec3 &B, Vec3 &C, Vec3 &D);

    bool checkCollision(Plane p);
    Vec3 middlePoint;
    Vec3 middlePointSphere;
    double openPercentage;
    Plane *left;
    Plane *right;
    Plane *front;
    Plane *top;
    Plane *bottom;
    Plane *back;
    SphereOld *sphere;
    double scale;
    double rotate_alpha;
    Vec3 rotate_vec;
    Vec3 translate_vec;
    Vec3 translate_vec_sphere;
};



#endif //GLFW3_DEMO_WITH_CMAKE_GLQUARTER_H
