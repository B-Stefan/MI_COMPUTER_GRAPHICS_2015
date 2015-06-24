//
// Created by Stefan B. on 09.06.15.
//

#include "GlObject.h"
#include "Point.h"
#include "../_lib/utils.h"
GlObject::GlObject(Point *origin) {
    this->originPoint = origin;
    this->rotationVec = new Vec3(0,0,0);
    this->angle = new double();
}

void GlObject::setRotation(double *angle, Vec3 *vec) {
    this->rotationVec= vec;
    this->angle = angle;
    this->originPoint->setDynamicRotate(this->angle,this->rotationVec,this->originPoint->getPosition());
}

void GlObject::draw() {
    this->originPoint->recalculatePosition();
}
