//
// Created by Stefan B. on 16.06.15.
//

#include <iostream>
#include "Snake.h"
#include "Point.h"
#include "SnakePart.h"
#include "GlObject.h"
Snake::Snake(Point *origin)
        : GlObject::GlObject(origin) {

        this->firstPart = new SnakePart(1,origin);
        this->firstPart->addPart();
        this->firstPart->addPart();
        this->firstPart->addPart();
        this->firstPart->addPart();
        this->firstPart->addPart();
        this->firstPart->addPart();

}
bool Snake::collidateThemSelf() {
    Vec3 headPoint = this->getHeadPoint();
    return this->firstPart->collidate(&headPoint);
}
bool Snake::colidate(Vec3 * vec) {
    this->firstPart->collidate(vec);
}
void Snake::draw() {
        GlObject::draw();
        this->firstPart->setRotation(*this->angle, 0,1,0);
        this->firstPart->draw();
}
/**
 * Return the first point of the snake based on the current move direction
 */
Vec3 Snake::getHeadPoint() {
        Point p = new Point(this->firstPart->getOriginPoint(),
                            this->firstPart->getPartLength()/2*-1 + 0.1
                           ,0,
                            0);

        return *p.getPosition();
}