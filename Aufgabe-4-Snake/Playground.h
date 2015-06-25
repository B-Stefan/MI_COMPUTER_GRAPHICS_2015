//
// Created by Fabian Redecker on 25.06.15.
//

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "../_lib/vec3.hpp"


#ifndef GLFW3_DEMO_WITH_CMAKE_PLAYGROUND_H
#define GLFW3_DEMO_WITH_CMAKE_PLAYGROUND_H


class Playground {

public:
    // attributes
    double fieldWidth;
    double fieldHeight;
    //height of Sides


    double fieldZ;

    //start x & y
    double startX;
    double startY;
    double fieldPosZ;

    Playground();

    //methods
    void setMaterialColoR(int side, double r, double g, double b);
    void drawPlaygrounD();
    std::vector<double> distanceFromSideS(Vec3 k);



};


#endif //GLFW3_DEMO_WITH_CMAKE_PLAYGROUND_H
