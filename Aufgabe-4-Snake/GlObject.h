//
// Created by Stefan B. on 09.06.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_OBJECT_H
#define GLFW3_DEMO_WITH_CMAKE_OBJECT_H


#include "../_lib/vec3.hpp"
#include "Point.h"

class GlObject {
    public:
        static enum MATERIAL_SIDES {
                FRONT = 1,
                BACK = 2
        };
        static void setMaterialColorStatic(MATERIAL_SIDES side, double r, double g, double b);
        void setMaterialColor(MATERIAL_SIDES side, double r, double g, double b);
        void setMaterialColor(MATERIAL_SIDES side, Vec3 *rgb);
        GlObject(Point *origin);
        virtual bool colidate(Vec3 * point) = 0; //Abstract function. Implemented by the inheritance class
        virtual void draw();
        virtual void setRotation(double angle, Vec3 vec);
        virtual void setRotation(double angle, int x, int y, int z);
        Point * getOriginPoint();
        virtual void setTranslationVec(Vec3 vec);
        virtual void setTranslationVec(double x, double y, double z);
    protected:
        Point* originPoint;
        Vec3 * rotationVec;
        Vec3 * translationVec;
        Vec3 * material_front;
        Vec3 * material_back;
        double * angle;
};


#endif //GLFW3_DEMO_WITH_CMAKE_OBJECT_H
