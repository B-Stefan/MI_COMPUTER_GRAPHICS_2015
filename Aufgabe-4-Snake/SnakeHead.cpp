//
// Created by Stefan B. on 16.06.15.
//

#include "SnakeHead.h"
#include "SnakeHeadObject.h"
#include <iostream>
SnakeHead::SnakeHead(double l,double * velocity, Point *origin)
        :SnakePart(l,origin){
    this->trackPositions = new std::deque<Vec3>();
    this->velocity = velocity;
    this->saveValuesToTrack();
    Point * headRotationX = new Point(this->originPoint);
    Point * headRotationY = new Point(headRotationX);


    this->drawObject = new SnakeHeadObject(this->part_length/2, this->part_length,headRotationY);
    this->drawObject->getOriginPoint()->setTranslationVec(this->innerTranslationVec);
}
void SnakeHead::saveValuesToTrack() {
    Vec3 *globalOrigin = this->globalOrigin->getPosition();
    Vec3 vecToLastPosFromGlobalOrigin = *this->drawObject->getOriginPoint()->getPosition()- *globalOrigin;
    this->trackPositions->push_front(vecToLastPosFromGlobalOrigin);
    this->trackRotations->push_front(*this->getAngle());
}
void SnakeHead::draw() {
    SnakePart::draw();
    * this->deltaBetweenParts  = exp(*this->velocity)+120/(*this->velocity*100);
    this->innerTranslationVec->p[0] = *this->velocity * -1;
    this->saveValuesToTrack();

}