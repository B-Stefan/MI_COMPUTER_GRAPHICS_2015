//
// Created by Fabian Redecker on 30.06.15.
//

#ifndef GLFW3_DEMO_WITH_CMAKE_SCOREPRINTER_H
#define GLFW3_DEMO_WITH_CMAKE_SCOREPRINTER_H

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "../_lib/vec3.hpp"
#include "../_lib/utils.h"
#include "../_lib/Quarter.h"
#include "Playground.h"
#include "Snake.h"
#include "Cuboid.h"
#include "Rectangle.h"
#include "Point.h"
#include <unistd.h>

class ScorePrinter {
private:
    //attributes
    string textToPrint;
    int posX;
    int posY;
    int posZ;
    int startScore = 0;


public:
    //constructors
    ScorePrinter();
    ScorePrinter(int x, int y,int z, string text);

    //methods
    void print();
    void printDefaultText(string defaultText);
    string intToString(int number);

    //getter & Setter
    int getStartScore(){
        return startScore;
    }
    void setStartScore(int startScore) {
        ScorePrinter::startScore = startScore;
    }
    void changeText(string newText);
};


#endif //GLFW3_DEMO_WITH_CMAKE_SCOREPRINTER_H
