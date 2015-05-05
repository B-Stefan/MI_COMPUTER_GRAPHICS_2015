//
// Created by Stefan B. on 21.04.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_PLANE_H
#define GLFW3_DEMO_WITH_CMAKE_PLANE_H

#import "vec3.hpp"
#include <GLUT/glut.h>

class Plane {

    public:
        typedef enum {A,B,C,D} POINTS;
        static Vec3 getSide(POINTS point);

        Plane(Vec3 &middle, double l);
        void draw();
        void drawAxis();
        void drawRotation();
        void setRotateAlpha(double  &a);
        void setRotateVec(Vec3  &a);
        void setRotateCenterVec(Vec3 &a);
        void setTranslateVec(Vec3  &a);
        void setInitRotation(double alpha, Vec3  vector);
        Vec3 getA();
        Vec3 getB();
        Vec3 getC();
        Vec3 getD();
    private:
        void updateGlobalCoords(Vec3 &A,Vec3 &B,Vec3 &C,Vec3 &D);
        Vec3 middle;
        Vec3 globalA;
        Vec3 globalB;
        Vec3 globalC;
        Vec3 globalD;
        double length;
        double initAlpha;
        Vec3 initRotationVector;
        Vec3 rotate_vec;
        Vec3 rotateCenterVec;
        double rotate_alpha;
        Vec3 translate_vec;
};


#endif //GLFW3_DEMO_WITH_CMAKE_PLANE_H
