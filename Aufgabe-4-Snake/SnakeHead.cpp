//
// Created by Stefan B. on 16.06.15.
//

#include "SnakeHead.h"
#include "SnakeHeadObject.h"
#include <iostream>
SnakeHead::SnakeHead(double l, Point *origin)
        :SnakePart(l,origin){
    this->trackPositions = new std::deque<Vec3>();
    this->velocity = 0.01;
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
    this->innerTranslationVec->p[0] = this->velocity * -1;
    this->saveValuesToTrack();

}