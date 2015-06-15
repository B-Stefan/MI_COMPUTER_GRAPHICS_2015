//
// Created by Stefan B. on 09.06.15.
//

#include "Point.h"
#include <iostream>
#include <math.h>
#include "./../_lib/utils.h"

using namespace std;
Point::Point(Vec3 *origin) {
    this->applyDefaults();
    this->originVec = origin;
}
Point::Point(Point *origin) {
    this->applyDefaults();
    this->originVec = origin->getPosition();
}
Point::Point(Point *origin, double x, double y, double z) {
    this->applyDefaults();
    this->defaultTranslateVec = *new Vec3(x,y,z);
    this->originVec = origin->getPosition();
}
void Point::applyDefaults() {
    this->calculatedPosition = *new Vec3(0,0,0);
    this->defaultRotationVec = new Vec3(0,0,0);
    this->defaultRotationAngle = new double();
    this->defaultTranslateVec = * new Vec3(0,0,0);

    this->dynamicRotationVec = new Vec3(0,0,0);
    this->dynamicRotationAngle = new double();
    this->dynamicTranslateVec = * new Vec3(0,0,0);
    this->dynamicRotationOrigin = this->originVec;
}
void Point::setDefaultRotation(double *angle, Vec3 *v) {
    this->defaultRotationAngle = angle;
    this->defaultRotationVec = v;
}
void Point::applyRotate(double *angle, Vec3 *rotationVec, Vec3 *rotationOrigin) {

    //Only applyRotate if angle and vector set
    if(*angle == 0|| (rotationVec->p[0] + rotationVec->p[1] + rotationVec->p[2]) == 0 ){
        return;
    }
    // translate point back to origin:
    Vec3* p = new Vec3(this->calculatedPosition - *rotationOrigin);

    double alpha  = *angle;

    double n1 = rotationVec->p[0];
    double n2 = rotationVec->p[1];
    double n3 = rotationVec->p[2];

    double cosA = cos(alpha);
    double sinA = sin(alpha);
    //cout  << "alpha: " << alpha << "\t n"<< n1 << ", " << n2 << ","<< n3<<" cos/alpga" << cosA << "/"  << sinA <<  endl;


    Vec3* newPos = new Vec3();
    newPos->p[0] = p->p[0] *     (n1*n1*(1-cosA)+cosA)       + p->p[1] *     (n1*n2 * (1-cosA)- n3*sinA)      +      p->p[2] *     (n1*n3*(1-cosA)+2*sinA);
    newPos->p[1] = p->p[0] *     (n2*n1*(1-cosA)+n3*sinA)    + p->p[1] *     (n2*n2 * (1-cosA)+ cosA)         +      p->p[2] *     (n2*n3*(1-cosA)-n1*sinA);
    newPos->p[2] = p->p[0] *     (n3*n1*(1-cosA)-n2*sinA)    + p->p[1] *     (n3*n2 * (1-cosA)+ n1 * sinA)    +      p->p[2] *     (n3*n3*(1-cosA) + cosA);


    // translate point back:
    this->calculatedPosition = *newPos + *rotationOrigin;

}
void Point::setDynamicRotate(double *angle, Vec3 *rotationVec, Vec3 *rotationOrigin) {
    this->dynamicRotationAngle  = angle;
    this->dynamicRotationVec = rotationVec;
    this->dynamicRotationOrigin = rotationOrigin;
}
void Point::recalculatePosition() {
    Vec3 newPos = (*this->originVec) + this->defaultTranslateVec;
    this->calculatedPosition.p[0] = newPos.p[0];
    this->calculatedPosition.p[1] = newPos.p[1];
    this->calculatedPosition.p[2] = newPos.p[2];
    this->applyRotate(this->defaultRotationAngle, this->defaultRotationVec, this->originVec);
    this->applyRotate(this->dynamicRotationAngle, this->dynamicRotationVec, this->dynamicRotationOrigin);
}
Vec3* Point::getPosition() {
    this->recalculatePosition();
    return &this->calculatedPosition;
}