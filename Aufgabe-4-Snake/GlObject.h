//
// Created by Stefan B. on 09.06.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_OBJECT_H
#define GLFW3_DEMO_WITH_CMAKE_OBJECT_H


#include "../_lib/vec3.hpp"
#include "Point.h"

class GlObject {
    public:
        GlObject(Point *origin);
        virtual void draw();
        void setRotation(double angle, Vec3 vec);
        void setRotation(double angle, int x, int y, int z);
        Point * getOriginPoint();
        void setTranslationVec(Vec3 vec);
        void setTranslationVec(int x, int y, int z);
    protected:
        Point* originPoint;
        Vec3 * rotationVec;
        Vec3 * translationVec;
        double * angle;
};


#endif //GLFW3_DEMO_WITH_CMAKE_OBJECT_H
