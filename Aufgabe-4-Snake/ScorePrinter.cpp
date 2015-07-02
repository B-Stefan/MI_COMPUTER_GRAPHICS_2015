//
// Created by Fabian Redecker on 30.06.15.
//

#include <OpenGL/OpenGL.h>
#include "ScorePrinter.h"

ScorePrinter::ScorePrinter(){}

ScorePrinter::ScorePrinter(int x, int y, int z, string text) {
    this->textToPrint = text;
    this->posX = x;
    this->posY = y;
    this->posZ = z;
}

string ScorePrinter::intToString(int number) {
    return to_string(number);
}

void ScorePrinter::changeText(string newText) {
    this->textToPrint = newText;
}

void ScorePrinter::print() {
    //x,y & z position of the text
    glRasterPos3f(this->posX, this->posY, this->posZ);
    //get lenght of the string
    int len = this->textToPrint.length();
    //display char by char
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, this->textToPrint[i]);
    }
}

void ScorePrinter::printDefaultText(string defaultText) {
    //x,y & z position of the text
    glRasterPos3f(-1,1,19);
    //get lenght of the string
    int len = defaultText.length();
    //display char by char
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, defaultText[i]);
    }
}

