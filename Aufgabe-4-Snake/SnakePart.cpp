//
// Created by Stefan B. on 16.06.15.
//

#include "SnakePart.h"
#include "Cuboid.h"
#include <iostream>
#include <cmath>
#include "./../_lib/utils.h";

const double DELTA_STEPS_BETWEEN_PARTS = 10;
const double DEFAULT_VELOCITY  = 0.01;

SnakePart::SnakePart(double l, int index,std::deque<Vec3>* trackPos,std::deque<double>* trackRotation,int * deltaBetweenParts, SnakePart *origin)
        : GlObject(origin->globalOrigin){
    this->globalOrigin = origin->globalOrigin;
    this->applyValues(l);
    this->beforeNode = origin;
    this->index = index;
    this->trackPositions = trackPos;
    this->trackRotations= trackRotation;
    this->deltaBetweenParts = deltaBetweenParts;
}
SnakePart::SnakePart(double l, SnakePart *origin)
        : GlObject(origin->globalOrigin) {
    this->globalOrigin = origin->globalOrigin;
    this->applyValues(l);
    this->beforeNode = origin;

}
SnakePart::SnakePart(double l, Point *origin)
        : GlObject(origin) {
    this->globalOrigin = origin;
    this->applyValues(l);

}

double SnakePart::getPartLength() {
    return this->part_length;
}

void SnakePart::applyValues(double l) {
    this->index = 0;
    this->trackPositions = new std::deque<Vec3>();
    this->trackRotations = new std::deque<double>();
    this->part_length = l;
    this->innerTranslationVec = new Vec3(0, 0, 0);
    this->drawObject = new Cuboid(this->part_length, this->part_length, this->originPoint);
    this->drawObject->getOriginPoint()->setTranslationVec(this->innerTranslationVec);
    this->nextNode = nullptr;
    this->beforeNode = nullptr;
    this->deltaBetweenParts = new int(DELTA_STEPS_BETWEEN_PARTS);

}
void SnakePart::setRotation(double angle, int x, int y, int z) {
    this->drawObject->setRotation(angle,x,y,z);
}
void SnakePart::setRotation(double angle, Vec3 vec) {
    this->drawObject->setRotation(angle,vec);
}
std::deque<Vec3>* SnakePart::getTrack() {
    return  this->trackPositions;
}
SnakePart *SnakePart::addPart() {
    if (this->nextNode != nullptr) {
        return this->nextNode->addPart();
    } else {
        int newIndex = this->index+1;
        this->nextNode = new SnakePart(this->part_length,newIndex, this->trackPositions,this->trackRotations,this->deltaBetweenParts, this);
        return this->nextNode;
    }
}

double * SnakePart::getAngle() {
    return this->drawObject->getOriginPoint()->getAngle();
}
/**
 * Calculates the rotation for the part, based on the previous parts
 */
void SnakePart::recalculateRotationValues() {
    //If the part is not the first part
    if (this->beforeNode != nullptr) {
        this->setRotation(this->getRotationFromTrack(),0,1,0);

    }
}


bool SnakePart::isTrackReadyToDraw() {
    return this->trackPositions->size() >= (*this->deltaBetweenParts * this->index);
}

bool SnakePart::colidate(Vec3 * vec) {
    if(!this->isTrackReadyToDraw()){
        return false;
    }
    if(this->drawObject->colidate(vec)){
        return true;

    }
    else if(this->nextNode != nullptr){
        if(this->nextNode->colidate(this->getOriginPoint()->getPosition())){
            return true;
        }
        return this->nextNode->colidate(vec);
    }else {
        return false;
    }
}

/**
 * Set up translation for this part based on the last position.
 * This functions generate an vector that points to the old position relative to the global origin of the snake
 */
void SnakePart::recalculateTranslationValues() {
    Vec3 translationVecToOldPos = this->getPositionFromTrack();

    this->translationVec->p[0] = translationVecToOldPos.p[0];
    this->translationVec->p[1] = translationVecToOldPos.p[1];
    this->translationVec->p[2] = translationVecToOldPos.p[2];

}

Vec3 SnakePart::getPositionFromTrack() {
    std::deque <Vec3> track = *this->trackPositions;
    return track[this->index * *this->deltaBetweenParts];
}
double SnakePart::getRotationFromTrack() {
    std::deque <double > track = *this->trackRotations;
    return track[this->index * *this->deltaBetweenParts];


}
Point* SnakePart::getOriginPoint() {
    return this->drawObject->getOriginPoint();
}
void SnakePart::draw() {
    GlObject::draw();

    if(!this->isTrackReadyToDraw()){
        return;
    }

    this->recalculateRotationValues();
    this->recalculateTranslationValues();

    this->drawObject->setMaterialColor(GlObject::MATERIAL_SIDES::BACK, 1, 0, 0);
    this->drawObject->setMaterialColor(GlObject::MATERIAL_SIDES::FRONT, 1, 0, 0);

    this->drawObject->draw();

    if (this->nextNode != nullptr) {
        this->nextNode->draw();
    }
}