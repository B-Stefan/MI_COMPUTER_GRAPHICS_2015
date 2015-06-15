//
// Created by Stefan B. on 09.06.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_POINT_H
#define GLFW3_DEMO_WITH_CMAKE_POINT_H


#include "../_lib/vec3.hpp"

class Point {
    public:
        Point(Vec3 *origin);
        Point(Point *origin);
        Point(Point *origin, double x, double y, double z);
        void setDefaultRotation(double *angle, Vec3 *a);
        Vec3* getPosition();
        void recalculatePosition();
        void setDynamicRotate(double *angle, Vec3 *rotationVec, Vec3 *rotationOrigin);
    private:
        void applyRotate(double *angle, Vec3 *rotationVec, Vec3 *rotationOrigin);
        void applyDefaults();
        Vec3* originVec;
        Vec3 calculatedPosition;


        Vec3        defaultTranslateVec;
        Vec3*       defaultRotationVec;
        double*     defaultRotationAngle;


        Vec3        dynamicTranslateVec;
        Vec3*       dynamicRotationVec;
        double*     dynamicRotationAngle;
        Vec3*       dynamicRotationOrigin;
};


#endif //GLFW3_DEMO_WITH_CMAKE_POINT_H
