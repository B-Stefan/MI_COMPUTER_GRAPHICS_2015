//
// Created by Fabian Redecker on 25.06.15.
//

#include "Playground.h"
#include "GlObject.h"


Playground::Playground() {
    //field height
    this->fieldHeight = 18;
    //field width
    this->fieldWidth = 19.0;
    //height of the side fence
    this->fieldZ = 2;
    // left down corner x position
    this->startX = 5;
    // left down corner y position
    this->startY = 5;
    // z position of the points
    this->fieldPosZ = 0;
}

Playground::Playground(double field_width, double field_height, double start_x, double start_y) {
    //field height
    this->fieldHeight = field_height;
    //field width
    this->fieldWidth = field_width;
    //height of the side fence
    this->fieldZ = 2;
    // left down corner x position
    this->startX = start_x;
    // left down corner y position
    this->startY = start_y;
    // z position of the points
    this->fieldPosZ = 0;
}

void Playground::setMaterialColoR(GlObject::MATERIAL_SIDES side, double r, double g, double b) {
    GlObject::setMaterialColorStatic(side, r, g, b);
}

void Playground::drawPlaygrounD(){

    //ground
    glBegin(GL_QUADS);
    setMaterialColoR(GlObject::MATERIAL_SIDES::FRONT ,0,1,0);
    setMaterialColoR(GlObject::MATERIAL_SIDES::BACK,0,1,0);
    glVertex3f(startX,fieldPosZ,startY);
    glVertex3f(fieldWidth + startX, fieldPosZ, startY);
    glVertex3f(fieldWidth + startX ,fieldPosZ, fieldHeight + startY);
    glVertex3f(startX, fieldPosZ, fieldHeight + startY);
    glEnd();
    glFlush();


    //left
    glBegin(GL_QUAD_STRIP);
    setMaterialColoR(GlObject::MATERIAL_SIDES::FRONT,1,0,0);
    setMaterialColoR(GlObject::MATERIAL_SIDES::BACK,1,0,0);
    glVertex3f(startX,fieldPosZ,startY);
    glVertex3f(startX, fieldPosZ, fieldHeight + startY);
    glVertex3f(startX,  fieldZ, startY);
    glVertex3f(startY, fieldZ, fieldHeight + startY);
    glEnd();
    glFlush();

    //right
    glBegin(GL_QUAD_STRIP);
    setMaterialColoR(GlObject::MATERIAL_SIDES::FRONT,0,1,0);
    setMaterialColoR(GlObject::MATERIAL_SIDES::BACK,0,1,0);
    glVertex3f(fieldWidth + startX, fieldPosZ, startY);
    glVertex3f(fieldWidth + startX  ,fieldZ,startY);
    glVertex3f(fieldWidth + startX, fieldPosZ, fieldHeight + startY);
    glVertex3f(fieldWidth + startX, fieldZ, fieldHeight + startY);
    glEnd();
    glFlush();

    //down
    glBegin(GL_QUAD_STRIP);
    setMaterialColoR(GlObject::MATERIAL_SIDES::FRONT,0,0,1);
    setMaterialColoR(GlObject::MATERIAL_SIDES::BACK,0,0,1);
    glVertex3f(startX,fieldPosZ,startY);
    glVertex3f(fieldWidth + startX, fieldPosZ, startY);
    glVertex3f(startX, fieldZ, startY);
    glVertex3f(fieldWidth + startX,fieldZ, startY);
    glEnd();
    glFlush();

    //Top
    glBegin(GL_QUAD_STRIP);
    setMaterialColoR(GlObject::MATERIAL_SIDES::FRONT,0,0,0);
    setMaterialColoR(GlObject::MATERIAL_SIDES::BACK,0,0,0);
    glVertex3f(startX,fieldPosZ,fieldHeight + startY);
    glVertex3f(fieldWidth + startX, fieldPosZ, fieldHeight + startY);
    glVertex3f(startX,fieldZ,fieldHeight + startY);
    glVertex3f(fieldWidth + startX, fieldZ, fieldHeight + startY);
    glEnd();
    glFlush();

}

bool Playground::isVecInField(Vec3 k) {
    //check x && y
    if((k.p[0] > this->fieldMinX && k.p[0] < this->fieldMaxX)
            &&(k.p[2] > this->fieldMinY && k.p[2] < this->fieldMaxY)){
        return true;
    }
    else{
        return false;
    }
}