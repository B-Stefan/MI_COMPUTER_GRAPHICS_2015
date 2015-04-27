//
// Created by Stefan B. on 21.04.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_PLANE_H
#define GLFW3_DEMO_WITH_CMAKE_PLANE_H

#import "vec3.hpp"

class Plane {

    public:
        typedef enum {A,B,C,D} POINTS;
        static Vec3 getSide(POINTS point);

        Plane(Vec3 &middle, double l);
        void draw();
        void drawNormal(Vec3 normal);
        void drawRotation();
        void setRotateAlpha(double  &a);
        void setRotateVec(Vec3  &a);
        void setRotateCenterVec(Vec3  &a);
        void setTranslateVec(Vec3  &a);
        void setInitRotation(double alpha, Vec3  vector);
    private:

        Vec3 middle;
        double length;
        double initAlpha;
        Vec3 initRotationVector;
        Vec3 rotate_vec;
        Vec3 rotateCenterVec;
        double rotate_alpha;
        Vec3 translate_vec;
};


#endif //GLFW3_DEMO_WITH_CMAKE_PLANE_H
