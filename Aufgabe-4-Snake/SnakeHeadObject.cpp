//
// Created by Stefan B. on 05.07.15.
//

#include "SnakeHeadObject.h"
#include "./../_lib/utils.h"

SnakeHeadObject::SnakeHeadObject(double l, Point *origin) : GlObject(origin){
        this->length = l;



        this->rotationPointForTop = new Point(this->originPoint, 0,-l/2,0);
        Point * topPoint = new Point(this->rotationPointForTop, 0,0,0);
        Point * bottomPoint = new Point(this->originPoint, 0,0,-l/2);


        this->top = new TriangleCuboid(l,l/2,topPoint);
        this->bottom= new TriangleCuboid(l,l/2,bottomPoint);
        this->top->setTranslationVec(0,l/2,0);

        //this->side_a->setRotation(M_PI*0.25,0,1,0);
        //Material
        this->top->setMaterialColor(GlObject::MATERIAL_SIDES::FRONT, this->material_front);
        this->top->setMaterialColor(GlObject::MATERIAL_SIDES::BACK, this->material_back);

        this->bottom->setMaterialColor(GlObject::MATERIAL_SIDES::FRONT, new Vec3(1,0,0));
        this->bottom->setMaterialColor(GlObject::MATERIAL_SIDES::BACK, new Vec3(1,0,0));





}
bool SnakeHeadObject::colidate(Vec3 *point) {
    if (this->top->colidate(point)){
        return true;
    }
    else if (this->bottom->colidate(point)){
        return true;
    }else {
        return false;
    }
}
void SnakeHeadObject::draw() {
    GlObject::draw();
    double  * angle =  new double(*this->getOriginPoint()->getAngle());
    * angle = sin(*angle);
    if(*angle > 0 ){
     this->top->setRotation(*angle,1,0,0);
    }
    this->top->draw();
    this->bottom->draw();
}