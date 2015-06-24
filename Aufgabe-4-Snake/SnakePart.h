//
// Created by Stefan B. on 16.06.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_SNAKEPART_H
#define GLFW3_DEMO_WITH_CMAKE_SNAKEPART_H

#include "GlObject.h"
#include "Point.h"
#include "Cuboid.h"
class SnakePart : public Cuboid{
public:
    SnakePart(double l,SnakePart *origin);
    SnakePart(double l,Point *origin);
    SnakePart* addPart();
    void dawNextLoop();
    SnakePart* getBeforeNode();
    void draw();
    Vec3* getRotationVec();
    double* getAngle();
private:
    void recalculateRotationValues();
    void applyValues(double l);
    double part_length;
    SnakePart *beforeNode;
    SnakePart *nextNode;
};


#endif //GLFW3_DEMO_WITH_CMAKE_SNAKEPART_H
