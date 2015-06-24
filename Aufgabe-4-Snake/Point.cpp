//
// Created by Stefan B. on 09.06.15.
//

#include "Point.h"
#include <iostream>
#include <math.h>
#include "./../_lib/utils.h"
#include <string>
// Converts radians to degrees
double Rad2Deg(double radians){
    return radians*(180/3.141592653589793238);
}

using namespace std;
Point::Point(Vec3 *origin, std::string name ) {
    this->applyDefaults();
    this->originVec = origin;
    this->name = name;
    this->dynamicRotationOrigin = this->originVec;
}
Point::Point(Vec3 *origin) {
    this->applyDefaults();
    this->originVec = origin;
    this->dynamicRotationOrigin = this->originVec;
}
Point::Point(Point *origin) {
    this->applyDefaults();
    this->originVec = origin->getPosition();
    this->originPoint  = origin;
    this->dynamicRotationOrigin = this->originVec;
}
Point::Point(Point *origin, double x, double y, double z) {
    this->applyDefaults();
    this->defaultTranslateVec = *new Vec3(x,y,z);
    this->originVec = origin->getPosition();
    this->originPoint  = origin;
    this->dynamicRotationOrigin = this->originVec;
}
void Point::applyDefaults() {
    this->originPoint = nullptr;
    this->name = "NONE";
    this->calculatedNormalVector = *new Vec3(1,1,1);
    this->calculatedPosition = *new Vec3(0,0,0);

    this->defaultRotationVec = new Vec3(0,0,0);
    this->defaultRotationAngle = new double();
    this->defaultTranslateVec = * new Vec3(0,0,0);

    this->dynamicTranslateVec = new Vec3(0,0,0);
    this->dynamicRotationVec = new Vec3(0,0,0);
    this->dynamicRotationAngle = new double();

}
void Point::setDynamicTranslationVec(Vec3 *vec) {
    this->dynamicTranslateVec = vec;
}

void Point::setDefaultRotation(double *angle, Vec3 *v) {
    this->defaultRotationAngle = angle;
    this->defaultRotationVec = v;
}
void Point::applyRotate(double *angle, Vec3 *rotationVec, Vec3 *rotationOrigin, Vec3 *resultVec) {

    //Only applyRotate if angle and vector set
    if(*angle == 0|| (rotationVec->p[0] + rotationVec->p[1] + rotationVec->p[2]) == 0 ){
        return;
    }
    // translate point back to origin:
    Vec3* p = new Vec3(*resultVec - *rotationOrigin);


    double alpha  = *angle;

    double n1 = rotationVec->p[0];
    double n2 = rotationVec->p[1];
    double n3 = rotationVec->p[2];

    double cosA = cos(alpha);
    double sinA = sin(alpha);
    //cout  << "alpha: " << alpha << "\t n"<< n1 << ", " << n2 << ","<< n3<<" cos/alpga" << cosA << "/"  << sinA <<  endl;


    Vec3* newPos = new Vec3();
    newPos->p[0] = p->p[0] *     (n1*n1*(1-cosA)+cosA)       + p->p[1] *     (n1*n2 * (1-cosA)- n3*sinA)      +      p->p[2] *     (n1*n3*(1-cosA)+n2*sinA);
    newPos->p[1] = p->p[0] *     (n2*n1*(1-cosA)+n3*sinA)    + p->p[1] *     (n2*n2 * (1-cosA)+ cosA)         +      p->p[2] *     (n2*n3*(1-cosA)-n1*sinA);
    newPos->p[2] = p->p[0] *     (n3*n1*(1-cosA)-n2*sinA)    + p->p[1] *     (n3*n2 * (1-cosA)+ n1 * sinA)    +      p->p[2] *     (n3*n3*(1-cosA) + cosA);


    // translate point back:
    Vec3 result = *newPos + *rotationOrigin;
    resultVec->p[0] = result.p[0];
    resultVec->p[1] = result.p[1];
    resultVec->p[2] = result.p[2];

}
void Point::setDynamicRotate(double *angle, Vec3 *rotationVec, Vec3 *rotationOrigin) {
    this->dynamicRotationAngle  = angle;
    this->dynamicRotationVec = rotationVec;
    this->dynamicRotationOrigin = rotationOrigin;
}
void Point::applyRotations() {

    Vec3  * normal = new Vec3(*this->getNormal());
    double r = normal->Length();

    if(r== 0){
        return;
    }
    Utils::printVec3(*this->dynamicRotationVec, "vec");
    Utils::printVec3(*this->dynamicRotationOrigin,"origin");
    Utils::printVec3(this->calculatedPosition, "calculatedPos");
    Utils::printVec3(*normal, "normal");

    /*// Polar angle
    double theta = atan2(sqrt(pow(normal->p[0],2)
                              +pow(normal->p[1],2)),normal->p[2]);

    // Azimuthal angle
    double phi = atan2(normal->p[1],normal->p[0]);

    cout << "===>" << this->getName() << "<===" << endl;
    cout <<"P:" << Rad2Deg(phi) << "(" << phi << ")" << endl;
    cout <<"theta:" << Rad2Deg(theta) << "(" << theta << ")" << endl;
    cout <<"R:" << Rad2Deg(r) << "(" << r << ")" << endl;
*/

    /*

    Vec3 tangent0 = *normal % *new Vec3(1,0,0);

    double t =  tangent0.DotXY(tangent0);
    cout << "test"<< tangent0.DotXY(tangent0) <<  " - "<< t << endl;
    if (tangent0.DotXY(tangent0) < 0.001){
        tangent0 = *normal % *new Vec3(0, 1, 0);
    }
    Utils::printVec3(tangent0, "tangent0");

        tangent0.Normalize();

    // Find another vector in the plane
    Vec3* tangent1 = new Vec3(*normal % tangent0);
    Utils::printVec3(*tangent1, "tangent1");
        tangent1->Normalize();

    cout << "=>>> ULTIMATE ROTAION MATRIX for " << this->getName() << endl;
    cout << tangent0.p[0] << " \t " << tangent1->p[0] << " \t "<< normal->p[0] << endl;
    cout << tangent0.p[1] << " \t " << tangent1->p[1] << " \t "<< normal->p[1] << endl;
    cout << tangent0.p[2] << " \t " << tangent1->p[2] << " \t "<< normal->p[2] << endl;


    Vec3* p = new Vec3(this->calculatedPosition - *this->originVec);

    Vec3* newPos = new Vec3();
    newPos->p[0] = p->p[0] *     tangent0.p[0]    + p->p[1] *     tangent1->p[0]      +      p->p[2] *     normal->p[0];
    newPos->p[1] = p->p[0] *     tangent0.p[1]    + p->p[1] *     tangent1->p[1]      +      p->p[2] *     normal->p[1];
    newPos->p[2] = p->p[0] *     tangent0.p[2]    + p->p[1] *     tangent1->p[2]      +      p->p[2] *     normal->p[2];

     */


    Vec3 * direction = normal;
    Vec3 *up =  new Vec3(0,1,0);


    Vec3 * column1 = new Vec3();
    Vec3 * column2 = new Vec3(); 
    Vec3 * column3 = new Vec3(); 
    Vec3 xaxis = *up % *direction;
    xaxis.Normalize();

    Vec3 yaxis = *direction % xaxis;
    yaxis.Normalize();


    column1->p[0] = xaxis.p[0];
    column1->p[1] = yaxis.p[0];
    column1->p[2] = direction->p[0];

    column2->p[0] = xaxis.p[1];
    column2->p[1] = yaxis.p[1];
    column2->p[2] = direction->p[1];

    column3->p[0] = xaxis.p[2];
    column3->p[1] = yaxis.p[2];
    column3->p[2] = direction->p[2];






    Vec3* p = new Vec3(this->calculatedPosition - *this->originVec);

    Vec3* newPos = new Vec3();
    newPos->p[0] = p->p[0] *     column1->p[0]    + p->p[1] *     column2->p[0]      +      p->p[2] *     column3->p[0];
    newPos->p[1] = p->p[0] *     column1->p[1]    + p->p[1] *     column2->p[1]      +      p->p[2] *     column3->p[1];
    newPos->p[2] = p->p[0] *     column1->p[2]    + p->p[1] *     column2->p[2]      +      p->p[2] *     column3->p[2];


    *newPos = *newPos + *this->originVec;
    Utils::printVec3(*newPos, "newPost");
    this->calculatedPosition.p[0] = newPos->p[0];
    this->calculatedPosition.p[1] = newPos->p[1];
    this->calculatedPosition.p[2] = newPos->p[2];

}
void Point::applyTranslations() {
    Vec3 newPos = (*this->originVec) + this->defaultTranslateVec;
    newPos = (*this->dynamicTranslateVec) + newPos;
    this->calculatedPosition.p[0] = newPos.p[0];
    this->calculatedPosition.p[1] = newPos.p[1];
    this->calculatedPosition.p[2] = newPos.p[2];

}
void Point::recalculateNormalVector() {
    if(this->originPoint != nullptr){
        Vec3  * parentNormal = this->originPoint->getNormal();
        Utils::printVec3(*parentNormal,"Parent normal");

        this->calculatedNormalVector.p[0] = parentNormal->p[0];
        this->calculatedNormalVector.p[1] = parentNormal->p[1];
        this->calculatedNormalVector.p[2] = parentNormal->p[2];
    }else {
        this->calculatedNormalVector.p[0] = 1;
        this->calculatedNormalVector.p[1] = 1;
        this->calculatedNormalVector.p[2] = 1;
    }
    this->applyRotate(this->dynamicRotationAngle,this->dynamicRotationVec, new Vec3(0,0,0), &this->calculatedNormalVector);
    this->calculatedNormalVector.Normalize();

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
void Point::recalculatePosition() {
    this->applyTranslations();
    this->applyRotations();
}

Vec3* Point::getPosition() {
    this->recalculatePosition();
    return &this->calculatedPosition;
}