//
// Created by Stefan B. on 09.06.15.
//

#include "Point.h"
#include <iostream>
#include <math.h>
#include "./../_lib/utils.h"
#include <string>

using namespace std;

int Point::currentLoopNumber = 0;

Point::Point(Vec3 *origin, std::string name ) {
    this->applyDefaults();
    this->originVec = origin;
    this->name = name;
}
Point::Point(Vec3 *origin) {
    this->applyDefaults();
    this->originVec = origin;
}
Point::Point(Point *origin) {
    this->applyDefaults();
    this->originVec = origin->getPosition();
    this->originPoint  = origin;
}
Point::Point(Point *origin, double x, double y, double z) {
    this->applyDefaults();
    this->originVec = origin->getPosition();
    this->originPoint  = origin;
    this->translateVec = new Vec3(x,y,z);
}
void Point::applyDefaults() {
    this->originPoint = nullptr;
    this->name = "NONE";
    this->calculatedNormalVector = *new Vec3(1,1,1);
    this->calculatedPosition = *new Vec3(0,0,0);

    this->translateVec = new Vec3(0,0,0);
    this->rotationVec = new Vec3(0,0,0);
    this->rotationAngle = new double();

    this->loopNumber = -1;

}
void Point::setTranslationVec(Vec3 *vec) {
    this->translateVec = vec;
}

void Point::setRotate(double *angle, Vec3 *rotationVec) {
    this->rotationAngle = angle;
    this->rotationVec = rotationVec;
}
void Point::applyRotations() {

    Vec3  * normal = new Vec3(*this->getNormal());
    if(normal->Length() == 0 ){
        return;
    }

    double cosA = cos(normal->p[0]);
    double sinA = sin(normal->p[0]);

    double cosB = cos(normal->p[1]);
    double sinB = sin(normal->p[1]);

    double cosG = cos(normal->p[2]);
    double sinG = sin(normal->p[2]);


    Vec3* p = new Vec3(this->calculatedPosition - *this->originVec);
    Vec3* newPos = new Vec3();
    /*
    newPos->p[0] = p->p[0] *     (cosA * cosG*-sinA*cosB*sinG)      + p->p[1] *     (sinA * cosG + cosA * cosB * cosG)          +      p->p[2] *     (cosA * sinB * cosG + sinA * sinG);
    newPos->p[1] = p->p[0] *     (-cosA*sinG-sinA*cosB*cosG)        + p->p[1] *     (-sinA * sinG + cosA * cosB * cosG)          +      p->p[2] *     (cosA * sinB * sinG - sinA * cosG);
    newPos->p[2] = p->p[0] *     (sinA*sinB)                        + p->p[1] *     (sinA*cosB)                             +      p->p[2] *     (cosA * cosB);
*/

    newPos->p[0] = p->p[0] *     (cosB*cosG )       + p->p[1] *     (sinA*sinB*cosG - cosA * sinG)          +      p->p[2] *     (cosA * sinB * cosG + sinA * sinG);
    newPos->p[1] = p->p[0] *     (cosB*sinG)        + p->p[1] *     (sinA*sinB*sinG + cosA * cosG)          +      p->p[2] *     (cosA * sinB * sinG - sinA * cosG);
    newPos->p[2] = p->p[0] *     (-sinB)            + p->p[1] *     (sinA*cosB)                             +      p->p[2] *     (cosA * cosB);


    // translate point back:
    Vec3 result = *newPos + *this->originVec;
    this->calculatedPosition.p[0] = result.p[0];
    this->calculatedPosition.p[1] = result.p[1];
    this->calculatedPosition.p[2] = result.p[2];

   // this->applyRotate(&normal->p[2],new Vec3(0,0,1),this->originVec, &this->calculatedPosition);
   // this->applyRotate(&normal->p[1],new Vec3(0,1,0),this->originVec, &this->calculatedPosition);
   // this->applyRotate(&normal->p[0],new Vec3(1,0,0),this->originVec, &this->calculatedPosition);

}
void Point::applyTranslations() {
    Vec3 newPos = (*this->originVec) + *this->translateVec;

    this->calculatedPosition.p[0] = newPos.p[0];
    this->calculatedPosition.p[1] = newPos.p[1];
    this->calculatedPosition.p[2] = newPos.p[2];

}
void Point::recalculateNormalVector() {
    if(this->originPoint != nullptr){
        Vec3  * parentNormal = this->originPoint->getNormal();

        this->calculatedNormalVector.p[0] = parentNormal->p[0];
        this->calculatedNormalVector.p[1] = parentNormal->p[1];
        this->calculatedNormalVector.p[2] = parentNormal->p[2];
    }else {
        this->calculatedNormalVector.p[0] = 0;
        this->calculatedNormalVector.p[1] = 0;
        this->calculatedNormalVector.p[2] = 0;
    }
    double angle = *this->rotationAngle;
    this->calculatedNormalVector.p[0] = this->calculatedNormalVector.p[0] + this->rotationVec->p[0] * angle;
    this->calculatedNormalVector.p[1] = this->calculatedNormalVector.p[1] + this->rotationVec->p[1] * angle;
    this->calculatedNormalVector.p[2] = this->calculatedNormalVector.p[2] + this->rotationVec->p[2] * angle;

}
void Point::setName(std::string name) {
    this->name = name;
}
std::string Point::getName() {
    return this->name;
}
Vec3* Point::getNormal() {
    this->recalculateNormalVector();
    return &this->calculatedNormalVector;
}
double* Point::getAngle() {
    return this->rotationAngle;
}
Vec3* Point::getRotationVec() {
    return this->rotationVec;
}
void Point::recalculatePosition(bool force) {
    if(this->loopNumber == Point::currentLoopNumber && force == false){
        return;
    }
    this->loopNumber = Point::currentLoopNumber;
    if(this->originPoint != nullptr){
        this->originPoint->recalculatePosition(force);
    }

    this->applyTranslations();
    this->applyRotations();
}
void Point::recalculatePosition() {
    this->recalculatePosition(false);
}

Vec3* Point::getPosition() {
    this->recalculatePosition();
    return &this->calculatedPosition;
}