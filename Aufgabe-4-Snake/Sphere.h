//
// Created by Stefan B. on 30.06.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_SPHERE_H
#define GLFW3_DEMO_WITH_CMAKE_SPHERE_H

#include "GlObject.h"

class Sphere : public GlObject{

public:
    Sphere(double r, Point * origin);

    void draw();
    double getRadius();
    bool colidate(Vec3 * snakeHead);

private:
    double radius;
};


#endif //GLFW3_DEMO_WITH_CMAKE_SPHERE_H
