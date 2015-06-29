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
        static int currentLoopNumber;
        Point(Vec3 *origin,std::string name);
        Point(Vec3 *origin);
        Point(Point *origin);
        Point(Point *origin, double x, double y, double z);
        Vec3* getPosition();
        Vec3* getNormal();
        void setName(std::string name);
        std::string getName();
        void setTranslationVec(Vec3 *vec);
        void recalculatePosition();
        void recalculatePosition(bool force);
        double * getAngle();
        Vec3 * getRotationVec();
        void setRotate(double *angle, Vec3 *rotationVec);
    private:
        int  loopNumber = 0;
        void recalculateNormalVector();
        void applyRotations();
        void applyDefaults();
        void applyTranslations();
        Vec3* originVec;
        Point* originPoint;
        Vec3 calculatedPosition;
        Vec3 calculatedNormalVector;

        Vec3*translateVec;
        Vec3*rotationVec;
        double*rotationAngle;


        std::string name;
};


#endif //GLFW3_DEMO_WITH_CMAKE_POINT_H
