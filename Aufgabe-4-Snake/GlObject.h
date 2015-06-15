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

    protected:
        Point* originPoint;
};


#endif //GLFW3_DEMO_WITH_CMAKE_OBJECT_H
