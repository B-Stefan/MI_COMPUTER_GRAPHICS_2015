//
// Created by Stefan B. on 05.07.15.
//

#include "SnakeHeadObject.h"
#include "./../_lib/utils.h"

SnakeHeadObject::SnakeHeadObject(double width,double height, Point *origin) : GlObject(origin){

        Point * totalRotate = new Point(this->originPoint);
        Point * totalRotateY = new Point(totalRotate);

        this->rotationPointForTop = new Point(totalRotateY, 0,-width/2,0);
        Point * topPoint = new Point(this->rotationPointForTop, 0,0,0);
        Point * bottomPoint = new Point(totalRotateY, 0,0,width/2);

        totalRotate->setRotate(new double(M_PI*0.5),new Vec3(1,0,0));
        totalRotateY->setRotate(new double(M_PI*0.5*-1),new Vec3(0,1,0));

        this->top = new TriangleCuboid(width,height/2,topPoint);
        this->bottom= new TriangleCuboid(width,height/2,bottomPoint);
        this->top->setTranslationVec(0,width/2,0);

        //this->side_a->setRotation(M_PI*0.25,0,1,0);
        //Material
        this->top->setMaterialColor(GlObject::MATERIAL_SIDES::FRONT, this->material_front);
        this->top->setMaterialColor(GlObject::MATERIAL_SIDES::BACK, this->material_back);

        this->bottom->setMaterialColor(GlObject::MATERIAL_SIDES::FRONT, this->material_front);
        this->bottom->setMaterialColor(GlObject::MATERIAL_SIDES::BACK, this->material_back);



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
    if(*angle < 0 ){
     this->top->setRotation(*angle,1,0,0);
    }
    this->top->draw();
    this->bottom->draw();
}