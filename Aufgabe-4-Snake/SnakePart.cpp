//
// Created by Stefan B. on 16.06.15.
//

#include "SnakePart.h"
#include "Cuboid.h"
#include <iostream>
double DELTA_BETWEEN_PARTS = 0.3;
bool  testtest = true;
SnakePart::SnakePart(double l, SnakePart *origin)
        :Cuboid(l,l,new Point(origin->originPoint,l+DELTA_BETWEEN_PARTS,0,0)){
        this->beforeNode = origin;
        this->applyValues(l);

}
SnakePart::SnakePart(double l, Point *origin)
        :Cuboid(l,l,origin){
        this->applyValues(l);

}
double* SnakePart::getAngle() {
        return this->angle;
}
Vec3* SnakePart::getRotationVec() {
        return this->rotationVec;
}
void SnakePart::applyValues(double l) {
        this->part_length = l;
}
SnakePart* SnakePart::getBeforeNode() {
        return this->beforeNode;
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
                double angleBefore = *this->beforeNode->getAngle();
                this->rotationVec->p[0] = this->beforeNode->getRotationVec()->p[0];
                this->rotationVec->p[1] = this->beforeNode->getRotationVec()->p[1];
                this->rotationVec->p[2] = this->beforeNode->getRotationVec()->p[2];
                double delta = M_PI  * 0.5;
                *this->angle = angleBefore + delta; //angleBefore - M_PI *0.10;
                //Recalculate translation for the part

                Vec3 * translationVec = new Vec3(0,0,0);

                /*
                if(this->beforeNode->getBeforeNode() == nullptr){
                        std::cout << *this->angle /M_PI << std::endl;
                        testtest = false;
                        translationVec->p[2]  = this->part_length * (*this->angle/M_PI) *2  *-1 ;
                }*/
                //translationVec->p[2]  = this->part_length/4 *-1 ;
                this->originPoint->setDynamicTranslationVec(translationVec);
        }
}
void SnakePart::draw() {
        Cuboid::draw();
        this->recalculateRotationValues();
        if(this->nextNode != nullptr){
                this->nextNode->draw();
        }

}