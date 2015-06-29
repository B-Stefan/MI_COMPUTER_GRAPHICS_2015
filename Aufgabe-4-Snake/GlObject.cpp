//
// Created by Stefan B. on 09.06.15.
//

#include "GlObject.h"
#include "Point.h"
#include "../_lib/utils.h"
GlObject::GlObject(Point *origin) {
    this->originPoint = new Point(origin);
    this->rotationVec = new Vec3(0,0,0);
    this->translationVec = new Vec3(0,0,0);
    this->angle = new double();
    this->originPoint->setRotate(this->angle, this->rotationVec);
    this->originPoint->setTranslationVec(this->translationVec );
}

Point* GlObject::getOriginPoint() {
    return this->originPoint;
}
void GlObject::setTranslationVec(int x, int y, int z) {
    this->setTranslationVec(*new Vec3(x,y,z));
}
void GlObject::setTranslationVec(Vec3 vec) {
    this->translationVec->p[0] = vec.p[0];
    this->translationVec->p[1] = vec.p[1];
    this->translationVec->p[2] = vec.p[2];
}
void GlObject::setRotation(double angle, Vec3 vec) {
    this->rotationVec->p[0]= vec.p[0];
    this->rotationVec->p[1]= vec.p[1];
    this->rotationVec->p[2]= vec.p[2];
    *this->angle = angle;
}
void GlObject::setRotation(double angle, int x, int y, int z) {
    this->rotationVec->p[0]= x;
    this->rotationVec->p[1]= y;
    this->rotationVec->p[2]= z;
    *this->angle = angle;
}

void GlObject::draw() {
    this->originPoint->recalculatePosition(true);
}
