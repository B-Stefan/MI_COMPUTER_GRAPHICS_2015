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
        void setRotation(double * angle, Vec3 *vec);

    protected:
        Point* originPoint;
        Vec3 * rotationVec;
        double * angle;
};


#endif //GLFW3_DEMO_WITH_CMAKE_OBJECT_H
