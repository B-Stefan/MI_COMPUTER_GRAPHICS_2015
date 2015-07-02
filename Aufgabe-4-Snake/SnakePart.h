//
// Created by Stefan B. on 16.06.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_SNAKEPART_H
#define GLFW3_DEMO_WITH_CMAKE_SNAKEPART_H

#include "GlObject.h"
#include "Point.h"
#include "Cuboid.h"
class SnakePart : public GlObject{
public:
    SnakePart(double l,SnakePart *origin);
    SnakePart(double l,Point *origin);
    SnakePart* addPart();
    SnakePart* getBeforeNode();
    Point* globalOrigin;
    void draw();
    double* getAngle();
    Vec3 getOldAbsolutPosition();
    Vec3 getPositionForNewPart();
    void setVelocity(double d);
    double getVelocity();
    void setRotation(double angle, int x, int y, int z);
    double getPartLength();
    Point * getOriginPoint();
    Point * getTranslationPoint();
private:
    Cuboid * cuboid;
    Vec3 * cuboidTranslationVec;
    void recalculateRotationValues();
    void recalculateTranslationValues();
    void applyValues(double l);
    void applyLastPosition();
    double part_length;
    SnakePart *beforeNode;
    SnakePart *nextNode;
    Vec3 * oldAbsolutPosition;
    Vec3 * oldAbsolutRotation;
    double velocity;
};


#endif //GLFW3_DEMO_WITH_CMAKE_SNAKEPART_H
