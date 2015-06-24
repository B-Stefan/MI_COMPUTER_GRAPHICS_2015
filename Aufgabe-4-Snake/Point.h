//
// Created by Stefan B. on 09.06.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_POINT_H
#define GLFW3_DEMO_WITH_CMAKE_POINT_H


#include <iosfwd>
#include <string>
#include "../_lib/vec3.hpp"

class Point {
    public:
        Point(Vec3 *origin,std::string name);
        Point(Vec3 *origin);
        Point(Point *origin);
        Point(Point *origin, double x, double y, double z);
        void setDefaultRotation(double *angle, Vec3 *a);
        Vec3* getPosition();
        Vec3* getNormal();
        void setName(std::string name);
        std::string getName();
        void setDynamicTranslationVec(Vec3 *vec);
        void recalculatePosition();
        void setDynamicRotate(double *angle, Vec3 *rotationVec, Vec3 *rotationOrigin);
    private:
        void recalculateNormalVector();
        void applyRotations();
        void applyRotate(double *angle, Vec3 *rotationVec, Vec3 *rotationOrigin, Vec3* resultVec);
        void applyDefaults();
        void applyTranslations();
        Vec3* originVec;
        Point* originPoint;
        Vec3 calculatedPosition;
        Vec3 calculatedNormalVector;


        Vec3        defaultTranslateVec;
        Vec3*       defaultRotationVec;
        double*     defaultRotationAngle;


        Vec3*       dynamicTranslateVec;
        Vec3*       dynamicRotationVec;
        double*     dynamicRotationAngle;
        Vec3*       dynamicRotationOrigin;
        std::string name;
};


#endif //GLFW3_DEMO_WITH_CMAKE_POINT_H
