//
// Created by Stefan B. on 04.05.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_SPHEREOLD_H
#define GLFW3_DEMO_WITH_CMAKE_SPHEREOLD_H

#import "vec3.hpp"

class SphereOld {

    public:
        SphereOld(Vec3 &middle, double r);
        void draw();
        Vec3 getMiddle();
        void setMiddle(Vec3 v);
        double getR();
    private:
        Vec3 middle;
        Vec3 middleGlobal;
        Vec3 borderLocal;
        double rGlobal;
        double r;
        void updateGlobalCoords();
        void drawSphere();
};


#endif //GLFW3_DEMO_WITH_CMAKE_SPHEREOLD_H
