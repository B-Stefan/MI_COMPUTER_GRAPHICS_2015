//
// Created by Stefan B. on 16.06.15.
//

#include "Snake.h"
#include "Point.h"
#include "SnakePart.h"
#include "GlObject.h"
Snake::Snake(Point *origin)
        : GlObject::GlObject(origin) {

        this->firstPart = new SnakePart(1,origin);
        this->firstPart->addPart();
        this->firstPart->addPart();

}

void Snake::draw() {
        GlObject::draw();
        this->firstPart->setRotation(*this->angle, 0,1,0);
        this->firstPart->draw();
}