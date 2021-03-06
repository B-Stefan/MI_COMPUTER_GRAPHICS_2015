//
// Created by Stefan B. on 16.06.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_SNAKEPART_H
#define GLFW3_DEMO_WITH_CMAKE_SNAKEPART_H

#include <deque>
#include "GlObject.h"
#include "Point.h"
#include "Cuboid.h"
class SnakePart : public GlObject{
public:
    SnakePart(double l,int index,std::deque<Vec3> * track,std::deque<double> * trackRot,int * deltaBetweenParts, SnakePart *origin);
    SnakePart(double l,SnakePart *origin);
    SnakePart(double l,Point *origin);
    SnakePart* addPart();
    void draw();
    double getPartLength();
    bool colidate(Vec3 * vec);
    double* getAngle();
    void setRotation(double angle, int x, int y, int z);
    void setRotation(double angle, Vec3 vec);
    Point * getOriginPoint();
    std::deque<Vec3> * getTrack();

protected:
    Vec3 getPositionFromTrack();
    double getRotationFromTrack();
    double part_length;
    int * deltaBetweenParts;
    SnakePart *beforeNode;
    SnakePart *nextNode;
    std::deque<Vec3> *trackPositions;
    std::deque<double> *trackRotations;
    Vec3 *innerTranslationVec;
    Point* globalOrigin;
    GlObject *drawObject;
    int index;

private:
    void recalculateRotationValues();
    void recalculateTranslationValues();
    void applyValues(double l);
    bool isTrackReadyToDraw();
};


#endif //GLFW3_DEMO_WITH_CMAKE_SNAKEPART_H
