//
// Created by Stefan B. on 05.07.15.
//

#include "TriangleCuboid.h"
#include "./../_lib/utils.h"

TriangleCuboid::TriangleCuboid(double l, Point *origin) : GlObject(origin){
        this->length = l;

        Point * topPoint = new Point(this->originPoint, 0,l/2,0);
        Point * bottomPoint = new Point(this->originPoint, 0,-l/2,0);
        Point * leftPoint = new Point(this->originPoint, l/2,0,0);

        this->top = new Triangle(l,topPoint);
        this->bottom= new Triangle(l,bottomPoint);
        this->side_a = new Rectangle(l,l + l/2,leftPoint);


        this->top->setRotation(M_PI * 0.5, 1,0,0);
        this->bottom->setRotation(M_PI * 0.5, 1,0,0);
        this->side_a->setRotation(M_PI*0.25,0,1,0);
        //Material
        this->top->setMaterialColor(GlObject::MATERIAL_SIDES::FRONT, this->material_front);
        this->top->setMaterialColor(GlObject::MATERIAL_SIDES::BACK, this->material_back);

        this->bottom->setMaterialColor(GlObject::MATERIAL_SIDES::FRONT, this->material_front);
        this->bottom->setMaterialColor(GlObject::MATERIAL_SIDES::BACK, this->material_back);


        this->side_a->setMaterialColor(GlObject::MATERIAL_SIDES::FRONT, new Vec3(1,0,0));
        this->side_a->setMaterialColor(GlObject::MATERIAL_SIDES::BACK, new Vec3(1,0,0));


}
bool TriangleCuboid::colidate(Vec3 *point) {
    if (this->top->colidate(point)){
        return true;
    }
    else if (this->bottom->colidate(point)){
        return true;
    }else {
        return false;
    }
}
void TriangleCuboid::draw() {
    GlObject::draw();

    Utils::drawPoint(this->originPoint,1);
    this->top->draw();
    this->bottom->draw();
    this->side_a->draw();
}