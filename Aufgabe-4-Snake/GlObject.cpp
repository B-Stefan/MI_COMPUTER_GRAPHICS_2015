//
// Created by Stefan B. on 09.06.15.
//

#include "GlObject.h"
#include "Point.h"
#include "../_lib/utils.h"
GlObject::GlObject(Point *origin) {
    this->originPoint = origin;
}
void GlObject::draw() {
    this->originPoint->recalculatePosition();
}