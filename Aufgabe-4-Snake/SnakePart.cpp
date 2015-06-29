//
// Created by Stefan B. on 16.06.15.
//

#include "SnakePart.h"
#include "Cuboid.h"
#include <iostream>
#include <cmath>
#include "./../_lib/utils.h";
double startAngle = 1;
double DELTA_BETWEEN_PARTS = 0.6;
SnakePart::SnakePart(double l, SnakePart *origin)
        :GlObject(origin->globalOrigin){
        this->globalOrigin = origin->globalOrigin;
        this->beforeNode = origin;
        this->applyValues(l);

}
SnakePart::SnakePart(double l, Point *origin)
        :GlObject(origin){
        this->globalOrigin = origin;
        this->applyValues(l);

}
double SnakePart::getVelocity() {
        return this->cuboidTranslationVec->p[0];
}
double* SnakePart::getAngle() {
        return this->cuboid->getOriginPoint()->getAngle();
}
void SnakePart::applyValues(double l) {
        this->part_length = l;
        this->velocity = 0;
        this->cuboidTranslationVec = new Vec3(0,0,0);
        this->cuboid = new Cuboid(this->part_length,this->part_length,this->originPoint);
        this->cuboid->getOriginPoint()->setTranslationVec(this->cuboidTranslationVec);
        this->oldAbsolutPosition = nullptr;
        this->oldAbsolutRotation = new Vec3();

}
Vec3 SnakePart::getOldAbsolutPosition() {
        return *this->oldAbsolutPosition;
}
SnakePart* SnakePart::getBeforeNode() {
        return this->beforeNode;
}
void SnakePart::setRotation(double angle, int x, int y, int z) {
        this->cuboid->setRotation(angle, x,y,z);
}
Point* SnakePart::getTranslationPoint() {
        return this->originPoint;
}
SnakePart* SnakePart::addPart() {
        if(this->nextNode != nullptr){
                return this->nextNode->addPart();
        }else {
                this->nextNode = new SnakePart(this->part_length, this);
                return this->nextNode;
        }
}
void SnakePart::recalculateRotationValues() {
        if(this->beforeNode != nullptr){
                double * angleBefore = this->beforeNode->getAngle();
                double * currentangle = this->getAngle();
                double delta = *angleBefore - *currentangle;

               // std::cout << "START FOR NEW PART " << std::endl;
//                std::cout << "angleBefore: " << * angleBefore  << std::endl;
//                std::cout << "currentangle: " << * currentangle  << std::endl;
               // std::cout << "delta: " << delta  << std::endl;
               std::cout << "(0.004/delta): " << *currentangle / * angleBefore  << std::endl;

                double diffAngle = delta *0.005;
                if(*angleBefore != 0 ){
                        diffAngle = diffAngle +diffAngle* (*currentangle / * angleBefore);
                }
                *currentangle =  * currentangle + diffAngle;

                // std::cout << "diffAngle " << diffAngle<< std::endl;

             //   std::cout << "verhältnis " << *currentangle / * angleBefore << std::endl;


                this->cuboid->setRotation(*currentangle,0,1,0);

                if(delta >0){

                        this->cuboidTranslationVec->p[0] = -0.01;//delta;
                }else {
                        this->cuboidTranslationVec->p[0] = -0.01;
                }

                //* currentangle = angleBefore - 0.1;
                //this->translationVec->p[]
                //double percent = cos(angle);;

                //double roundedPercent = round(percent * 100) / 100;
                //this->part_length*0.5 * percent;
                //std::cout << "percentage: " << percent  << "asda: " << angleBefore << std::endl;
        }else {
                double * angle = this->getAngle();
                this->cuboid->setRotation(*angle * 0.5,0,1,0);
                this->cuboidTranslationVec->p[0] = -0.01;
        }
}
Vec3 SnakePart::getPositionForNewPart() {
        this->cuboid->getOriginPoint()->recalculatePosition(true);
        Point * newPos = new Point(this->cuboid->getOriginPoint(),this->part_length + DELTA_BETWEEN_PARTS,0,0);
        Utils::printVec3(*newPos->getPosition(), "NEW POS");
        return *newPos->getPosition();


}
void SnakePart::setVelocity(double d) {
        this->velocity = d;
}
void SnakePart::recalculateTranslationValues() {
        Vec3 *  globalOrigin = this->globalOrigin->getPosition();
        Vec3    vecToLastPosFromGlobalOrigin            = *this->oldAbsolutPosition - *globalOrigin;
        Vec3    translationVecToOldPos =  vecToLastPosFromGlobalOrigin;
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

}
void SnakePart::applyLastPosition() {
        if(this->oldAbsolutPosition == nullptr){
                if(this->beforeNode != nullptr){
                        this->oldAbsolutPosition = new Vec3(this->beforeNode->getPositionForNewPart());
                }else {
                        this->oldAbsolutPosition = new Vec3();
                }
        }else {
                this->cuboid->getOriginPoint()->recalculatePosition(true);
                Vec3 * calculatedInnerPos = this->cuboid->getOriginPoint()->getPosition();
                this->oldAbsolutPosition->p[0] = calculatedInnerPos->p[0];
                this->oldAbsolutPosition->p[1] = calculatedInnerPos->p[1];
                this->oldAbsolutPosition->p[2] = calculatedInnerPos->p[2];


                double * calculatedInnerRotation = this->cuboid->getOriginPoint()->getAngle();
                this->oldAbsolutRotation->p[0] = 0;
                this->oldAbsolutRotation->p[1] = *calculatedInnerRotation;
                this->oldAbsolutRotation->p[2] = 0;
        }

}
void SnakePart::draw() {
        GlObject::draw();
        //If first draw set the value
        if(this->oldAbsolutPosition == nullptr){
                std::cout << "FIRST DRAW " << std::endl;
                this->applyLastPosition();
        }

        this->recalculateRotationValues();
        this->recalculateTranslationValues();
        this->cuboid->draw();

        if(this->nextNode != nullptr){
                this->nextNode->draw();
        }

        this->applyLastPosition();

}