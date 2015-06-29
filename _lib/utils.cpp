//
// Created by Stefan B. on 04.05.15.
//

#include "utils.h"
#include "vec3.hpp"
#include <GLFW/glfw3.h>
#include <GLUT/glut.h>
#include <iostream>
#include "./../Aufgabe-4-Snake/Point.h"
//this creates my translation matrix which causes the cube to disappear
using namespace std;
void Utils::setGlobalCoords(Vec3 &local, Vec3 &global) {
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble proj[16];
    GLdouble inverse[16];

    long double  tx  = local.p[0];
    long double  ty  = local.p[1];
    long double  tz  = local.p[2];
    long double  tw  = 1;

    long double newX;
    long double newY;
    long double newZ;
    long double newW;
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, proj );
    newX=modelview[0]*tx    +modelview[4]*ty    +modelview[8]*ty    +modelview[12] * tw;
    newY=modelview[1]*tx    +modelview[5]*ty    +modelview[9]*ty    +modelview[13] * tw;
    newZ=modelview[2]*tx    +modelview[6]*ty    +modelview[10]*ty   +modelview[14] * tw;
    newW=modelview[3]*tx    +modelview[7]*ty    +modelview[11]*ty   +modelview[15] * tw;

    /*
     *  modelViewMatric = [ 1 0 0 0
     *                      0 1 0 0
     *                      0 0 1 0
     *                      0 0 0 1
     *                      ]
     *
     *
     * */


    //Utils::logMatrix(modelview);
    //Utils::logMatrix(proj);

    global.p[0] = newX;
    global.p[1] = newY;
    global.p[2] = newZ;


}
void Utils::logMatrix(double m[16]){
    std::cout << m[0] << "\t " << m[4] << "\t " << m[8]<< "\t " << m[12]<< std::endl;
    std::cout << m[1] << "\t " << m[5] << "\t " << m[9]<< "\t " << m[13]<< std::endl;
    std::cout << m[2] << "\t " << m[6] << "\t " << m[10]<< "\t " << m[14]<< std::endl;
    std::cout << m[3] << "\t " << m[7] << "\t " << m[11]<< "\t " << m[15]<< std::endl;

}
void Utils::printVec3(Vec3 &point) {
    cout << "X:"<<point.p[0]   << "\t Y: " << point.p[1] << " \t Z:" << point.p[2]<< endl;
}

void Utils::printVec3(Vec3 &point, string desc) {
    cout  << "Point: " << desc << "\t X:"<<point.p[0]   << "\t Y: " << point.p[1] << " \t Z:" << point.p[2]<< endl;
}
void Utils::drawAxis(Vec3 &point, double length) {

    //Normal z-axis
    glBegin(GL_LINES);
    glColor3f(0, 1, 0.0);
    glVertex3f(point.p[0],point.p[1], point.p[2]);
    glVertex3f(point.p[0],point.p[1], point.p[2]+1*length);
    glEnd();


    //x-axis
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(point.p[0],point.p[1], point.p[2]);
    glVertex3f(point.p[0]+1+1*length,point.p[1], point.p[2]);
    glEnd();

    //y-axis
    glBegin(GL_LINES);
    glColor3f(point.p[0],point.p[1], 1);
    glVertex3f(point.p[0],point.p[1], point.p[2]);
    glVertex3f(point.p[0],point.p[1]+1*length, point.p[2]);
    glEnd();

}
void Utils::drawPoint(Point *point, double length) {

    length = length /2;

    Vec3 * origin = point->getPosition();
    Point* z = new Point(point,0,0,length);
    Vec3 * vecZ = z->getPosition();
    //Normal z-axis
    glBegin(GL_LINES);
    glColor3f(0, 1, 0.0);
    glVertex3f(origin->p[0],origin->p[1], origin->p[2]);
    glVertex3f(vecZ->p[0],vecZ->p[1], vecZ->p[2]);
    glEnd();

    Point* x = new Point(point,length,0,0);
    Vec3 * vecX = x->getPosition();
    x->setName(point->getName() + "-x");

    //x-axis
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(origin->p[0],origin->p[1], origin->p[2]);
    glVertex3f(vecX->p[0],vecX->p[1], vecX->p[2]);
    glEnd();

    Point* y = new Point(point,0,length,0);
    y->setName(point->getName() + "-y");
    Vec3 * vecY = y->getPosition();

    //y-axis
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(origin->p[0],origin->p[1], origin->p[2]);
    glVertex3f(vecY->p[0],vecY->p[1], vecY->p[2]);
    glEnd();

    return;
    cout << "=====> "<< point->getName() << "<====="<< endl;
    Vec3 * vecNormal = point->getNormal();
    Vec3 vecAbsolutPosition = *vecNormal + *point->getPosition();
    Utils::printVec3(*vecNormal, "normal: ");
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(origin->p[0],origin->p[1], origin->p[2]);
    glVertex3f(vecAbsolutPosition.p[0]*2,vecAbsolutPosition.p[1]*2, vecAbsolutPosition.p[2]*2);
    glEnd();

}

