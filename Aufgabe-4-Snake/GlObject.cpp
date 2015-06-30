//
// Created by Stefan B. on 09.06.15.
//

#include "GlObject.h"
#include "Point.h"
#include "../_lib/utils.h"
#include <GLFW/glfw3.h>


void GlObject::setMaterialColorStatic(MATERIAL_SIDES side, double r, double g, double b) {
    float	amb[4], dif[4], spe[4];
    int mat;

    dif[0] = r;
    dif[1] = g;
    dif[2] = b;

    for(int i = 0; i < 3; i++) {
        amb[i] = .1 * dif[i];
        spe[i] = .5;
    }
    amb[3] = dif[3] = spe[3] = 1.0;

    switch(side){
        case GlObject::MATERIAL_SIDES::FRONT:	mat = GL_FRONT;
            break;
        case GlObject::MATERIAL_SIDES::BACK:	mat = GL_BACK;
            break;
        default: mat = GL_FRONT_AND_BACK;
    }

    glMaterialfv(mat, GL_AMBIENT, amb);
    glMaterialfv(mat, GL_DIFFUSE, dif);
    glMaterialfv(mat, GL_SPECULAR, spe);
    glMaterialf( mat, GL_SHININESS, 20);
}
void GlObject::setMaterialColor(MATERIAL_SIDES side, Vec3 *rgb) {
    if(MATERIAL_SIDES::FRONT == side){
        this->material_front = rgb;
    }else if (MATERIAL_SIDES::BACK == side){
        this->material_back = rgb;
    }else {
        std::cout << "ERROR while setting up material" << std::endl;
    }
}
void GlObject::setMaterialColor(MATERIAL_SIDES side, double r, double g, double b) {
    if(MATERIAL_SIDES::FRONT == side){
        this->material_front->p[0] = r;
        this->material_front->p[1] = g;
        this->material_front->p[2] = b;
    }else if (MATERIAL_SIDES::BACK == side){
        this->material_back->p[0] = r;
        this->material_back->p[1] = g;
        this->material_back->p[2] = b;
    }else {
        std::cout << "ERROR while setting up material" << std::endl;
    }
}
GlObject::GlObject(Point *origin) {
    this->originPoint = new Point(origin);
    this->rotationVec = new Vec3(0,0,0);
    this->translationVec = new Vec3(0,0,0);
    this->angle = new double();
    this->originPoint->setRotate(this->angle, this->rotationVec);
    this->originPoint->setTranslationVec(this->translationVec );
    this->material_back = new Vec3();
    this->material_front = new Vec3();
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
    GlObject::setMaterialColorStatic(GlObject::MATERIAL_SIDES::FRONT, this->material_front->p[0],this->material_front->p[1],this->material_front->p[2]);
    GlObject::setMaterialColorStatic(GlObject::MATERIAL_SIDES::BACK, this->material_front->p[0],this->material_front->p[1],this->material_front->p[2]);
}
