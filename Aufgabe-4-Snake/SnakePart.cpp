//
// Created by Stefan B. on 16.06.15.
//

#include "SnakePart.h"
#include "Cuboid.h"
#include <iostream>
#include <cmath>
#include "./../_lib/utils.h";

double DELTA_BETWEEN_PARTS = 0.6;
double DEFAULT_VELOCITY  = 0.01;

SnakePart::SnakePart(double l, SnakePart *origin)
        : GlObject(origin->globalOrigin) {
    this->globalOrigin = origin->globalOrigin;
    this->beforeNode = origin;
    this->applyValues(l);

}

SnakePart::SnakePart(double l, Point *origin)
        : GlObject(origin) {
    this->globalOrigin = origin;
    this->applyValues(l);
    this->beforeNode = nullptr;

}

double SnakePart::getPartLength() {
    return this->part_length;
}
double SnakePart::getVelocity() {
    return this->cuboidTranslationVec->p[0];
}
void SnakePart::applyValues(double l) {
    this->part_length = l;
    this->velocity = DEFAULT_VELOCITY;
    this->cuboidTranslationVec = new Vec3(0, 0, 0);
    this->cuboid = new Cuboid(this->part_length, this->part_length, this->originPoint);
    this->cuboid->getOriginPoint()->setTranslationVec(this->cuboidTranslationVec);
    this->oldAbsolutPosition = nullptr;
    this->oldAbsolutRotation = new Vec3();
    this->nextNode = nullptr;

}

Vec3 SnakePart::getOldAbsolutPosition() {
    return *this->oldAbsolutPosition;
}

SnakePart *SnakePart::getBeforeNode() {
    return this->beforeNode;
}

void SnakePart::setRotation(double angle, int x, int y, int z) {
    this->cuboid->setRotation(angle, x, y, z);
}
double *SnakePart::getAngle() {
    return this->cuboid->getOriginPoint()->getAngle();
}
Point* SnakePart::getOriginPoint() {
    return this->cuboid->getOriginPoint();
}

Point *SnakePart::getTranslationPoint() {
    return this->originPoint;
}

SnakePart *SnakePart::addPart() {
    if (this->nextNode != nullptr) {
        return this->nextNode->addPart();
    } else {
        this->nextNode = new SnakePart(this->part_length, this);
        return this->nextNode;
    }
}
/**
 * Calculates the rotation for the part, based on the previous parts
 */
void SnakePart::recalculateRotationValues() {
    //If the part is not the first part
    if (this->beforeNode != nullptr) {
        double *angleBefore = this->beforeNode->getAngle();
        double *currentangle = this->getAngle();
        double delta = *angleBefore - *currentangle;
        double  diff = 0;
        // std::cout << "START FOR NEW PART " << std::endl;
        // std::cout << "angleBefore: " << * angleBefore  << std::endl;
        // std::cout << "currentangle: " << * currentangle  << std::endl;
        // std::cout << "delta: " << delta  << std::endl;
        // std::cout << "(0.004/delta): " << *currentangle / *angleBefore << std::endl;



        /**
         * Set up rotation for part
         */
        if(delta != 0){

            //Function diagramm: https://www.google.de/webhp?sourceid=chrome-instant&ion=1&espv=2&ie=UTF-8#q=y%20%3D%201%2Fx%5E2
            diff = 1/exp(delta);
            //delta = delta * 0.004  + diff *delta * 0.004;
            delta = delta * 0.005;
        }

        if(fabs(delta) < 0.000005){
            delta = 0;
            *currentangle = *angleBefore;
        }else {
            *currentangle = *currentangle + delta;
        }
        std::cout << "delta: " << delta  << " - DIFF " << diff<<  std::endl;


        this->cuboid->setRotation(*currentangle, 0, 1, 0);
        this->setVelocity(DEFAULT_VELOCITY);

    } else {
        //if the part is the first part
        double *angle = this->getAngle();
        this->cuboid->setRotation(*angle * 0.5, 0, 1, 0);
        this->setVelocity(DEFAULT_VELOCITY);
    }
}

/**
 * Return a new postion for a part based an the current x orientation. So the new position is actual behind the this part
 */
Vec3 SnakePart::getPositionForNewPart() {
    this->cuboid->getOriginPoint()->recalculatePosition(true);
    Point *newPos = new Point(this->cuboid->getOriginPoint(), this->part_length + DELTA_BETWEEN_PARTS, 0, 0);
    Utils::printVec3(*newPos->getPosition(), "NEW POS");
    return *newPos->getPosition();


}

/**
 * Set up velocity for the current part s
 */
void SnakePart::setVelocity(double d) {
    this->velocity = d;
}

/**
 * Set up translation for this part based on the last position.
 * This functions generate an vector that points to the old position relative to the global origin of the snake
 */
void SnakePart::recalculateTranslationValues() {
    Vec3 *globalOrigin = this->globalOrigin->getPosition();
    Vec3 vecToLastPosFromGlobalOrigin = *this->oldAbsolutPosition - *globalOrigin;
    Vec3 translationVecToOldPos = vecToLastPosFromGlobalOrigin;
/*
        Utils::printVec3(*globalOrigin, "globalOrigin");
        Utils::printVec3(*this->oldAbsolutPosition, "oldAbsolutPosition");
        Utils::printVec3(vecTocurrentPositionFromGlobalOrigin, "vecTocurrentPositionFromGlobalOrigin");
        Utils::printVec3(vecToLastPosFromGlobalOrigin, "vecToLastPosFromGlobalOrigin");
        Utils::printVec3(translationVecToOldPos);
*/


    this->translationVec->p[0] = translationVecToOldPos.p[0];
    this->translationVec->p[1] = translationVecToOldPos.p[1];
    this->translationVec->p[2] = translationVecToOldPos.p[2];

    this->cuboidTranslationVec->p[0] = this->velocity * -1;//delta;

}

/**
 * Save the current position
 */
void SnakePart::applyLastPosition() {

    /**
     * If it is the fist time this function called set up the postion behind the part before
     */
    if (this->oldAbsolutPosition == nullptr) {
        if (this->beforeNode != nullptr) {
            this->oldAbsolutPosition = new Vec3(this->beforeNode->getPositionForNewPart());
        } else {
            this->oldAbsolutPosition = new Vec3();
        }
    } else {
        //store the absolut position of the cuboid in a vector

        this->cuboid->getOriginPoint()->recalculatePosition(true);
        Vec3 *calculatedInnerPos = this->cuboid->getOriginPoint()->getPosition();
        this->oldAbsolutPosition->p[0] = calculatedInnerPos->p[0];
        this->oldAbsolutPosition->p[1] = calculatedInnerPos->p[1];
        this->oldAbsolutPosition->p[2] = calculatedInnerPos->p[2];


        double *calculatedInnerRotation = this->cuboid->getOriginPoint()->getAngle();
        this->oldAbsolutRotation->p[0] = 0;
        this->oldAbsolutRotation->p[1] = *calculatedInnerRotation;
        this->oldAbsolutRotation->p[2] = 0;
    }

}

void SnakePart::draw() {
    GlObject::draw();
    //Only called once, on the first draw of the object
    if (this->oldAbsolutPosition == nullptr) {
        std::cout << "FIRST DRAW " << std::endl;
        this->applyLastPosition();
    }

    this->recalculateRotationValues();
    this->recalculateTranslationValues();

    this->cuboid->setMaterialColor(GlObject::MATERIAL_SIDES::BACK, 1, 0, 0);
    this->cuboid->setMaterialColor(GlObject::MATERIAL_SIDES::FRONT, 1, 0, 0);

    this->cuboid->draw();

    if (this->nextNode != nullptr) {
        this->nextNode->draw();
    }

    this->applyLastPosition();

}