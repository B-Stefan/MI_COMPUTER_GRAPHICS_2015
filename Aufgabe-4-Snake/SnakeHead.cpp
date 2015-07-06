//
// Created by Stefan B. on 16.06.15.
//

#include "SnakeHead.h"
#include "SnakeHeadObject.h"
#include <iostream>
SnakeHead::SnakeHead(double l,double * velocity,Sphere * apple,  Point *origin)
        :SnakePart(l,origin){
    this->trackPositions = new std::deque<Vec3>();
    this->velocity = velocity;
    this->saveValuesToTrack();
    this->apple = apple;
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
void SnakeHead::applyOpenPercent() {
    Point * front = new Point(this->drawObject->getOriginPoint(),-1,0,0);
    Point * middle = this->drawObject->getOriginPoint();

    double distanceToFront = this->apple->getDistance(front->getPosition());
    double distanceToMiddle = this->apple->getDistance(middle->getPosition());

    //move to the apple
    SnakeHeadObject * headObject = dynamic_cast<SnakeHeadObject*>(this->drawObject);
    if(distanceToFront < distanceToMiddle){
        if(distanceToFront < 2){
            double totalPercent = 1/(2-distanceToFront);
            double oldPercent = headObject->getOpenPercent();
            double newPercent = 0;

            newPercent = oldPercent+0.1 * totalPercent;
            headObject->setOpenPercent(newPercent);
        }
        else {
            headObject->setOpenPercent(0);
        }
    }else {
        headObject->setOpenPercent(0);
    }

    //std::cout << "distanceToMiddle" << distanceToMiddle << std::endl;
}
void SnakeHead::draw() {
    SnakePart::draw();
    this->applyOpenPercent();
    * this->deltaBetweenParts  = exp(*this->velocity)+120/(*this->velocity*100);
    this->innerTranslationVec->p[0] = *this->velocity * -1;
    this->saveValuesToTrack();

}