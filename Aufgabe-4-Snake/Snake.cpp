//
// Created by Stefan B. on 16.06.15.
//

#include "Snake.h"
#include "Point.h"
#include "SnakePart.h"
Snake::Snake(Point *origin)
        : GlObject::GlObject(origin) {
        this->firstPart = new SnakePart(1,origin);
        this->firstPart->addPart();
        this->firstPart->addPart();
        this->firstPart->addPart();
        this->firstPart->setRotation(this->angle, new Vec3(0,1,0));

}

void Snake::draw() {
        GlObject::draw();
        this->firstPart->draw();
}