//
// Created by Stefan B. on 16.06.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_SNAKEHEAD_H
#define GLFW3_DEMO_WITH_CMAKE_SNAKEHEAD_H


#import "GlObject.h"
#import "Rectangle.h"
#import "Sphere.h"
#import "TriangleCuboid.h"
#import "Rectangle.h"
#include "SnakePart.h"

class SnakeHead : public SnakePart{
public:
    SnakeHead(double l,double * velocity, Sphere * apple,  Point *origin);
    void draw();
    void  setVelocity(double v);
private:
    void applyOpenPercent();
    double * velocity;
    Sphere * apple;
    void saveValuesToTrack();
};


#endif //GLFW3_DEMO_WITH_CMAKE_SNAKEHEAD_H
